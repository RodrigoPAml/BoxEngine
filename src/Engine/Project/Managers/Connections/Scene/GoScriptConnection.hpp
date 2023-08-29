#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
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
		/// Global reference.
		/// </summary>
		static std::weak_ptr<GoScriptConnection> current;
	public:
		GoScriptConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static GoScriptConnectionPtr Get();
		static void Set(GoScriptConnectionPtr instance);
	private:
		// Go
		static int GetId(lua_State* L);
		static int CreateGo(lua_State* L);
		static int DestroyGo(lua_State* L);
		static int UpdateGo(lua_State* L);
		static int GetGo(lua_State* L);
		static int ChangeGoFather(lua_State* L);
		static int ChangeGoIndex(lua_State* L);

		// Scripts
		static int GetScript(lua_State* L);
		static int AddScript(lua_State* L); 
		static int RemoveScript(lua_State* L);
		static int ChangeScriptIndex(lua_State* L);
	};
}}}