#include <BoxEngine.hpp>
#include "ScriptManager.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {

	bool ScriptManager::LoadScriptNames(const std::string& basePath)
	{
		bool hasError = false;

		// Clear old information
		this->paths.clear();
		this->list.clear();

		// Load new paths
		this->LoadScriptsPaths(basePath, hasError);
		
		// Add script names
		for (const auto& item : this->paths)
			this->list.emplace_back(item.first);
		
		return hasError;
	}

	std::vector<std::string>& ScriptManager::GetScriptsNames()
	{
		return this->list;
	}

	bool ScriptManager::LoadLuaAndScriptsPath(const std::string& basePath)
	{
		// Load lua context 
		this->state = lua_open();
		luaL_openlibs(this->state);

		// Load connection between lua and c++
		this->connectionManager = ConnectionManagerPtr(new ConnectionManager(this->state));
		this->connectionManager->Bind();

		// Read again the scripts at runtime, with paths. If repeated gives error and stops initialization.
		if (this->LoadScriptNames(basePath))
			return true;

		return false;
	}

	void ScriptManager::DestroyAllScripts(bool hasError, std::vector<GameObjectPtr>& root)
	{
		// Clear the loaded scripts names
		this->loaded.clear();

		// Unload all scripts from lua, is error stops all
		if (!hasError)
			this->RecursiveUnloadAllScripts(root, hasError);

		// Clear lua context
		if(this->state != nullptr)
			lua_close(this->state);

		// Release connection with lua
		this->connectionManager = nullptr; 
		this->state = nullptr;
	}

	void ScriptManager::GetScriptsExecution(const GameObjectPtr go, std::vector<GoExecution>& executions , ProjectMode mode)
	{
		auto& scripts = go->GetScripts();
		
		// Plan execution for scripts of this go
		for (ScriptPtr script : scripts)
		{
			bool isActive = go->GetActive() && script->GetActive();

			if (script->GetRunMode() == RunMode::PlayModeDestroyed && mode == ProjectMode::PlayMode)
				isActive = false;

			if (script->GetRunMode() == RunMode::EditorModeDestroyed && mode == ProjectMode::EditorMode)
				isActive = false;

			if (script->GetRunMode() == RunMode::PlayModeRemoved && mode == ProjectMode::PlayMode)
			{
				script->SetState(ScriptState::ToDestroy);
				script->SetRemovedAfterDestroyed(true);
			}

			if (script->GetState() == ScriptState::ToLoad && isActive)
				executions.push_back(GoExecution(go, script, ""));
			else if (script->GetState() == ScriptState::ToStart && isActive)
			{
				std::string command = script->GetName() + ".start()";
				executions.push_back(GoExecution(go, script, command));
			}
			else if (script->GetState() == ScriptState::Updating && isActive)
			{
				std::string command = script->GetName() + ".update()";
				executions.push_back(GoExecution(go, script, command));
			}
			else if (script->GetState() == ScriptState::ToDestroy)
			{
				std::string command = script->GetName() + ".destroy()";
				executions.push_back(GoExecution(go, script, command));
			}
		}
	}

	bool ScriptManager::ExecuteScript(const GoExecution& execution, bool setAsCurrent)
	{
		// Execute a plan for the scripts
		auto script = execution.GetScript();
		auto go = execution.GetGameObject();
		auto state = script->GetState();

		if (setAsCurrent)
		{
			this->connectionManager->SetCurrentGo(go);
			this->connectionManager->SetCurrentScript(script);
		}

		// Check if needs to be loaded
		if (state == ScriptState::ToLoad)
		{
			auto scriptName = script->GetName();

			// Check if it is already loaded
			bool isLoaded = std::find_if(this->loaded.begin(), this->loaded.end(), [scriptName](const std::string& item) { return item == scriptName; }) != this->loaded.end();

			// Then schedule to start
			if (isLoaded)
			{
				script->SetState(ScriptState::ToStart);
				script->SetPath(this->paths[scriptName]);

				// Register go instance data
				this->connectionManager->CreateScriptData(go, script);
			}
			else
			{
				// If needs to load then read the code
				if (!this->paths.contains(scriptName))
				{
					// In case dont find it
					Debug::Logging::Log(
						"[Project]: Script " + script->GetName() + " not founded when loading in go " + go->GetId(),
						Debug::LogSeverity::Error,
						Debug::LogOrigin::Engine,
						{ {"go_id", go->GetId()}, {"script_name", script->GetName()} }
					);

					return false;
				}
				else
				{
					// init table with empty functions
					lua_newtable(this->state);
					lua_setglobal(this->state, script->GetName().c_str());
					luaL_dostring(this->state, ("function " + script->GetName() + ".start() end").c_str());
					luaL_dostring(this->state, ("function " + script->GetName() + ".update() end").c_str());
					luaL_dostring(this->state, ("function " + script->GetName() + ".destroy() end").c_str());

					// Read content and execute.
					std::string file = Utils::Directory::ReadFile(this->paths[scriptName]);

					if (luaL_dostring(this->state, file.c_str()))
					{
						Debug::Logging::Log("[Project]: Error when loading script "
							+ script->GetName() + ": " +
							lua_tostring(this->state, -1) + " in go " + go->GetId(),
							Debug::LogSeverity::Error,
							Debug::LogOrigin::Engine,
							{ {"go_id", go->GetId()}, {"script_name", script->GetName()} }
						);

						return false;
					}

					script->SetState(ScriptState::ToStart);
					script->SetPath(this->paths[scriptName]);

					// Register go instance data
					this->connectionManager->CreateScriptData(go, script);

					this->loaded.push_back(scriptName);
				}
			}
		}
		else
		{
			// Execute script plan
			auto command = execution.GetCommand();

			// Loaded mean that everything is ready to start executing any commands
			// This is made mainly becausa a script can be destroyed before it even started/loaded
			if (script->IsLoaded())
			{	
				if (luaL_dostring(this->state, command.c_str()))
				{
					Debug::Logging::Log("[Project]: Error in Script " +
						script->GetName() + ": " + command + " = " +
						lua_tostring(this->state, -1) + " in go " + go->GetId(),
						Debug::LogSeverity::Error,
						Debug::LogOrigin::Engine,
						{ {"go_id", go->GetId()}, {"script_name", script->GetName()} }
					);

					return false;
				}
			}

			// Change states
			if (state == ScriptState::ToStart)
				script->SetState(ScriptState::Updating);
			else if (state == ScriptState::ToDestroy)
			{
				script->SetState(ScriptState::Destroyed);
				
				if(script->IsLoaded())
					this->connectionManager->DeleteScriptData(go, script);

				if (script->IsRemovedAfterDestroyed())
					go->RemoveScript(script);
			}
		}
		
		return true;
	}

	bool ScriptManager::AddScript(GameObjectPtr go, const std::string& scriptName)
	{
		// Set script to be add in go.
		if (go != nullptr)
		{
			if (go->IsToDestroy())
			{
				Debug::Logging::Log(
					"[Project]: Can't add script " + scriptName + " to go " + go->GetId() + " because its destroyed",
					Debug::LogSeverity::Error,
					Debug::LogOrigin::Engine,
					{ {"go_id", go->GetId()}, {"script_name", scriptName} }
				);
			}

			ScriptPtr script = ScriptPtr(new Script(scriptName));
			return go->AddScript(script);
		}
		else
		{
			Debug::Logging::Log(
				"[Project]: Can't find go " + go->GetId() + " to add script " + scriptName, 
				Debug::LogSeverity::Error, 
				Debug::LogOrigin::Engine,
				{ {"go_id", go->GetId()}, {"script_name", scriptName} }
			);

			return false;
		}
	}

	bool ScriptManager::DestroyScript(GameObjectPtr go, const std::string& scriptName, bool remove)
	{
		// Set script to be destroyed
		if (go != nullptr)
		{
			for (auto script : go->GetScripts())
			{
				if (script->GetName() == scriptName)
				{
					if (script->GetState() == ScriptState::Destroyed && remove)
					{
						go->RemoveScript(script);
					}
					else
					{
						script->SetRemovedAfterDestroyed(remove);
						script->SetState(ScriptState::ToDestroy);
					}
					
					return true;
				}
			}
		}
		else
			Debug::Logging::Log(
				"[Project]: Can't find go " + go->GetId() + " to destroy script " + scriptName, 
				Debug::LogSeverity::Error, 
				Debug::LogOrigin::Engine,
				{ {"go_id", go->GetId()}, {"script_name", scriptName} }
			);
	
		return false;
	}

	bool ScriptManager::PreLoadScripts(GameObjectPtr go)
	{
		if (go != nullptr)
		{
			for (auto script : go->GetScripts())
			{
				GoExecution exec = GoExecution(go, script, "");
				if (script->GetState() == ScriptState::ToLoad && script->GetActive() && !this->ExecuteScript(exec, false))
					return false;
			}

			for (GameObjectPtr child : go->GetChildrens())
			{
				if (!PreLoadScripts(child))
					return false;
			}
		}

		return true;
	}

	void ScriptManager::UpdateScriptData(GameObjectPtr go)
	{
		for (const auto& script : go->GetScripts())
			this->connectionManager->UpdateScriptData(go, script);
	}

	void ScriptManager::UpdateAllScriptDataToSave(std::vector<GameObjectPtr> gos)
	{
		for (const auto& go : gos)
		{
			for (const auto& script : go->GetScripts())
				this->connectionManager->UpdateScriptData(go, script);
		}
	}

	int ScriptManager::GetStackSize()
	{
		if(this->connectionManager != nullptr)
			return this->connectionManager->GetStackSize();

		return 0;
	}

	std::unordered_map<long, Modules::GPU::TexturePtr> ScriptManager::GetTextures()
	{
		if (this->connectionManager == nullptr)
			return std::unordered_map<long, Modules::GPU::TexturePtr>();

		return this->connectionManager->GetTextures();
	}

	lua_State* ScriptManager::GetState()
	{
		return this->state;
	}

	#pragma region InternalFunctions

	void ScriptManager::LoadScriptsPaths(const std::string& basePath, bool& error)
	{
		// Load scripts names and paths from path (assets path)
		for (const std::string& file : Utils::Directory::ListDirectories(basePath, false))
		{
			auto fileName = Utils::Directory::GetLastPartFromPathNoExtension(file);
			auto extension = Utils::Directory::GetExtensionFromPath(file);

			if (fileName == "engine" && extension == "lua")
				continue;

			if (Utils::Directory::IsDirectory(file))
				LoadScriptsPaths(file, error);
			else if (extension == "lua" && this->paths.contains(fileName))
			{
				error = true;

				Debug::Logging::Log(
					"[Project]: Script with name " + fileName + " already exists.", 
					Debug::LogSeverity::Error, 
					Debug::LogOrigin::Engine
				);

				return;
			}
			else if(extension == "lua")
				this->paths[fileName] = file;
		}
	}

	void ScriptManager::RecursiveUnloadAllScripts(const std::vector<GameObjectPtr> gos, bool& error)
	{
		for (GameObjectPtr go : gos)
		{
			RecursiveUnloadAllScripts(go->GetChildrens(), error);
		
			if (error)
				return;

			auto scripts = go->GetScripts();
			std::reverse(scripts.begin(), scripts.end());

			if(this->connectionManager != nullptr)
				this->connectionManager->SetCurrentGo(go);

			for (ScriptPtr script : scripts)
			{
				if (this->connectionManager != nullptr)
					this->connectionManager->SetCurrentScript(script);

				// Only call destroy if has been initilizated
				if (script->IsStarted() && script->GetState() != ScriptState::Destroyed)
				{
					auto command = script->GetName() + ".destroy()";

					if (luaL_dostring(this->state, command.c_str()))
					{
						Debug::Logging::Log("[Project]: Error in Script " +
							script->GetName() + ": " + command + " = " +
							lua_tostring(this->state, -1) + " in go " + go->GetId(),
							Debug::LogSeverity::Error,
							Debug::LogOrigin::Engine,
							{ {"go_id", go->GetId()}, {"script_name", script->GetName()} }
						);

						error = true;
						break;
					}
					else
						script->SetState(ScriptState::Destroyed);
				}
			}
		}
	}

	#pragma endregion
}}}
