#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Serialization {

    /// <summary>
    /// Serialize debug configuration.
    /// </summary>
    static nlohmann::json Serialize(const Debug::DebugConfiguration& config)
	{
        using json = nlohmann::json;
        using namespace BoxEngine::Utils;

        nlohmann::basic_json debugObj = json::object(
        {
            {"autoLogGLFWErrors", config.autoLogGLFWErrors},
            {"autoLogOpenGLErrors", config.autoLogOpenGLErrors},
            {"enableGlfwDebugging", config.enableGlfwDebugging},
            {"enableOpenGLDebugging", config.enableOpenGLDebugging},
            {"openglSeverities", config.openGlSeverities},
        });

        return debugObj;
	}

    /// <summary>
    /// Deserialize debug configuration.
    /// </summary>
    static Debug::DebugConfiguration DeserializeDebugConfiguration(const nlohmann::json& data)
    {
        using json = nlohmann::json;
        using namespace BoxEngine::Utils;

        auto debugConfig = Debug::DebugConfiguration();

        if (data.contains("debug"))
        {
            auto obj = data["debug"];

            if (obj.contains("autoLogGLFWErrors"))
                debugConfig.autoLogGLFWErrors = obj["autoLogGLFWErrors"];
            if (obj.contains("enableGlfwDebugging"))
                debugConfig.enableGlfwDebugging = obj["enableGlfwDebugging"];
            if (obj.contains("enableOpenGLDebugging"))
                debugConfig.enableOpenGLDebugging = obj["enableOpenGLDebugging"];
            if (obj.contains("openglSeverities"))
            {
                debugConfig.openGlSeverities.clear();
                for (auto& item : obj["openglSeverities"].items())
                    debugConfig.openGlSeverities.insert((Debug::OpenGlErrorSeverity)item.value());
            }
        }
      
        return debugConfig;
    }

    /// <summary>
    /// Serialize logging configuration.
    /// </summary>
    static nlohmann::json Serialize(const Debug::LoggingConfiguration& config)
    {
        using json = nlohmann::json;
        using namespace BoxEngine::Utils;

        nlohmann::basic_json loggingObj = json::object(
        {
            {"logCallback", config.logCallback},
            {"logConsole", config.logConsole},
            {"logFile", config.logFile},
        });

        return loggingObj;
    }

    /// <summary>
    /// Deserialize logging configuration.
    /// </summary>
    static Debug::LoggingConfiguration DeserializeLoggingConfiguration(const nlohmann::json& data)
    {
        using json = nlohmann::json;
        using namespace BoxEngine::Utils;

        auto loggingConfig = Debug::LoggingConfiguration();

        if (data.contains("logging"))
        {
            auto obj = data["logging"];

            if (obj.contains("logCallback"))
                loggingConfig.logCallback = obj["logCallback"];
            if (obj.contains("logConsole"))
                loggingConfig.logConsole = obj["logConsole"];
            if (obj.contains("logFile"))
                loggingConfig.logFile = obj["logFile"];
        }

        return loggingConfig;
    }

    /// <summary>
    /// Serializa script data.
    /// </summary>
    static nlohmann::json SerializeScriptsData(std::vector<Project::ScriptData>& scriptData)
    {
        using namespace Project;
        using json = nlohmann::json;

        nlohmann::basic_json arr = json::array();

        for (ScriptData& data : scriptData)
        {
            nlohmann::basic_json obj = json::object(
            {
                {"name", data.GetName()},
                {"type", data.GetType()},
                {"value", data.GetValue()},
            });

            arr.push_back(obj);
        }

        return arr;
    }

    /// <summary>
    /// Deserialize scripts.
    /// </summary>
    static std::vector<Project::ScriptPtr> DeserializeScript(const nlohmann::json& data)
    {
        using namespace Project;
        using json = nlohmann::json;

        std::vector<ScriptPtr> scripts;
        for (auto scriptItem : data.items())
        {
            auto scriptObj = scriptItem.value();

            ScriptPtr script = ScriptPtr(new Script(scriptObj["name"]));

            std::vector<ScriptData> data;
            for (auto dataItem : scriptObj["data"].items())
            {
                auto dataObj = dataItem.value();

                data.push_back(ScriptData(dataObj["name"], dataObj["value"], dataObj["type"]));
            }

            script->SetScriptData(data);
            scripts.push_back(script);
        }

        return scripts;
    }

    /// <summary>
    /// Serializa scripts
    /// </summary>
    static nlohmann::json SerializeScripts(const std::vector<Project::ScriptPtr>& scripts)
    {
        using namespace Project;
        using json = nlohmann::json;

        nlohmann::basic_json arr = json::array();
        
        for (const ScriptPtr& script : scripts)
        {
            nlohmann::basic_json obj = json::object(
            {
                {"name", script->GetName()},
                {"data", SerializeScriptsData(script->GetScriptData())}
            });

            arr.push_back(obj);
        }

        return arr;
    }

    /// <summary>
    /// Serialize entities of project.
    /// </summary>
    static nlohmann::json SerializeGo(const std::vector<Project::GameObjectPtr>& gos)
    {
        using json = nlohmann::json;
        using namespace BoxEngine::Utils;

        nlohmann::basic_json arr = json::array();

        for (const Project::GameObjectPtr& go : gos)
        {
            nlohmann::basic_json obj = json::object(
            {
                {"id", go->GetId()},
                {"name", go->GetName()},
                {"active", go->GetActive()},
                {"childrens", SerializeGo(go->GetChildrens())},
                {"scripts", SerializeScripts(go->GetScripts())}
            });

            arr.push_back(obj);
        }

        return arr;
    }

    /// <summary>
    /// Deserialize entities and insert into current project.
    /// </summary>
    static void DeserializeGo(const nlohmann::json& data, const std::string& fatherId, Project::CreateGoFunction createGo)
    {
        using json = nlohmann::json;
        using namespace BoxEngine::Utils;

        for (auto item : data.items())
        {
            auto obj = item.value();
            auto scripts = DeserializeScript(obj["scripts"]);

            createGo(obj["id"], obj["name"], obj["active"], scripts, fatherId);

            DeserializeGo(obj["childrens"], obj["id"], createGo);
        }
    }
}}