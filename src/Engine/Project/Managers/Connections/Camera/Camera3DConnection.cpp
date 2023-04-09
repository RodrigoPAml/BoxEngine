#include <BoxEngine.hpp>
#include "Camera3DConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<Camera3DConnection> Camera3DConnection::current;

	Camera3DConnection::Camera3DConnection(lua_State* state)
	{
		this->state = state;
	}

	void Camera3DConnection::Bind()
	{
		// Cam3D manager
		lua_newtable(this->state);

		Utils::Lua::RegTable(this->state, "create", CreateCamera);
		Utils::Lua::RegTable(this->state, "destroy", DestroyCamera);
		Utils::Lua::RegTable(this->state, "update", UpdateCamera);
		Utils::Lua::RegTable(this->state, "get_view", GetViewMatrix);
		Utils::Lua::RegTable(this->state, "get_projection", GetProjectionMatrix);
		Utils::Lua::RegTable(this->state, "set_current", SetCurrentCamera);

		lua_setglobal(this->state, "_cam3d_");
	}

	void Camera3DConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	Camera3DConnectionPtr Camera3DConnection::Get()
	{
		return current.lock();
	}

	void Camera3DConnection::Set(Camera3DConnectionPtr instance)
	{
		current = instance;
	}

	int Camera3DConnection::CreateCamera(lua_State* L)
	{
		auto top_stack = lua_gettop(L);

		if (top_stack != 1)
			return luaL_error(L, "expecting 1 argument in function call");
			
		if (lua_istable(L, 1))
		{
			Camera::CameraConfiguration config;

			if (!Utils::Lua::GetTable(L, 1, "position", config.position))
				return luaL_error(L, "argument position needs to exists and be a table");

			if (!Utils::Lua::GetTable(L, 1, "yaw", config.yaw))
				return luaL_error(L, "argument yaw needs to exists and be a float");

			if (!Utils::Lua::GetTable(L, 1, "pitch", config.pitch))
				return luaL_error(L, "argument pitch needs to exists and be a float");

			if (!Utils::Lua::GetTable(L, 1, "fov", config.fov))
				return luaL_error(L, "argument fov needs to exists and be a float");

			if (!Utils::Lua::GetTable(L, 1, "aspect_ratio", config.aspectRatio))
				return luaL_error(L, "argument aspect_ratio needs to exists and be a float");

			if (!Utils::Lua::GetTable(L, 1, "zfar", config.zFar))
				return luaL_error(L, "argument zfar needs to exists and be a float");

			if (!Utils::Lua::GetTable(L, 1, "znear", config.zNear))
				return luaL_error(L, "argument znear needs to exists and be a float");

			auto instance = Camera3DConnection::Get();

			instance->cameras[++instance->currentId] = Camera::Camera3DPtr(new Camera::Camera3D(config));

			lua_pushnumber(L, instance->currentId);
			return 1;
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

		lua_pushnil(L);
		return 1;
	}

	int Camera3DConnection::DestroyCamera(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera3DConnection::Get();

			instance->cameras.erase(id);
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 0;
	}
	
	int Camera3DConnection::UpdateCamera(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		Camera::Camera3DPtr cam = nullptr;

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera3DConnection::Get();

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
			glm::vec3 pos;
			if (Utils::Lua::GetTable(L, 2, "position", pos))
				cam->SetPosition(pos);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument position needs be a table");
			}

			glm::vec3 rot;
			if (Utils::Lua::GetTable(L, 2, "rotation", rot))
				cam->SetPosition(rot);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument rotation needs be a table");
			}

			float aspectRatio;
			if (Utils::Lua::GetTable(L, 2, "aspect_ratio", aspectRatio))
				cam->SetAspectRatio(aspectRatio);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument aspect_ratio needs be a number");
			}

			float fov;
			if (Utils::Lua::GetTable(L, 2, "fov", fov))
				cam->SetFOV(fov);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument fov needs be a number");
			}

			float pitch;
			if (Utils::Lua::GetTable(L, 2, "pitch", pitch))
				cam->SetPitch(pitch);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument pitch needs be a number");
			}

			float yaw;
			if (Utils::Lua::GetTable(L, 2, "yaw", yaw))
				cam->SetPitch(yaw);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument yaw needs be a number");
			}
			
			float zfar;
			if (Utils::Lua::GetTable(L, 2, "zfar", zfar))
				cam->SetZFar(zfar);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument zfar needs be a number");
			}

			float znear;
			if (Utils::Lua::GetTable(L, 2, "znear", znear))
				cam->SetZNear(znear);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument znear needs be a number");
			}

			cam->UpdateProjectionMatrix();
			cam->UpdateViewMatrix();
		}
		else
		{
			cam = nullptr;
			return luaL_error(L, "argument 2 is expected to be a table");
		}

		lua_pushboolean(L, true);
		return 1;
	}
	
	int Camera3DConnection::GetCamera(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		Camera::Camera3DPtr cam = nullptr;

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera3DConnection::Get();

			cam = instance->cameras[id];
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (cam == nullptr)
			lua_pushnil(L);
		else
		{
			lua_newtable(L);

			Utils::Lua::RegTable(L, "position", cam->GetPosition());
			Utils::Lua::RegTable(L, "right", cam->GetRight());
			Utils::Lua::RegTable(L, "front", cam->GetFront());
			Utils::Lua::RegTable(L, "up", cam->GetUp());
			Utils::Lua::RegTable(L, "aspect_ratio", cam->GetAspectRatio());
			Utils::Lua::RegTable(L, "fov", cam->GetFOV());
			Utils::Lua::RegTable(L, "pitch", cam->GetPitch());
			Utils::Lua::RegTable(L, "yaw", cam->GetYaw());
			Utils::Lua::RegTable(L, "zfar", cam->GetZFar());
			Utils::Lua::RegTable(L, "znear", cam->GetZNear());
		}

		return 1;
	}
	
	int Camera3DConnection::GetViewMatrix(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		Camera::Camera3DPtr cam = nullptr;

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera3DConnection::Get();

			cam = instance->cameras[id];
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (cam != nullptr)
		{
			auto mat = cam->GetViewMatrix();

			lua_newtable(L);
			Utils::Lua::RegTable(L, 0, mat[0]);
			Utils::Lua::RegTable(L, 1, mat[1]);
			Utils::Lua::RegTable(L, 2, mat[2]);
			Utils::Lua::RegTable(L, 3, mat[3]);
		}
		else
			lua_pushnil(L);

		return 1;
	}
	
	int Camera3DConnection::GetProjectionMatrix(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		Camera::Camera3DPtr cam = nullptr;

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera3DConnection::Get();

			cam = instance->cameras[id];
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (cam != nullptr)
		{
			auto mat = cam->GetProjectionMatrix();

			lua_newtable(L);
			Utils::Lua::RegTable(L, 0, mat[0]);
			Utils::Lua::RegTable(L, 1, mat[1]);
			Utils::Lua::RegTable(L, 2, mat[2]);
			Utils::Lua::RegTable(L, 3, mat[3]);
		}
		else
			lua_pushnil(L);

		return 1;
	}
	
	int Camera3DConnection::SetCurrentCamera(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		Camera::Camera3DPtr cam = nullptr;

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);
			auto instance = Camera3DConnection::Get();

			cam = instance->cameras[id];
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (cam != nullptr)
			Camera::Camera3D::SetCurrentCamera(cam);

		return 0;
	}
 }}}