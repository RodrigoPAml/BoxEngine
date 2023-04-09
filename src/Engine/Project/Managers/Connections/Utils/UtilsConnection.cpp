#include <BoxEngine.hpp>
#include "UtilsConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<UtilsConnection> UtilsConnection::current;

	UtilsConnection::UtilsConnection(lua_State* state)
	{
		this->state = state;
	}

	void UtilsConnection::Bind()
	{
		lua_newtable(this->state);

		Utils::Lua::RegTable(this->state, "get_fps", GetFPS);
		Utils::Lua::RegTable(this->state, "get_frametime", GetFrametime);

		lua_setglobal(this->state, "_utils_");

		auto content = Utils::Directory::ReadFile(Utils::Directory::GetResourcePath() + "/scripts/utils.lua");
		luaL_dostring(this->state , content.c_str());
	}

	void UtilsConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	UtilsConnectionPtr UtilsConnection::Get()
	{
		return current.lock();
	}

	void UtilsConnection::Set(UtilsConnectionPtr instance)
	{
		current = instance;
	}

	int UtilsConnection::GetFPS(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		lua_pushnumber(L, Project::GetCurrentProject()->GetCurrentFPS());
		return 1;
	}

	int UtilsConnection::GetFrametime(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		lua_pushnumber(L, Project::GetCurrentProject()->GetCurrentFrameTime());
		return 1;
	}
}}}