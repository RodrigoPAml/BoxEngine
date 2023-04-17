#include <BoxEngine.hpp>
#include "WindowConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<WindowConnection> WindowConnection::current;

	WindowConnection::WindowConnection(lua_State* state)
	{
		this->state = state;
	}

	void WindowConnection::Bind()
	{
		lua_newtable(this->state);

		Utils::Lua::RegTable(this->state, "get_window_size", GetWindowSize);
		Utils::Lua::RegTable(this->state, "get_editor_window_size", GetEditorWindowSize);
		Utils::Lua::RegTable(this->state, "get_window_limits", GetWindowLimits);

		lua_setglobal(this->state, "_window_");
	}

	void WindowConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	WindowConnectionPtr WindowConnection::Get()
	{
		return current.lock();
	}

	void WindowConnection::Set(WindowConnectionPtr instance)
	{
		current = instance;
	}

	int WindowConnection::GetWindowSize(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		auto sizes = Project::GetCurrentProject()->GetScreenLimits();
		
		lua_newtable(L);
		Utils::Lua::RegTable(L, "x", std::abs(sizes.x - sizes.z));
		Utils::Lua::RegTable(L, "y", std::abs(sizes.y - sizes.w));

		return 1;
	}

	int WindowConnection::GetEditorWindowSize(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		auto size = Window::Window::GetSize();

		lua_newtable(L);
		Utils::Lua::RegTable(L, "x", size.x);
		Utils::Lua::RegTable(L, "y", size.y);

		return 1;
	}

	int WindowConnection::GetWindowLimits(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		auto sizes = Project::GetCurrentProject()->GetScreenLimits();

		lua_newtable(L);
		Utils::Lua::RegTable(L, "min_x", sizes.x);
		Utils::Lua::RegTable(L, "min_y", sizes.y);
		Utils::Lua::RegTable(L, "max_x", sizes.z);
		Utils::Lua::RegTable(L, "max_y", sizes.w);

		return 1;
	}
}}}