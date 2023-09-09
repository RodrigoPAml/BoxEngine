#include <BoxEngine.hpp>
#include "Camera2DConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<Camera2DConnection> Camera2DConnection::current;

	Camera2DConnection::Camera2DConnection(lua_State* state)
	{
		this->state = state;
	}

	void Camera2DConnection::Bind()
	{
		// Cam2D manager
		lua_newtable(this->state);

		Utils::Lua::RegTable(this->state, "create", CreateCamera);
		Utils::Lua::RegTable(this->state, "destroy", DestroyCamera);
		Utils::Lua::RegTable(this->state, "get", GetCamera);
		Utils::Lua::RegTable(this->state, "update", UpdateCamera);
		Utils::Lua::RegTable(this->state, "get_matrix", GetMatrix);
		Utils::Lua::RegTable(this->state, "set_current", SetCurrentCamera);
		Utils::Lua::RegTable(this->state, "get_current", GetCurrentCamera);

		lua_setglobal(this->state, "_cam2d_");
	}

	void Camera2DConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	Camera2DConnectionPtr Camera2DConnection::Get()
	{
		return current.lock();
	}

	void Camera2DConnection::Set(Camera2DConnectionPtr instance)
	{
		current = instance;
	}

	int Camera2DConnection::CreateCamera(lua_State* L)
	{
		auto top_stack = lua_gettop(L);

		if (top_stack != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		float left = 0, right = 0, top = 0, bottom = 0;
		if (lua_istable(L, 1))
		{
			if (!Utils::Lua::GetTable(L, 1, "left", left))
				return luaL_error(L, "argument left needs to be a number");

			if (!Utils::Lua::GetTable(L, 1, "right", right))
				return luaL_error(L, "argument right needs to be a number");

			if (!Utils::Lua::GetTable(L, 1, "top", top))
				return luaL_error(L, "argument top needs to be a number");

			if (!Utils::Lua::GetTable(L, 1, "bottom", bottom))
				return luaL_error(L, "argument bottom needs to be a number");
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

		auto instance = Camera2DConnection::Get();

		instance->cameras[++instance->currentId] = Camera::Camera2DPtr(new Camera::Camera2D(
			left,
			right,
			top,
			bottom
		));

		lua_pushnumber(L, instance->currentId);

		return 1;
	}

	int Camera2DConnection::DestroyCamera(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1); 
			auto instance = Camera2DConnection::Get();

			lua_pushboolean(L, instance->cameras.erase(id) > 0);
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1; 
	}
	
	int Camera2DConnection::UpdateCamera(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		Camera::Camera2DPtr cam = nullptr;

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera2DConnection::Get();

			cam = instance->cameras[id];
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (cam == nullptr)
		{
			lua_pushboolean(L, false);
			return 1;
		}

		if (lua_istable(L, 2))
		{
			lua_getfield(L, 2, "left");

			if (lua_isnumber(L, -1))
				cam->SetLeft(lua_tonumber(L, -1));
			else if (!lua_isnil(L, -1))
			{
				cam = nullptr;
				return luaL_error(L, "argument left needs to be a number");
			}

			lua_getfield(L, 2, "right");

			if (lua_isnumber(L, -1))
				cam->SetRight(lua_tonumber(L, -1));
			else if (!lua_isnil(L, -1))
			{
				cam = nullptr;
				return luaL_error(L, "argument right needs to be a number");
			}

			lua_getfield(L, 2, "top");

			if (lua_isnumber(L, -1))
				cam->SetTop(lua_tonumber(L, -1));
			else if (!lua_isnil(L, -1))
			{
				cam = nullptr;
				return luaL_error(L, "argument top needs to be a number");
			}

			lua_getfield(L, 2, "bottom");

			if (lua_isnumber(L, -1))
				cam->SetBottom(lua_tonumber(L, -1));
			else if (!lua_isnil(L, -1))
			{
				cam = nullptr;
				return luaL_error(L, "argument bottom needs to be a number");
			}
		}
		else
		{
			cam = nullptr;
			return luaL_error(L, "argument 2 is expected to be a table");
		}

		lua_pushboolean(L, true);
		return 1;
	}

	int Camera2DConnection::GetCamera(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		Camera::Camera2DPtr cam = nullptr;

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera2DConnection::Get();

			cam = instance->cameras[id];
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (cam == nullptr)
			lua_pushnil(L);
		else
		{
			lua_newtable(L);

			Utils::Lua::RegTable(L, "left", cam->GetLeft());
			Utils::Lua::RegTable(L, "right", cam->GetRight());
			Utils::Lua::RegTable(L, "top", cam->GetTop());
			Utils::Lua::RegTable(L, "bottom", cam->GetBottom());
		}

		return 1;
	}

	int Camera2DConnection::GetMatrix(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		Camera::Camera2DPtr cam = nullptr;

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera2DConnection::Get();

			cam = instance->cameras[id];
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (cam != nullptr)
		{
			auto mat = cam->GetOrthoMatrix();

			// Register four tables direct in this table
			lua_newtable(L);
			Utils::Lua::RegTable(L, 1, mat[0]);
			Utils::Lua::RegTable(L, 2, mat[1]);
			Utils::Lua::RegTable(L, 3, mat[2]);
			Utils::Lua::RegTable(L, 4, mat[3]);
		}
		else
			lua_pushnil(L);

		return 1;
	}

	int Camera2DConnection::SetCurrentCamera(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		Camera::Camera2DPtr cam = nullptr;

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera2DConnection::Get();

			cam = instance->cameras[id];
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (cam != nullptr)
			Camera::Camera2D::SetCurrentCamera(cam);

		lua_pushboolean(L, cam != nullptr);

		return 1;
	}
	
	int Camera2DConnection::GetCurrentCamera(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no argument in function call");

		auto camera = Camera::Camera2D::GetCurrentCamera();

		if (camera == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}
		else
		{
			auto instance = Camera2DConnection::Get();

			for (const auto& pair : instance->cameras) 
			{
				if (pair.second == camera)
				{
					lua_pushnumber(L, pair.first);
					return 1;
				}
			}
		}

		lua_pushnil(L);
		return 1;
	}
}}}