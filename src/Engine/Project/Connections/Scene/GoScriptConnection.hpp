#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class GoScriptConnection;
	typedef std::shared_ptr<GoScriptConnection> GoScriptConnectionPtr;
	typedef std::weak_ptr<GoScriptConnection> GoScriptConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle gos and scripts.
	/// </summary>
	class GoScriptConnection
	{
	private:
		lua_State* state;

		/// <summary>
		/// The current visited go by the engine
		/// </summary>
		GameObjectWeakPtr currentGo;

		/// <summary>
		/// The current visited go by the engine
		/// </summary>
		ScriptWeakPtr currentScript;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<GoScriptConnection> current;
	public:
		GoScriptConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);
		void SetCurrentScript(ScriptPtr script);

		static GoScriptConnectionPtr Get();
		static void Set(GoScriptConnectionPtr instance);
	private:
		// Go
		static int GetId(lua_State* L);
		static int CreateGo(lua_State* L);
		static int DestroyGo(lua_State* L);
		static int Copy(lua_State* L);
		static int SetActive(lua_State* L);
		static int SetName(lua_State* L);
		static int GetGo(lua_State* L);
		static int ChangeGoFather(lua_State* L);
		static int ChangeGoIndex(lua_State* L);
		static int LoadScripts(lua_State* L);
		static int GetGosOfScript(lua_State* L);
		static int InspectGo(lua_State* L);
		static int GetInspectedGo(lua_State* L);

		// Scripts
		static int GetCurrent(lua_State* L);
		static int GetScript(lua_State* L);
		static int AddScript(lua_State* L); 
		static int SetScriptActive(lua_State* L);
		static int RemoveScript(lua_State* L);
		static int ChangeScriptIndex(lua_State* L);
		static int DisplaceScript(lua_State* L);

		// Persistance
		static int SetPersistCurrentGo(lua_State* L);
		static int SetPersistExternalGo(lua_State* L);

		static int SetPersistCurrentScript(lua_State* L);
		static int SetPersistCurrentScriptData(lua_State* L);
		static int SetShowCurrentScriptData(lua_State* L);

		static int SetPersistExternalScript(lua_State* L);
		static int SetPersistExternalScriptData(lua_State* L);
		static int SetShowExternalScriptData(lua_State* L);
	};
}}}}