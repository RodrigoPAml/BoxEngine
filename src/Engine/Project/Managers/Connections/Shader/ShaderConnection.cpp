#include <BoxEngine.hpp>
#include "ShaderConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<ShaderConnection> ShaderConnection::current;

	ShaderConnection::ShaderConnection(lua_State* state)
	{
		this->state = state;
	}

	void ShaderConnection::Bind()
	{
		lua_newtable(this->state);
		
		Utils::Lua::RegTable(this->state, "create", CreateShader);
		Utils::Lua::RegTable(this->state, "destroy", DestroyShader);

		Utils::Lua::RegTable(this->state, "active", Active);
		Utils::Lua::RegTable(this->state, "unactive_all", UnactiveAll);

		Utils::Lua::RegTable(this->state, "set_bool", SetShaderBool);
		Utils::Lua::RegTable(this->state, "set_float", SetShaderFloat);
		Utils::Lua::RegTable(this->state, "set_int", SetShaderInt);

		Utils::Lua::RegTable(this->state, "set_mat2", SetShaderMat2);
		Utils::Lua::RegTable(this->state, "set_mat3", SetShaderMat3);
		Utils::Lua::RegTable(this->state, "set_mat4", SetShaderMat4);

		Utils::Lua::RegTable(this->state, "set_vec2", SetShaderVec2);
		Utils::Lua::RegTable(this->state, "set_vec3", SetShaderVec3);
		Utils::Lua::RegTable(this->state, "set_vec4", SetShaderVec4);

		Utils::Lua::RegTable(this->state, "set_xy", SetShaderXY);
		Utils::Lua::RegTable(this->state, "set_xyz", SetShaderXYZ);
		Utils::Lua::RegTable(this->state, "set_xyzw", SetShaderXYZW);

		lua_setglobal(this->state, "_shader_");
	}

	void ShaderConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	ShaderConnectionPtr ShaderConnection::Get()
	{
		return current.lock();
	}

	void ShaderConnection::Set(ShaderConnectionPtr instance)
	{
		current = instance;
	}
	
	int ShaderConnection::CreateShader(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_istable(L, 1))
		{
			std::string vertexPath = "";
			std::string fragmentPath = "";
			std::string geometryPath = "";

			if (!Utils::Lua::GetTable(L, 1, "vertex_path", vertexPath))
				return luaL_error(L, "argument vertex needs to exists and be a string");

			Utils::Lua::GetTable(L, 1, "fragment_path", vertexPath);
			Utils::Lua::GetTable(L, 1, "geometry_path", geometryPath);

			bool success = false;

			std::string vertexContent = Utils::Directory::ReadFile(vertexPath, &success);
			std::string fragmentContent = "";
			std::string geometryContent = "";

			if(!success)
				return luaL_error(L, "failed to read vertex shader file");

			if (fragmentPath.size() > 0)
				fragmentContent = Utils::Directory::ReadFile(fragmentPath, &success);

			if (!success)
				return luaL_error(L, "failed to read fragment shader file");

			if (geometryPath.size() > 0)
				geometryContent = Utils::Directory::ReadFile(geometryPath, &success);

			if (!success)
				return luaL_error(L, "failed to read geometry shader file");

			GPU::ShaderPtr shader = nullptr;
			auto instance = ShaderConnection::Get();

			try
			{
				shader = GPU::ShaderPtr(new GPU::Shader(vertexContent, fragmentContent, geometryContent));

				instance->shaders[++instance->currentId] = shader;
				lua_pushnumber(L, instance->currentId);
				return 1;
			}
			catch (std::exception)
			{
				lua_pushnil(L);
				shader = nullptr;
				instance = nullptr;
				return 1;
			}
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

		lua_pushnil(L);
		return 1;
	}

	int ShaderConnection::DestroyShader(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			auto instance = ShaderConnection::Get();
			lua_pushboolean(L, instance->shaders.erase(lua_tonumber(L, 1) > 0));
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
	}

	int ShaderConnection::Active(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");
		
		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->Use();

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::UnactiveAll(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		GPU::Shader::ClearCurrentShader();

		return 0;
	}

	int ShaderConnection::SetShaderBool(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		bool value = false;
		if (lua_isboolean(L, 3))
			value = lua_toboolean(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a bool");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetBool(label, value);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderInt(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		int value = 0;
		if (lua_isnumber(L, 3))
			value = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetInt(label, value);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderFloat(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		float value = 0;
		if (lua_isnumber(L, 3))
			value = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetFloat(label, value);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderXY(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 4)
			return luaL_error(L, "expecting 4 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		float value1 = 0;
		if (lua_isnumber(L, 3))
			value1 = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		float value2 = 0;
		if (lua_isnumber(L, 4))
			value2 = lua_tonumber(L, 4);
		else return luaL_error(L, "argument 4 is expected to be a number");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetXY(label, value1, value2);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderXYZ(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 5)
			return luaL_error(L, "expecting 5 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		float value1 = 0;
		if (lua_isnumber(L, 3))
			value1 = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		float value2 = 0;
		if (lua_isnumber(L, 4))
			value2 = lua_tonumber(L, 4);
		else return luaL_error(L, "argument 4 is expected to be a number");

		float value3 = 0;
		if (lua_isnumber(L, 5))
			value3 = lua_tonumber(L, 5);
		else return luaL_error(L, "argument 5 is expected to be a number");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetXYZ(label, value1, value2, value3);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderXYZW(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 6)
			return luaL_error(L, "expecting 6 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		float value1 = 0;
		if (lua_isnumber(L, 3))
			value1 = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		float value2 = 0;
		if (lua_isnumber(L, 4))
			value2 = lua_tonumber(L, 4);
		else return luaL_error(L, "argument 4 is expected to be a number");

		float value3 = 0;
		if (lua_isnumber(L, 5))
			value3 = lua_tonumber(L, 5);
		else return luaL_error(L, "argument 5 is expected to be a number");

		float value4 = 0;
		if (lua_isnumber(L, 6))
			value4 = lua_tonumber(L, 6);
		else return luaL_error(L, "argument 6 is expected to be a number");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetXYZW(label, value1, value2, value3, value4);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderVec2(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		glm::vec2 value;
		if (lua_istable(L, 3))
		{
			if(!Utils::Lua::GetTable(L, 3, "value", value))
				return luaL_error(L, "argument 3 is expected to be a table with vec2");
		}
		else return luaL_error(L, "argument 3 is expected to be a table");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetVec2(label, value);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderVec3(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		glm::vec3 value;
		if (lua_istable(L, 3))
		{
			if (!Utils::Lua::GetTable(L, 3, "value", value))
				return luaL_error(L, "argument 3 is expected to be a table with vec3");
		}
		else return luaL_error(L, "argument 3 is expected to be a table");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetVec3(label, value);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderVec4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		glm::vec4 value;
		if (lua_istable(L, 3))
		{
			if (!Utils::Lua::GetTable(L, 3, "value", value))
				return luaL_error(L, "argument 3 is expected to be a table with vec4");
		}
		else return luaL_error(L, "argument 3 is expected to be a table");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetVec4(label, value);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderMat2(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		glm::mat2 mat;
		if (lua_istable(L, 3))
		{
			if (!Utils::Lua::GetTable(L, 3, 1, mat[0]))
				return luaL_error(L, "argument 3 is expected to be a table, missing vec2 1");

			if (!Utils::Lua::GetTable(L, 3, 2, mat[1]))
				return luaL_error(L, "argument 3 is expected to be table, missing vec2 2");
		}
		else return luaL_error(L, "argument 3 is expected to be a table with mat2 format");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetMat4(label, mat);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderMat3(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		glm::mat3 mat;
		if (lua_istable(L, 3))
		{
			if (!Utils::Lua::GetTable(L, 3, 1, mat[0]))
				return luaL_error(L, "argument 3 is expected to be a table, missing vec3 1");

			if (!Utils::Lua::GetTable(L, 3, 2, mat[1]))
				return luaL_error(L, "argument 3 is expected to be table, missing vec3 2");

			if (!Utils::Lua::GetTable(L, 3, 3, mat[2]))
				return luaL_error(L, "argument 3 is expected to be table, missing vec3 3");
		}
		else return luaL_error(L, "argument 3 is expected to be a table with mat3 format");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetMat4(label, mat);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}

	int ShaderConnection::SetShaderMat4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string label = "";
		if (lua_isstring(L, 2))
			label = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		glm::mat4 mat;
		if (lua_istable(L, 3))
		{
			if(!Utils::Lua::GetTable(L, 3, 1, mat[0]))
				return luaL_error(L, "argument 3 is expected to be a table, missing vec4 1");

			if (!Utils::Lua::GetTable(L, 3, 2, mat[1]))
				return luaL_error(L, "argument 3 is expected to be table, missing vec4 2");

			if (!Utils::Lua::GetTable(L, 3, 3, mat[2]))
				return luaL_error(L, "argument 3 is expected to be a table, missing vec4 3");

			if (!Utils::Lua::GetTable(L, 3, 4, mat[3]))
				return luaL_error(L, "argument 3 is expected to be a table, missing vec4 4");
		}
		else return luaL_error(L, "argument 3 is expected to be a table with mat4 format");

		auto instance = ShaderConnection::Get();
		auto shader = instance->shaders[id];

		if (shader != nullptr)
			shader->SetMat4(label, mat);

		lua_pushboolean(L, shader != nullptr);
		return 1;
	}
}}}