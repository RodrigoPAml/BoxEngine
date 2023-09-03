#include <BoxEngine.hpp>
#include "InputConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<InputConnection> InputConnection::current;

	InputConnection::InputConnection(lua_State* state)
	{
		this->state = state;
	}

	void InputConnection::Bind()
	{
		lua_newtable(this->state);

		Utils::Lua::RegTable(this->state, "get_key", GetKey);
		Utils::Lua::RegTable(this->state, "get_mod", GetMod);

		Utils::Lua::RegTable(this->state, "get_mouse_pos", GetMousePos);
		Utils::Lua::RegTable(this->state, "get_cam_mouse_pos", GetCamMousePos);
		Utils::Lua::RegTable(this->state, "get_mouse_var", GetMouseVar);
		Utils::Lua::RegTable(this->state, "get_mouse_button", GetMouseButton);

		lua_setglobal(this->state, "_input_");
	}

	void InputConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	InputConnectionPtr InputConnection::Get()
	{
		return current.lock();
	}

	void InputConnection::Set(InputConnectionPtr instance)
	{
		current = instance;
	}

	int InputConnection::GetKey(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string key = "";

		if (lua_isstring(L, 1))
			key = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		auto action = Input::Keyboard::GetKeyState(Input::MapKey(key));
		lua_pushstring(L, Input::MapInputAction(action).c_str());

		return 1;
	}

	int InputConnection::GetMod(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string mod = "";

		if (lua_isstring(L, 1))
			mod = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		auto action = Input::Keyboard::GetModState(Input::MapMod(mod));

		lua_pushstring(L, Input::MapInputAction(action).c_str());

		return 1;
	}

	int InputConnection::GetMousePos(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		auto pos = Input::Mouse::GetMousePosition();

		// x = x min
		// y = y min
		// z = x max
		// w = y max
		auto box = Project::GetCurrentProject()->GetScreenLimits();
		
		float x = std::max(pos.x - box.x, 0.0f);
		x = std::min(x, box.z);

		float y = std::max(pos.y - box.y, 0.0f);
		y = std::min(y, box.w);

		lua_newtable(L);
		Utils::Lua::RegTable(L, "x", x);
		Utils::Lua::RegTable(L, "y", y);

		return 1;
	}

	int InputConnection::GetCamMousePos(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		auto cam = Camera::Camera2D::GetCurrentCamera();

		if (cam == nullptr)
			lua_pushnil(L);
		else
		{
			auto pos = Input::Mouse::GetMousePosition();

			// x = x min
			// y = y max
			// z = x max
			// w = y min
			auto box = Project::GetCurrentProject()->GetScreenLimits();

			float x = std::max(pos.x - box.x, 0.0f);
			x = std::min(x, box.z);

			float y = std::max(pos.y - box.y, 0.0f);
			y = std::min(y, box.w);
			
			float maxX = std::abs(box.x - box.z);
			float maxY = std::abs(box.y - box.w);

			lua_newtable(L);
			Utils::Lua::RegTable(L, "x", (x/maxX)*cam->GetRight());
			Utils::Lua::RegTable(L, "y", (y/maxY)*cam->GetTop());
		}

		return 1;
	}

	int InputConnection::GetMouseVar(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		auto var = Input::Mouse::GetMouseVariation();

		lua_newtable(L);
		Utils::Lua::RegTable(L, "x", var.x);
		Utils::Lua::RegTable(L, "y", var.y);

		return 1;
	}

	int InputConnection::GetMouseButton(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");
		
		std::string key = "";

		if (lua_isstring(L, 1))
			key = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		auto var = Input::Mouse::GetMouseButtonState(Input::MapMouseButton(key));

		lua_pushstring(L, Input::MapInputAction(var).c_str());

		return 1;
	}
}}}