#include <BoxEngine.hpp>
#include "Camera3DConnection.hpp"

namespace BoxEngine {
namespace Engine {
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

		LuaUtils::RegTable(this->state, "create", CreateCamera);
		LuaUtils::RegTable(this->state, "destroy", DestroyCamera);
		LuaUtils::RegTable(this->state, "update", UpdateCamera);
		LuaUtils::RegTable(this->state, "get", GetCamera);

		LuaUtils::RegTable(this->state, "translate", TranslateCameraRelative);
		LuaUtils::RegTable(this->state, "translate_abs", TranslateCameraAbsolute);
		LuaUtils::RegTable(this->state, "rotate", RotateCamera);

		LuaUtils::RegTable(this->state, "get_view", GetViewMatrix);
		LuaUtils::RegTable(this->state, "get_projection", GetProjectionMatrix);
		LuaUtils::RegTable(this->state, "set_current", SetCurrentCamera);

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

			LuaUtils::GetTable(L, 1, "position", config.position);
			LuaUtils::GetTable(L, 1, "yaw", config.yaw);
			LuaUtils::GetTable(L, 1, "pitch", config.pitch);
			LuaUtils::GetTable(L, 1, "fov", config.fov);
			LuaUtils::GetTable(L, 1, "aspect_ratio", config.aspectRatio);
			LuaUtils::GetTable(L, 1, "zfar", config.zFar);
			LuaUtils::GetTable(L, 1, "znear", config.zNear);

			auto instance = Camera3DConnection::Get();

			instance->cameras[++instance->currentId] = Camera::Camera3DPtr(new Camera::Camera3D(config));

			lua_pushnumber(L, instance->currentId);
			return 1;
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

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

			lua_pushboolean(L, instance->cameras.erase(id) > 0);
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
	}

	int Camera3DConnection::TranslateCameraRelative(lua_State* L)
	{
		auto top_stack = lua_gettop(L);

		if (top_stack != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);

			if (lua_istable(L, 1))
			{
				auto instance = Camera3DConnection::Get();
				Camera::Camera3DPtr cam = instance->cameras[id];
				
				if (cam == nullptr)
				{
					instance = nullptr;
					lua_pushboolean(L, false);
					return 1;
				}

				std::string str = "";
				float velocity = 0;

				if (LuaUtils::GetTable(L, 1, "direction", str))
				{
					instance = nullptr;
					lua_pushboolean(L, false);
					return luaL_error(L, "expecting argument direction to be a string");
				}

				if (LuaUtils::GetTable(L, 1, "velocity", velocity))
				{
					instance = nullptr;
					lua_pushboolean(L, false);
					return luaL_error(L, "expecting argument velocity to be a number");
				}
				
				cam->TranslateRelative(Camera::GetCameraMovementFromString(str), velocity);

				lua_pushboolean(L, true);
				return 1;
			}
			else return luaL_error(L, "argument 1 is expected to be a table");
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
	}

	int Camera3DConnection::TranslateCameraAbsolute(lua_State* L)
	{
		auto top_stack = lua_gettop(L);

		if (top_stack != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);

			if (lua_istable(L, 1))
			{
				auto instance = Camera3DConnection::Get();
				Camera::Camera3DPtr cam = instance->cameras[id];

				if (cam == nullptr)
				{
					instance = nullptr;
					lua_pushboolean(L, false);
					return 1;
				}

				std::string str = "";
				float velocity = 0;

				if (LuaUtils::GetTable(L, 1, "direction", str))
				{
					instance = nullptr;
					lua_pushboolean(L, false);
					return luaL_error(L, "expecting argument direction to be a string");
				}

				if (LuaUtils::GetTable(L, 1, "velocity", velocity))
				{
					instance = nullptr;
					lua_pushboolean(L, false);
					return luaL_error(L, "expecting argument velocity to be a number");
				}

				cam->TranslateAbsolute(Camera::GetCameraMovementFromString(str), velocity);

				lua_pushboolean(L, true);
				return 1;
			}
			else return luaL_error(L, "argument 1 is expected to be a table");
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
	}

	int Camera3DConnection::RotateCamera(lua_State* L)
	{
		auto top_stack = lua_gettop(L);

		if (top_stack != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);

			if (lua_istable(L, 1))
			{
				auto instance = Camera3DConnection::Get();
				Camera::Camera3DPtr cam = instance->cameras[id];

				if (cam == nullptr)
				{
					instance = nullptr;
					lua_pushboolean(L, false);
					return 1;
				}

				float yaw = cam->GetYaw(), pitch = cam->GetPitch();

				LuaUtils::GetTable(L, 1, "yaw", yaw);
				LuaUtils::GetTable(L, 1, "pitch", pitch);
				
				cam->Rotate(yaw, pitch);

				lua_pushboolean(L, true);
				return 1;
			}
			else return luaL_error(L, "argument 1 is expected to be a table");
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
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
			if (LuaUtils::GetTable(L, 2, "position", pos))
				cam->SetPosition(pos);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument position needs be a table");
			}

			glm::vec3 rot;
			if (LuaUtils::GetTable(L, 2, "rotation", rot))
				cam->SetRotation(rot);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument rotation needs be a table");
			}

			float aspectRatio;
			if (LuaUtils::GetTable(L, 2, "aspect_ratio", aspectRatio))
				cam->SetAspectRatio(aspectRatio);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument aspect_ratio needs be a number");
			}

			float fov;
			if (LuaUtils::GetTable(L, 2, "fov", fov))
				cam->SetFOV(fov);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument fov needs be a number");
			}

			float pitch;
			if (LuaUtils::GetTable(L, 2, "pitch", pitch))
				cam->SetPitch(pitch);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument pitch needs be a number");
			}

			float yaw;
			if (LuaUtils::GetTable(L, 2, "yaw", yaw))
				cam->SetPitch(yaw);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument yaw needs be a number");
			}
			
			float zfar;
			if (LuaUtils::GetTable(L, 2, "zfar", zfar))
				cam->SetZFar(zfar);
			else if (!lua_isnil(L, 2))
			{
				cam = nullptr;
				return luaL_error(L, "argument zfar needs be a number");
			}

			float znear;
			if (LuaUtils::GetTable(L, 2, "znear", znear))
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

			LuaUtils::RegTable(L, "position", cam->GetPosition());
			LuaUtils::RegTable(L, "right", cam->GetRight());
			LuaUtils::RegTable(L, "front", cam->GetFront());
			LuaUtils::RegTable(L, "up", cam->GetUp());
			LuaUtils::RegTable(L, "aspect_ratio", cam->GetAspectRatio());
			LuaUtils::RegTable(L, "fov", cam->GetFOV());
			LuaUtils::RegTable(L, "pitch", cam->GetPitch());
			LuaUtils::RegTable(L, "yaw", cam->GetYaw());
			LuaUtils::RegTable(L, "zfar", cam->GetZFar());
			LuaUtils::RegTable(L, "znear", cam->GetZNear());
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
			LuaUtils::RegTable(L, 1, mat[0]);
			LuaUtils::RegTable(L, 2, mat[1]);
			LuaUtils::RegTable(L, 3, mat[2]);
			LuaUtils::RegTable(L, 4, mat[3]);
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
			LuaUtils::RegTable(L, 1, mat[0]);
			LuaUtils::RegTable(L, 2, mat[1]);
			LuaUtils::RegTable(L, 3, mat[2]);
			LuaUtils::RegTable(L, 4, mat[3]);
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

		lua_pushboolean(L, cam != nullptr);

		return 1;
	}
 }}}}