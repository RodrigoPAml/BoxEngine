 #include <BoxEngine.hpp>
#include "Project.hpp"

namespace BoxEngine {
namespace Project {

    std::weak_ptr<Project> Project::current;

    void Project::Create()
    {
        using json = nlohmann::json;
        using namespace BoxEngine::Utils;

        auto debugConfig = Debug::Debugging::GetConfiguration();
        auto loggingConfig = Debug::Logging::GetConfiguration();

        auto debugObj = Serialization::Serialize(debugConfig);
        auto loggingObj = Serialization::Serialize(loggingConfig);

        json jsonFile = {
            {"project_name", this->name},
            {"debug", debugObj},
            {"logging", loggingObj},
            {"scene", json::array()}
        };

        std::string projectPath = this->GetBasePath();
        std::string projectSettingsPath = this->GetProjectSettingsPath();
        std::string assetsPath = this->GetAssetsPath();
        std::string logsPath = this->GetLogsPath();

        if (!Directory::Exists(projectPath))
            Directory::CreateDirectory(projectPath);

        if (Directory::Exists(projectSettingsPath))
            Directory::Delete(projectSettingsPath);

        Directory::CreateFile(projectSettingsPath, jsonFile.dump(2));

        if (!Directory::Exists(assetsPath))
            Directory::CreateDirectory(assetsPath);

        if (!Directory::Exists(logsPath))
            Directory::CreateDirectory(logsPath);

        Debug::Logging::Log("[Project]: Created in " + projectPath, Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);

        this->goManager = GoManagerPtr(new GoManager());
        this->scriptManager = ScriptManagerPtr(new ScriptManager());

        this->isModified = false;
    }

    void Project::Save()
    {
        using json = nlohmann::json;
        using namespace BoxEngine::Utils;
           
        auto debugConfig = Debug::Debugging::GetConfiguration();
        auto loggingConfig = Debug::Logging::GetConfiguration();

        auto debugObj = Serialization::Serialize(debugConfig);
        auto loggingObj = Serialization::Serialize(loggingConfig);
        auto gos = Serialization::SerializeGo(this->goManager->GetRootGameObjects());

        json jsonFile = {
            {"project_name", this->name},
            {"debug", debugObj},
            {"logging", loggingObj},
            {"scene", gos}
        };

        std::string projectPath = this->GetBasePath();
        std::string projectSettingsPath = this->GetProjectSettingsPath();
        std::string assetsPath = this->GetAssetsPath();
        std::string logsPath = this->GetLogsPath();

        if(!Directory::Exists(projectPath))
            Directory::CreateDirectory(projectPath);

        if (Directory::Exists(projectSettingsPath))
            Directory::Delete(projectSettingsPath);
            
        Directory::CreateFile(projectSettingsPath, jsonFile.dump(2));
           
        if (!Directory::Exists(assetsPath))
            Directory::CreateDirectory(assetsPath);

        if (!Directory::Exists(logsPath))
            Directory::CreateDirectory(logsPath);

        Debug::Logging::Log("[Project]: Saved in " + projectPath, Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
            
        this->isModified = false;
    }

    void Project::LoadFrom(const std::string& path)
    {
        this->SetPath(path);

        this->goManager = GoManagerPtr(new GoManager());
        this->scriptManager = ScriptManagerPtr(new ScriptManager());
    }

    void Project::Load()
    {
        using json = nlohmann::json;
        using namespace BoxEngine::Utils;

        std::string rawJson = Directory::ReadFile(this->GetProjectSettingsPath());
        json data = json::parse(rawJson);

        if (data.contains("project_name"))
            this->SetName(data["project_name"]);

        auto debugConfig = Serialization::DeserializeDebugConfiguration(data);
        auto loggingConfig = Serialization::DeserializeLoggingConfiguration(data);

        Debug::Debugging::SetConfiguration(debugConfig);
        Debug::Logging::SetConfiguration(loggingConfig);

        Debug::Logging::Log("[Project]: Loading scene from " + path, Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);

        // Load scripts name only.
        this->scriptManager->LoadScriptNames(this->GetAssetsPath());

        // Load gos of the scene
        this->goManager->Load(data);

        this->isModified = false;
    }

    void Project::SetDirty()
    {
        if (this->GetState() == ProjectState::Idle)
            this->isModified = true;
    }

    bool Project::isDirty() const
    {
        return this->isModified;
    }

    void Project::SetName(const std::string& name)
    {
        this->name = name;
    }

    std::string Project::GetName() const
    {
        return this->name;
    }

    void Project::SetPath(const std::string& path)
    {
        this->path = path;
    }

    std::string Project::GetBasePath() const
    {
        return this->path;
    }

    std::string Project::GetAssetsPath() const
    {
        return this->GetBasePath() + '/' + "Assets";
    }

    std::string Project::GetLogsPath() const
    {
        return this->GetBasePath() + '/' + "Logs";
    }

    std::string Project::GetProjectSettingsPath() const
    {
        return this->GetBasePath() + '/' + "project.cvproj";
    }

    void Project::SetScreenLimits(glm::vec2 start, glm::vec2 end)
    {
        this->data.topLeft = start;
        this->data.bottomRight = end;
    }

    glm::vec4 Project::GetScreenLimits() const
    {
        return glm::vec4(this->data.topLeft, this->data.bottomRight);
    }

    ProjectState Project::GetState() const
    {
        return this->state;
    }

    void Project::Start()
    {
        if(state == ProjectState::Idle)
            this->state = ProjectState::Loading;
    }

    void Project::Stop()
    {
        if (state == ProjectState::Running)
            this->state = ProjectState::Stoping;
    }

    void Project::Reload()
    {
        if (state == ProjectState::Idle)
            this->state = ProjectState::Stoping;
    }

    void Project::Execute()
    {
        this->CalculateMetrics();

        if (this->state == ProjectState::Idle)
            return;

        bool hasError = false;
        if (this->state == ProjectState::Loading)
        {
            Debug::Logging::Log("[Project]: Starting scene", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
            
            // load scripts names and paths
            if (!this->scriptManager->LoadLuaAndScriptsPath(this->GetAssetsPath()))
            {
                Debug::Logging::Log("[Project]: Running scene", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
                this->state = ProjectState::Running;
            }
            else
            {
                Debug::Logging::Log("[Project]: Failed to start. Fix errors", Debug::LogSeverity::Error, Debug::LogOrigin::Engine);
                hasError = true;
                this->state = ProjectState::Stoping;
            }
        }

        if (this->state == ProjectState::Running)
        {
            // Execution returned
            std::vector<GoExecution> executions;
            executions.reserve(GameObject::GetCurrentGosCount() * Script::GetCurrentScriptsCount());

            // Plan and then execute
            this->PlanExecution(this->goManager->GetRootGameObjects(), executions);
            
            if (!this->Execute(executions))
            {
                this->state = ProjectState::Stoping;
                hasError = true;
            }
        }

        if (this->state == ProjectState::Stoping)
        {
            using json = nlohmann::json;
        
            auto& root = this->goManager->GetRootGameObjects();
            
            // Destroy scripts (call destroy if without error)
            this->scriptManager->DestroyAllScripts(hasError, root);

            // Also here destroy the gos (script ref go with this).
            this->goManager->Unload();

            if (hasError)
                Debug::Logging::Log("[Project]: Stopped with errors. Now in idle", Debug::LogSeverity::Error, Debug::LogOrigin::Engine);
            else
                Debug::Logging::Log("[Project]: Stopped. Now in idle", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);

            if(GameObject::GetCurrentGosCount() != 0)
                Debug::Logging::Log("[Project]: Assertion Failed. Leaked Gos!", Debug::LogSeverity::Error, Debug::LogOrigin::Engine);

            if (Script::GetCurrentScriptsCount() != 0)
                Debug::Logging::Log("[Project]: Assertion Failed. Leaked Scripts!", Debug::LogSeverity::Error, Debug::LogOrigin::Engine);

            // Reload the original scene
            this->isModified = false;
            std::string rawJson = Utils::Directory::ReadFile(this->GetProjectSettingsPath());
            json data = json::parse(rawJson);

            // Carrega somente todos scripts disponiveis, somente nomes.
            this->scriptManager->LoadScriptNames(this->GetAssetsPath());
            // Aqui re/carrega os gameobjects no seu estado inicial
            this->goManager->Load(data);
            
            this->state = ProjectState::Idle;
        }
    }

    ProjectPtr Project::GetCurrentProject()
    {
        if (current.expired())
            return nullptr;
        else
            return current.lock();
    }

    void Project::SetCurrentProject(ProjectPtr project)
    {
        current = project;
    }

    std::vector<std::string>& Project::GetScriptNamesForEditor() const
    {
        return this->scriptManager->GetScriptsNames();
    }

    void Project::LoadScriptNameListForEditor() const
    {
        this->scriptManager->LoadScriptNames(this->GetAssetsPath());
    }

    void Project::AddGameObjectInEditor(const std::string& name, const std::string& fatherId)
    {
        this->isModified = true;
        this->goManager->AddGameObject(name, true, fatherId);
    }

    void Project::RemoveGameObjectInEditor(const std::string& goId)
    {
        this->isModified = true;
        this->goManager->RemoveGameObjectReferences(goId);
    }

    GameObjectPtr Project::AddGameObject(const std::string& name, bool active, const std::string& fatherId)
    {
        return this->goManager->AddGameObject(name, active, fatherId);
    }

    bool Project::DestroyGameObject(const std::string& id)
    {
        return this->goManager->RemoveGameObject(id);
    }

    GameObjectPtr Project::GetGameObject(const std::string& id)
    {
        return this->goManager->GetGameObject(id);
    }

    bool Project::AddScript(const std::string& goId, const std::string& scriptName)
    {
        return this->scriptManager->AddScript(this->goManager->GetGameObject(goId), scriptName);
    }

    bool Project::DestroyScript(const std::string& goId, const std::string& scriptName)
    {
        return this->scriptManager->DestroyScript(this->goManager->GetGameObject(goId), scriptName);
    }

    std::vector<GameObjectPtr> Project::GetGosFromRoot() const
    {
        return this->goManager->GetRootGameObjects();
    }

    int Project::GetCurrentFPS()
    {
        return this->data.fps;
    }

    double Project::GetCurrentFrameTime()
    {
        return this->data.frameTime;
    }

    void Project::CalculateMetrics()
    {
        // Calculate fps and frametime
        if (Utils::Time::GetTimestamp() > this->data.currentTime + 1)
        {
            this->data.fps = this->data.fpsCounter;
            this->data.fpsCounter = 0;
            this->data.currentTime = Utils::Time::GetTimestamp();
        }
        else
            this->data.fpsCounter++;

        this->data.frameTime = (Utils::Time::GetTimestamp() - this->data.lastFrameTime) * 1000;
        this->data.lastFrameTime = Utils::Time::GetTimestamp();
    }

    int Project::GetStackSize()
    {
        return this->scriptManager->GetStackSize();
    }

    GPU::FramebufferPtr Project::GetCurrentFramebuffer() const
    {
        return this->data.current.lock();
    }

    void Project::SetCurrentFramebuffer(GPU::FramebufferPtr framebuffer) 
    {
        this->data.current = framebuffer;
    }

    void Project::PlanExecution(const std::vector<GameObjectPtr>& gos, std::vector<GoExecution>& executions)
    {
        for (const GameObjectPtr go : gos)
        {
            // If the go is inactive and not marked to visit
            if (!go->GetActive() && !go->IsToVisit())
                continue;

            go->SetToVisit(false);

            // If destroy execution is diferent
            if (go->IsToDestroy())
            {
                PlanExecutionToDestroy({go}, executions);
                this->scriptManager->GetScriptsExecution(go, executions);
            }
            else
            {
                // Get execution for scripts
                this->scriptManager->GetScriptsExecution(go, executions);
                PlanExecution(go->GetChildrens(), executions);
            }
        }
    }

    void Project::PlanExecutionToDestroy(const std::vector<GameObjectPtr> gos, std::vector<GoExecution>& executions)
    {
        for (const GameObjectPtr go : gos)
        {
            // Destroy from leaf
            PlanExecutionToDestroy(go->GetChildrens(), executions);

            // Destroy scripts in reverse order
            auto childrensInReverse = go->GetScripts();
            std::reverse(go->GetScripts().begin(), go->GetScripts().end());

            for (const ScriptPtr script : childrensInReverse)
            {
                // Only call destroy if has been initilizated
                if (script->IsStarted())
                {
                    std::string command = script->GetName() + ".destroy()";
                    executions.push_back(GoExecution(go, script, command));
                }
            }

            // Actually destroy the go
            auto exec = GoExecution(go, nullptr, "");
            exec.SetIsDestroy(true);
            executions.push_back(exec);
        }
    }

    bool Project::Execute(const std::vector<GoExecution>& executions)
    {
        // Gos to remove
        std::set<GameObjectPtr> toRemove;
        for (const GoExecution& exec : executions)
        {
            // Execute scripts
            if (exec.GetScript() != nullptr && !this->scriptManager->ExecuteScript(exec))
                return false;

            // if destroy save to remove refs later
            if (exec.IsDestroyed())
                toRemove.insert(exec.GetGo());
        }

        // Remove destroyed gos.
        for (const GameObjectPtr item : toRemove)
            this->goManager->RemoveGameObjectReferences(item);

        return true;
    }
}}