#include <BoxEngine.hpp>
#include "ScriptManager.hpp"

namespace BoxEngine {
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
			this->list.push_back(item.first);
		
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

	void ScriptManager::GetScriptsExecution(const GameObjectPtr go, std::vector<GoExecution>& executions)
	{
		auto& scripts = go->GetScripts();
		bool isToDestroy = go->IsToDestroy();

		// Plan execution for scripts of this go
		for (ScriptPtr script : scripts)
		{
			// if go is set to be destroyed and have been started, we need to call the destroy any way.
			if (isToDestroy)
			{
				if (script->IsStarted())
				{
					std::string command = script->GetName() + ".destroy()";

					auto exec = GoExecution(go, script, command);
					exec.SetIsDestroy(true);

					executions.push_back(exec);
				}

				continue;
			}

			if (script->GetState() == ScriptState::ToLoad)
				executions.push_back(GoExecution(go, script, ""));
			else if (script->GetState() == ScriptState::ToStart && go->GetActive())
			{
				std::string command = script->GetName() + ".start()";
				executions.push_back(GoExecution(go, script, command));
			}
			else if (script->GetState() == ScriptState::Updating && go->GetActive())
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

	bool ScriptManager::ExecuteScript(const GoExecution& execution)
	{
		// Execute a plan for the scripts
		auto script = execution.GetScript();
		auto go = execution.GetGo();
		auto state = script->GetState();

		this->connectionManager->SetCurrentGo(go);

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

					// Register go instance data
					this->connectionManager->CreateScriptData(go, script);

					this->loaded.push_back(scriptName);
					script->SetPath(this->paths[scriptName]);
				}
			}
		}
		else
		{
			// Execute script plan
			auto command = execution.GetCommand();

			if (script->GetUpdateScriptData())
			{
				this->connectionManager->UpdateScriptData(go, script);
				script->SetUpdateScriptData(false);
			}

			if (luaL_dostring(this->state, command.c_str()))
			{
				Debug::Logging::Log("[Project]: Error in Script " + 
					script->GetName() + ": " + command + " = " +
					lua_tostring(this->state, -1) + " in go " + go->GetId(),
					Debug::LogSeverity::Error,
					Debug::LogOrigin::Engine,
					{ {"go_id", go->GetId()}, {"script_name", script->GetName()}}
				);

				return false;
			}

			// Change states
			if (state == ScriptState::ToStart)
				script->SetState(ScriptState::Updating);
			else if (state == ScriptState::ToDestroy)
			{
				script->SetState(ScriptState::Destroyed);
				this->connectionManager->DeleteScriptData(go, script);
			}
		}
		
		return true;
	}

	bool ScriptManager::AddScript(GameObjectPtr go, const std::string& scriptName)
	{
		// Set script to be add in go.
		if (go != nullptr)
		{
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

	bool ScriptManager::DestroyScript(GameObjectPtr go, const std::string& scriptName)
	{
		// Set script to be destroyed
		if (go != nullptr)
		{
			for (auto script : go->GetScripts())
			{
				if (script->GetName() == scriptName)
				{
					script->SetState(ScriptState::ToDestroy);
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

	int ScriptManager::GetStackSize()
	{
		if(this->connectionManager != nullptr)
			return this->connectionManager->GetStackSize();

		return 0;
	}

	#pragma region InternalFunctions

	void ScriptManager::LoadScriptsPaths(const std::string& basePath, bool& error)
	{
		// Load scripts names and paths from path (assets path)
		for (const std::string& file : Utils::Directory::ListDirectories(basePath, false))
		{
			auto fileName = Utils::Directory::GetLastPartFromPathNoExtension(file);
			auto extension = Utils::Directory::GetExtensionFromPath(file);

			if (Utils::Directory::IsDirectory(file))
				LoadScriptsPaths(file, error);
			else if (this->paths.contains(fileName))
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
}}
