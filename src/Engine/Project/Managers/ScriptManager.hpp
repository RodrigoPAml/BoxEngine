#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {

	class ScriptManager;

	typedef std::shared_ptr<ScriptManager> ScriptManagerPtr;
	typedef std::weak_ptr<ScriptManager> ScriptManagerWeakPtr;

	/// <summary>
	/// Scripts Manager.
	/// </summary>
	class ScriptManager
	{
	private:
		/// <summary>
		/// Map between script with location 
		/// </summary>
		std::unordered_map<std::string, std::string> paths;

		/// <summary>
		/// List of scripts
		/// </summary>
		std::vector<std::string> list;

		/// <summary>
		/// Scripts that are loaded at runtime
		/// </summary>
		std::vector<std::string> loaded;

		/// <summary>
		/// Manager for the connection (calls between lua and c++)
		/// </summary>
		ConnectionManagerPtr connectionManager;

		/// <summary>
		/// Lua State
		/// </summary>
		lua_State* state = nullptr;
	public:
		// Load all the names of scripts in a vector
		bool LoadScriptNames(const std::string& basePath);

		// Return the list of scripts
		std::vector<std::string>& GetScriptsNames();

		// Load and delete all scripts containad in gameobjects of the scene
		bool LoadLuaAndScriptsPath(const std::string& basePath);

		// Destroy all scripts from gos
		void DestroyAllScripts(bool hasError, std::vector<GameObjectPtr>& root);

		// Get the plan of execution of the scripts of a go.
		void GetScriptsExecution(const GameObjectPtr go, std::vector<GoExecution>& executions, ProjectMode mode);

		// Execute script of a go
		bool ExecuteScript(const GoExecution& execution, bool setAsCurrent = true);

		// Add and remove script at runtime
		bool AddScript(GameObjectPtr go, const std::string& scriptName);
		bool DestroyScript(GameObjectPtr go, const std::string& scriptName, bool remove);
		
		// In case you just created a go and want it scripts to load imediatly
		// Otherwise will be in the next frame
		bool PreLoadScripts(GameObjectPtr go);

		int GetStackSize();
	private:
		// Load a map by ref with a map with name and path of the script
		void LoadScriptsPaths(const std::string& basePath, bool& error);

		// When te engine stops, release all scripts by calling destroy, if have error stop.
		void RecursiveUnloadAllScripts(const std::vector<GameObjectPtr> gos, bool& error);
	};
}}}