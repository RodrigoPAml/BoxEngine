#include <BoxEngine.hpp>
#include "GoManager.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {

    void GoManager::Load(nlohmann::json& data)
    {
        using namespace Utils;
        using namespace std::placeholders;

        Debug::Logging::Log("[Project]: Loading gos", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
        Serialization::DeserializeGo(data["scene"], "", std::bind(&GoManager::AddGameObjectFromFile, this, _1, _2, _3, _4, _5));
    }

    void GoManager::Unload()
    {
        // Remove all references
        this->gosMap.clear();
        
        // Remove recursive
        this->RecursiveRemoveGos(this->gos);
        
        // Remove root
        this->gos.clear();
    }

    std::vector<GameObjectPtr>& GoManager::GetRootGameObjects()
    {
        return this->gos;
    }

    GameObjectPtr GoManager::GetGameObject(const std::string& id)
    {
        if (this->gosMap.contains(id))
            return this->gosMap[id];

        return nullptr;
    }

    GameObjectPtr GoManager::AddGameObject(const std::string& name, bool active, const std::string& fatherId)
    {
        GameObjectPtr newGo = GameObjectPtr(new GameObject());
        GameObjectPtr fatherGo = nullptr;

        newGo->id = this->NewGoId();
        newGo->name = name.size() == 0 ? "New Game Object" : name;
        newGo->active = active;
        newGo->toDestroy = false;

        if (fatherId.size() > 0)
        {
            if (this->gosMap.contains(fatherId))
            {
                fatherGo = this->gosMap.at(fatherId);

                if (fatherGo->IsToDestroy())
                {
                    Debug::Logging::Log(
                        "[Project]: When creating go " + name + ": father with id " + fatherId + " is set to be destroyed", 
                        Debug::LogSeverity::Error, 
                        Debug::LogOrigin::Engine,
                        {{"father_id", fatherId}}
                    );

                    return nullptr;
                }
            }
            else
            {
                Debug::Logging::Log(
                    "[Project]: When creating go " + name + ": Can't find father with id " + fatherId, 
                    Debug::LogSeverity::Error, 
                    Debug::LogOrigin::Engine,
                    { {"father_id", fatherId} }
                );
                return nullptr;
            }
        }

        newGo->SetFather(fatherGo);

        if (fatherGo != nullptr)
            fatherGo->childrens.emplace_back(newGo);
        else
            this->gos.emplace_back(newGo);

        this->gosMap[newGo->id] = newGo;

        return newGo;
    }

    bool GoManager::RemoveGameObject(const std::string& id)
    {
        if (this->gosMap.contains(id))
            RemoveGameObject(this->gosMap[id]);
        else
        {
            Debug::Logging::Log(
                "[Project]: Can't find go with id " + id + " to be destroyed.", 
                Debug::LogSeverity::Warning,
                Debug::LogOrigin::Engine,
                { {"go_id", id} }
            );
            return false;
        }

        return true;
    }

    void GoManager::RemoveGameObject(GameObjectPtr go)
    {
        go->SetToDestroy();
    }

    void GoManager::ChangeGoFather(const std::string& id, const std::string& fatherId)
    {
        if (this->gosMap.contains(id))
        {
            if (fatherId != "" && !this->gosMap.contains(fatherId))
                return;

            GameObjectPtr go = this->gosMap[id];
            GameObjectPtr oldFather = go->GetFather();
            GameObjectPtr newFather = this->gosMap[fatherId];

            if (this->IsDegreeFather(newFather, go))
            {
                Debug::Logging::Log("[Project]: Can't change go father with id " + id + " because they already are family.", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine, { {"go_id", id}, {"father_id", fatherId} });
                return;
            }

            if (go->IsToDestroy())
            {
                Debug::Logging::Log("[Project]: Can't change go father with id " + id + " because it's destroyed.", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine, { {"go_id", id}, {"father_id", fatherId} });
                return;
            }

            if (newFather != nullptr && newFather->IsToDestroy())
            {
                Debug::Logging::Log("[Project]: Can't change go father with id " + id + " because new father is destroyed.", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine, { {"go_id", id}, {"father_id", fatherId} });
                return;
            }

            if (oldFather != nullptr)
            {
                auto& childrens = oldFather->GetChildrens();
                childrens.erase(std::remove(childrens.begin(), childrens.end(), go), childrens.end());
            }
            else
                this->gos.erase(std::remove(this->gos.begin(), this->gos.end(), go), this->gos.end());

            go->SetFather(newFather);

            if (newFather != nullptr)
                newFather->GetChildrens().emplace_back(go);
            else this->gos.emplace_back(go);
        }
        else
        {
            Debug::Logging::Log("[Project]: Can't change go father with id " + id + " because this go dont exists.", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine, { {"go_id", id} });
            return;
        }
    }

    void GoManager::ChangeGoPosition(const std::string& id, int displacement)
    {
        if (this->gosMap.contains(id))
        {
            GameObjectPtr go = this->gosMap[id];

            if (go->IsToDestroy())
            {
                Debug::Logging::Log("[Project]: Can't change go position with id " + id + " because it's destroyed.", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine, { {"go_id", id} });
                return;
            }
            
            auto& arr = go->GetFather() != nullptr ? go->GetFather()->GetChildrens() : this->gos;

            if (arr.size() <= 1)
                return;

            auto it = std::find(arr.begin(), arr.end(), go);

            if (it == arr.end())
                return;

            int oldIndex = it - arr.begin();

            int newPos = oldIndex + displacement;
            newPos = std::min((int)arr.size() - 1, newPos);
            newPos = std::max(newPos, 0);

            auto old = arr[newPos];
            arr[newPos] = go;
            arr[oldIndex] = old;
        }
    }

    void GoManager::ChangeScriptPosition(const std::string& id, const std::string& scriptName, int displacement)
    {
        if (this->gosMap.contains(id))
        {
            GameObjectPtr go = this->gosMap[id];
            ScriptPtr script = nullptr;

            if (go->IsToDestroy())
            {
                Debug::Logging::Log("[Project]: Can't change go script position with id " + id + " because it's destroyed.", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine, { {"go_id", id}});
                return;
            }

            for(auto item : go->GetScripts())
            {
                if (item->GetName() == scriptName)
                {
                    script = item;
                    break;
                }
            }

            auto& arr = go->GetScripts();

            if (arr.size() <= 1)
                return;

            auto it = std::find(arr.begin(), arr.end(), script);

            if (it == arr.end())
                return;

            int oldIndex = it - arr.begin();

            int newPos = oldIndex + displacement;
            newPos = std::min((int)arr.size() - 1, newPos);
            newPos = std::max(newPos, 0);

            auto old = arr[newPos];
            arr[newPos] = script;
            arr[oldIndex] = old;
        }
    }

    void GoManager::RemoveGameObjectReferences(GameObjectPtr go)
    {
        RemoveGameObjectReferences(go->GetId());
    }

    void GoManager::RemoveGameObjectReferences(const std::string& id)
    {
        // Era ref from father or root, and then the childrens
        if (this->gosMap.contains(id))
        {
            auto go = this->gosMap[id];
            auto father = go->GetFather();

            if (father == nullptr)
            {
                std::erase_if(this->gos, [&go](const auto& item) {
                    return item->GetId() == go->GetId();
                });
            }
            else
            {
                std::erase_if(go->GetFather()->GetChildrens(), [&go](const auto& item) {
                    return item->GetId() == go->GetId();
                });
            }

            this->gosMap.erase(id);
            
            // Then just erase the remaining.
            RecursiveRemoveGos(go->childrens);
            go->childrens.clear();
        }
    }

    std::string GoManager::DuplicateGo(const std::string& id, const std::string fatherId, bool isFirst)
    {
        if (this->gosMap.contains(id))
        {
            GameObjectPtr go = this->gosMap[id];
         
            if (isFirst && RecursiveCheckDestroyed(go))
            {
                Debug::Logging::Log("[Project]: Can't duplicate go with id " + id + " because him or its childrens are destroyed.", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine, { {"go_id", id} });
                return  "";
            }
            
            GameObjectPtr newGo = this->AddGameObject(go->GetName(), go->GetActive(), fatherId);

            for (const ScriptPtr script : go->GetScripts())
            {
                ScriptPtr newScript = ScriptPtr(new Script(script->GetName()));
                newScript->SetScriptData(script->GetScriptData());
                
                newGo->AddScript(newScript);
            }

            for (const GameObjectPtr child : go->GetChildrens())
                DuplicateGo(child->GetId(), newGo->GetId(), false);

            return newGo->GetId();
        }

        return "";
    }

    #pragma region InternalFunctions

    void GoManager::AddGameObjectFromFile(
        const std::string& id, 
        const std::string& name, 
        bool active, 
        const std::vector<ScriptPtr>& scripts,
        const std::string fatherId
    )
    {
        GameObjectPtr newGo = GameObjectPtr(new GameObject());
        GameObjectPtr fatherGo = nullptr;

        newGo->name = name.size() == 0 ? "New Game Object" : name;
        newGo->id = id;
        newGo->active = active;
        newGo->scripts = scripts;

        auto scriptsList = Project::GetCurrentProject()->GetScriptNamesForEditor();
        for (const auto& script : scripts)
        {
            if (std::find_if(
                scriptsList.begin(), 
                scriptsList.end(), 
                [&script](const auto& x) { return x == script->GetName(); }) == scriptsList.end()
             )
            {
                script->MarkAsFailedToLoad();
                Debug::Logging::Log("[Project]: When loading go " + name + " with id " + id + " script " + script->GetName() + " not founded!", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine, { {"go_id", id}});
            }
        }

        if (this->gosMap.contains("id"))
        {
            Debug::Logging::Log("[Project]: Go " + name + " with id " + id + " already exists. It will be ignored with it childrens.", Debug::LogSeverity::Error, Debug::LogOrigin::Engine, { {"go_id", id} });
            return;
        }

        if (fatherId.size() > 0)
        {
            if (this->gosMap.contains(fatherId))
                fatherGo = this->gosMap.at(fatherId);
            else
            {
                Debug::Logging::Log("[Project]: Failed to create go " + name + ": Can't find father with id " + fatherId, Debug::LogSeverity::Error, Debug::LogOrigin::Engine, { {"go_id", id}, {"father_id", fatherId} });
                return;
            }
        }

        newGo->SetFather(fatherGo);

        if (fatherGo != nullptr)
            fatherGo->childrens.emplace_back(newGo);
        else
            this->gos.emplace_back(newGo);

        this->gosMap[newGo->id] = newGo;
    }

    void GoManager::RecursiveRemoveGos(std::vector<GameObjectPtr>& gos)
    {
        for (const GameObjectPtr& go : gos)
        {
            this->gosMap.erase(go->GetId());
            RecursiveRemoveGos(go->GetChildrens());
            gos.clear();
        }
    }

    std::string GoManager::NewGoId()
    {
        std::string id = Utils::Directory::NewGuid().substr(0, 10);

        while (true)
        {
            if (!this->gosMap.contains(id))
                break;

            id = Utils::Directory::NewGuid().substr(0, 10);
        }

        return id;
    }

    bool GoManager::IsDegreeFather(GameObjectPtr go, GameObjectPtr possibleFather)
    {
        if (go == nullptr)
            return false;

        if (possibleFather == nullptr)
            return false;

        auto father = go->GetFather();

        while (father != nullptr)
        {
            if (father == possibleFather)
                return true;
            else
                father = father->GetFather();
        }
            
        return false;
    }

    bool GoManager::RecursiveCheckDestroyed(GameObjectPtr go)
    {
        if (go->IsToDestroy())
            return true;

        for (GameObjectPtr child : go->GetChildrens())
        {
            if (RecursiveCheckDestroyed(child))
                return true;
        }

        return false;
    }
    
    #pragma endregion
}}}