#include <BoxEngine.hpp>
#include "EngineConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<EngineConnection> EngineConnection::current;

	EngineConnection::EngineConnection(lua_State* state)
	{
		this->state = state;
	}

	void EngineConnection::Bind()
	{
		lua_newtable(this->state);

		LuaUtils::RegTable(this->state, "get_fps", GetFPS);
		LuaUtils::RegTable(this->state, "get_frametime", GetFrametime);
		LuaUtils::RegTable(this->state, "stop", StopEngine);
		LuaUtils::RegTable(this->state, "restart", RestartEngine);

		lua_setglobal(this->state, "_engine_");
	}

	void EngineConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	EngineConnectionPtr EngineConnection::Get()
	{
		return current.lock();
	}

	void EngineConnection::Set(EngineConnectionPtr instance)
	{
		current = instance;
	}

	int EngineConnection::GetFPS(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		lua_pushnumber(L, Project::GetCurrentProject()->GetCurrentFPS());
		return 1;
	}

	int EngineConnection::GetFrametime(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		lua_pushnumber(L, Project::GetCurrentProject()->GetCurrentFrameTime());
		return 1;
	}
	
	int EngineConnection::StopEngine(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		Project::GetCurrentProject()->Stop();
		return 0;
	}

	int EngineConnection::RestartEngine(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		Project::GetCurrentProject()->StopThenStart();
		return 0;
	}
}}}}