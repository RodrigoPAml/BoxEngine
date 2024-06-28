#include <BoxEngine.hpp>
#include "MathConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<MathConnection> MathConnection::current;

	MathConnection::MathConnection(lua_State* state)
	{
		this->state = state;
	}

	void MathConnection::Bind()
	{
		lua_newtable(this->state);

		LuaUtils::RegTable(this->state, "random", Random);

		LuaUtils::RegTable(this->state, "make_vec2", MakeMat4);
		LuaUtils::RegTable(this->state, "make_vec3", MakeMat4);
		LuaUtils::RegTable(this->state, "make_vec4", MakeMat4);

		LuaUtils::RegTable(this->state, "make_mat4", MakeMat4);
		LuaUtils::RegTable(this->state, "make_identity_mat4", MakeIdentityMat4);
		
		LuaUtils::RegTable(this->state, "make_mat3", MakeMat4);
		LuaUtils::RegTable(this->state, "make_identity_mat3", MakeIdentityMat4);

		LuaUtils::RegTable(this->state, "make_mat2", MakeMat4);
		LuaUtils::RegTable(this->state, "make_identity_mat2", MakeIdentityMat4);
		
		LuaUtils::RegTable(this->state, "translate", Translate);
		LuaUtils::RegTable(this->state, "rotate", Rotate);
		LuaUtils::RegTable(this->state, "scale", Scale);
		LuaUtils::RegTable(this->state, "multiply", Multiply);

		lua_setglobal(this->state, "_math_");
	}

	void MathConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	MathConnectionPtr MathConnection::Get()
	{
		return current.lock();
	}

	void MathConnection::Set(MathConnectionPtr instance)
	{
		current = instance;
	}

	int MathConnection::Random(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");
		
		double randomNumber = static_cast<double>(std::rand()) / RAND_MAX;
		lua_pushnumber(L, randomNumber);

		return 1;
	}

	int MathConnection::MakeVec2(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::vec2 vec = { 0, 0 };

		lua_newtable(L);
		
		lua_pushstring(L, "x");
		lua_pushnumber(L, vec.x);
		lua_settable(L, -3);

		lua_pushstring(L, "y");
		lua_pushnumber(L, vec.y);
		lua_settable(L, -3);

		return 1;
	}

	int MathConnection::MakeVec3(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::vec3 vec = { 0, 0, 0 };

		lua_newtable(L);

		lua_pushstring(L, "x");
		lua_pushnumber(L, vec.x);
		lua_settable(L, -3);

		lua_pushstring(L, "y");
		lua_pushnumber(L, vec.y);
		lua_settable(L, -3);

		lua_pushstring(L, "z");
		lua_pushnumber(L, vec.z);
		lua_settable(L, -3);

		return 1;
	}

	int MathConnection::MakeVec4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::vec4 vec = { 0, 0, 0, 0 };
		lua_newtable(L);

		lua_pushstring(L, "x");
		lua_pushnumber(L, vec.x);
		lua_settable(L, -3);

		lua_pushstring(L, "y");
		lua_pushnumber(L, vec.y);
		lua_settable(L, -3);

		lua_pushstring(L, "z");
		lua_pushnumber(L, vec.z);
		lua_settable(L, -3);

		lua_pushstring(L, "w");
		lua_pushnumber(L, vec.w);
		lua_settable(L, -3);

		return 1;
	}

	int MathConnection::MakeMat2(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::mat2 mat = glm::mat2();

		lua_newtable(L);
		LuaUtils::RegTable(L, 1, mat[0]);
		LuaUtils::RegTable(L, 2, mat[1]);

		return 1;
	}

	int MathConnection::MakeMat3(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::mat3 mat = glm::mat3();

		lua_newtable(L);
		LuaUtils::RegTable(L, 1, mat[0]);
		LuaUtils::RegTable(L, 2, mat[1]);
		LuaUtils::RegTable(L, 3, mat[2]);

		return 1;
	}

	int MathConnection::MakeMat4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::mat4 mat = glm::mat4();

		lua_newtable(L);
		LuaUtils::RegTable(L, 1, mat[0]);
		LuaUtils::RegTable(L, 2, mat[1]);
		LuaUtils::RegTable(L, 3, mat[2]);
		LuaUtils::RegTable(L, 4, mat[3]);

		return 1;
	}

	int MathConnection::MakeIdentityMat2(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::mat2 mat = glm::mat2(1.0f);

		lua_newtable(L);
		LuaUtils::RegTable(L, 1, mat[0]);
		LuaUtils::RegTable(L, 2, mat[1]);

		return 1;
	}

	int MathConnection::MakeIdentityMat3(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::mat3 mat = glm::mat3(1.0f);

		lua_newtable(L);
		LuaUtils::RegTable(L, 1, mat[0]);
		LuaUtils::RegTable(L, 2, mat[1]);
		LuaUtils::RegTable(L, 3, mat[2]);

		return 1;
	}

	int MathConnection::MakeIdentityMat4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::mat4 mat = glm::mat4(1.0f);

		lua_newtable(L);
		LuaUtils::RegTable(L, 1, mat[0]);
		LuaUtils::RegTable(L, 2, mat[1]);
		LuaUtils::RegTable(L, 3, mat[2]);
		LuaUtils::RegTable(L, 4, mat[3]);

		return 1;
	}
	
	int MathConnection::Translate(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		glm::mat4 mat;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, 1, 1, mat[0]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 2, mat[1]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 3, mat[2]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 4, mat[3]))
				return luaL_error(L, "argument 1 is expected to be a mat4");
		}
		else return luaL_error(L, "argument 1 is expected to be a mat4");

		glm::vec3 vec;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, 2, "x", vec.x))
				return luaL_error(L, "argument 2 is expected to be a vec3");

			if (!LuaUtils::GetTable(L, 2, "y", vec.y))
				return luaL_error(L, "argument 2 is expected to be a vec3");

			if (!LuaUtils::GetTable(L, 2, "z", vec.z))
				return luaL_error(L, "argument 2 is expected to be a vec3");
		}
		else return luaL_error(L, "argument 2 is expected to be a vec3");

		glm::mat4 model = glm::translate(mat, vec);

		lua_newtable(L);
		LuaUtils::RegTable(L, 1, model[0]);
		LuaUtils::RegTable(L, 2, model[1]);
		LuaUtils::RegTable(L, 3, model[2]);
		LuaUtils::RegTable(L, 4, model[3]);

		return 1;
	}

	int MathConnection::Rotate(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		glm::mat4 mat;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, 1, 1, mat[0]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 2, mat[1]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 3, mat[2]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 4, mat[3]))
				return luaL_error(L, "argument 1 is expected to be a mat4");
		}
		else return luaL_error(L, "argument 1 is expected to be a mat4");

		glm::vec3 vec;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, 2, "x", vec.x))
				return luaL_error(L, "argument 2 is expected to be a vec3");

			if (!LuaUtils::GetTable(L, 2, "y", vec.y))
				return luaL_error(L, "argument 2 is expected to be a vec3");

			if (!LuaUtils::GetTable(L, 2, "z", vec.z))
				return luaL_error(L, "argument 2 is expected to be a vec3");
		}
		else return luaL_error(L, "argument 2 is expected to be a vec3");

		float angle;
		if (lua_isnumber(L, 3))
			angle = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		glm::mat4 model = glm::rotate(mat, angle, vec);

		lua_newtable(L);
		LuaUtils::RegTable(L, 1, model[0]);
		LuaUtils::RegTable(L, 2, model[1]);
		LuaUtils::RegTable(L, 3, model[2]);
		LuaUtils::RegTable(L, 4, model[3]);

		return 1;
	}

	int MathConnection::Scale(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		glm::mat4 mat;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, 1, 1, mat[0]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 2, mat[1]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 3, mat[2]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 4, mat[3]))
				return luaL_error(L, "argument 1 is expected to be a mat4");
		}
		else return luaL_error(L, "argument 1 is expected to be a mat4");

		glm::vec3 vec;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, 2, "x", vec.x))
				return luaL_error(L, "argument 2 is expected to be a vec3");

			if (!LuaUtils::GetTable(L, 2, "y", vec.y))
				return luaL_error(L, "argument 2 is expected to be a vec3");

			if (!LuaUtils::GetTable(L, 2, "z", vec.z))
				return luaL_error(L, "argument 2 is expected to be a vec3");
		}
		else return luaL_error(L, "argument 2 is expected to be a vec3");

		glm::mat4 model = glm::scale(mat, vec);

		lua_newtable(L);
		LuaUtils::RegTable(L, 1, model[0]);
		LuaUtils::RegTable(L, 2, model[1]);
		LuaUtils::RegTable(L, 3, model[2]);
		LuaUtils::RegTable(L, 4, model[3]);

		return 1;
	}

	int MathConnection::Multiply(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		glm::mat4 mat;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, 1, 1, mat[0]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 2, mat[1]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 3, mat[2]))
				return luaL_error(L, "argument 1 is expected to be a mat4");

			if (!LuaUtils::GetTable(L, 1, 4, mat[3]))
				return luaL_error(L, "argument 1 is expected to be a mat4");
		}
		else return luaL_error(L, "argument 1 is expected to be a mat4");

		glm::vec4 vec;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, 2, "x", vec.x))
				return luaL_error(L, "argument 2 is expected to be a vec4");

			if (!LuaUtils::GetTable(L, 2, "y", vec.y))
				return luaL_error(L, "argument 2 is expected to be a vec4");

			if (!LuaUtils::GetTable(L, 2, "z", vec.z))
				return luaL_error(L, "argument 2 is expected to be a vec4");

			if (!LuaUtils::GetTable(L, 2, "w", vec.w))
				return luaL_error(L, "argument 2 is expected to be a vec4");
		}
		else return luaL_error(L, "argument 2 is expected to be a vec4");

		glm::vec4 result = vec * mat;

		lua_newtable(L);

		lua_pushstring(L, "x");
		lua_pushnumber(L, result.x);
		lua_settable(L, -3);

		lua_pushstring(L, "y");
		lua_pushnumber(L, result.y);
		lua_settable(L, -3);

		lua_pushstring(L, "z");
		lua_pushnumber(L, result.z);
		lua_settable(L, -3);

		lua_pushstring(L, "w");
		lua_pushnumber(L, result.w);
		lua_settable(L, -3);

		return 1;
	}
}}}}