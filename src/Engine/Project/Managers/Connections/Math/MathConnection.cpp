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

		LuaUtils::RegTable(this->state, "make_mat4", MakeMat4);
		LuaUtils::RegTable(this->state, "make_identity_mat4", MakeIdentityMat4);
		LuaUtils::RegTable(this->state, "translate_mat4", TranslateMat4);
		LuaUtils::RegTable(this->state, "rotate_mat4", RotateMat4);
		LuaUtils::RegTable(this->state, "scale_mat4", ScaleMat4);

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

	int MathConnection::MakeMat4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::mat4 mat = glm::mat4();

		// Register four tables direct in this table
		lua_newtable(L);
		LuaUtils::RegTable(L, 1, mat[0]);
		LuaUtils::RegTable(L, 2, mat[1]);
		LuaUtils::RegTable(L, 3, mat[2]);
		LuaUtils::RegTable(L, 4, mat[3]);

		return 1;
	}

	int MathConnection::MakeIdentityMat4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		glm::mat4 mat = glm::mat4(1.0f);

		// Register four tables direct in this table
		lua_newtable(L);
		LuaUtils::RegTable(L, 1, mat[0]);
		LuaUtils::RegTable(L, 2, mat[1]);
		LuaUtils::RegTable(L, 3, mat[2]);
		LuaUtils::RegTable(L, 4, mat[3]);

		return 1;
	}
	
	int MathConnection::TranslateMat4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		glm::mat4 mat;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, 1, 1, mat[0]))
				return luaL_error(L, "argument 1 is expected to be a table, missing vec4 1");

			if (!LuaUtils::GetTable(L, 1, 2, mat[1]))
				return luaL_error(L, "argument 1 is expected to be table, missing vec4 2");

			if (!LuaUtils::GetTable(L, 1, 3, mat[2]))
				return luaL_error(L, "argument 1 is expected to be a table, missing vec4 3");

			if (!LuaUtils::GetTable(L, 1, 4, mat[3]))
				return luaL_error(L, "argument 1 is expected to be a table, missing vec4 4");
		}
		else return luaL_error(L, "argument 1 is expected to be a table with mat4 format");

		glm::vec3 vec;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, 2, "x", vec.x))
				return luaL_error(L, "argument 2 is expected to be a table, missing x");

			if (!LuaUtils::GetTable(L, 2, "y", vec.y))
				return luaL_error(L, "argument 2 is expected to be a table, missing y");

			if (!LuaUtils::GetTable(L, 2, "z", vec.z))
				return luaL_error(L, "argument 2 is expected to be a table, missing z");
		}
		else return luaL_error(L, "argument 2 is expected to be a table");

		glm::mat4 model = glm::translate(mat, vec);

		// Register four tables direct in this table
		lua_newtable(L);
		LuaUtils::RegTable(L, 1, model[0]);
		LuaUtils::RegTable(L, 2, model[1]);
		LuaUtils::RegTable(L, 3, model[2]);
		LuaUtils::RegTable(L, 4, model[3]);

		return 1;
	}

	int MathConnection::RotateMat4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		glm::mat4 mat;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, 1, 1, mat[0]))
				return luaL_error(L, "argument 1 is expected to be a table, missing vec4 1");

			if (!LuaUtils::GetTable(L, 1, 2, mat[1]))
				return luaL_error(L, "argument 1 is expected to be table, missing vec4 2");

			if (!LuaUtils::GetTable(L, 1, 3, mat[2]))
				return luaL_error(L, "argument 1 is expected to be a table, missing vec4 3");

			if (!LuaUtils::GetTable(L, 1, 4, mat[3]))
				return luaL_error(L, "argument 1 is expected to be a table, missing vec4 4");
		}
		else return luaL_error(L, "argument 1 is expected to be a table with mat4 format");

		glm::vec3 vec;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, 2, "x", vec.x))
				return luaL_error(L, "argument 2 is expected to be a table, missing x");

			if (!LuaUtils::GetTable(L, 2, "y", vec.y))
				return luaL_error(L, "argument 2 is expected to be a table, missing y");

			if (!LuaUtils::GetTable(L, 2, "z", vec.z))
				return luaL_error(L, "argument 2 is expected to be a table, missing z");
		}
		else return luaL_error(L, "argument 2 is expected to be a table");

		float angle;
		if (lua_isnumber(L, 3))
			angle = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		glm::mat4 model = glm::rotate(mat, angle, vec);

		// Register four tables direct in this table
		lua_newtable(L);
		LuaUtils::RegTable(L, 1, model[0]);
		LuaUtils::RegTable(L, 2, model[1]);
		LuaUtils::RegTable(L, 3, model[2]);
		LuaUtils::RegTable(L, 4, model[3]);

		return 1;
	}

	int MathConnection::ScaleMat4(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		glm::mat4 mat;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, 1, 1, mat[0]))
				return luaL_error(L, "argument 1 is expected to be a table, missing vec4 1");

			if (!LuaUtils::GetTable(L, 1, 2, mat[1]))
				return luaL_error(L, "argument 1 is expected to be table, missing vec4 2");

			if (!LuaUtils::GetTable(L, 1, 3, mat[2]))
				return luaL_error(L, "argument 1 is expected to be a table, missing vec4 3");

			if (!LuaUtils::GetTable(L, 1, 4, mat[3]))
				return luaL_error(L, "argument 1 is expected to be a table, missing vec4 4");
		}
		else return luaL_error(L, "argument 1 is expected to be a table with mat4 format");

		glm::vec3 vec;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, 2, "x", vec.x))
				return luaL_error(L, "argument 2 is expected to be a table, missing x");

			if (!LuaUtils::GetTable(L, 2, "y", vec.y))
				return luaL_error(L, "argument 2 is expected to be a table, missing y");

			if (!LuaUtils::GetTable(L, 2, "z", vec.z))
				return luaL_error(L, "argument 2 is expected to be a table, missing z");
		}
		else return luaL_error(L, "argument 2 is expected to be a table");

		glm::mat4 model = glm::scale(mat, vec);

		// Register four tables direct in this table
		lua_newtable(L);
		LuaUtils::RegTable(L, 1, model[0]);
		LuaUtils::RegTable(L, 2, model[1]);
		LuaUtils::RegTable(L, 3, model[2]);
		LuaUtils::RegTable(L, 4, model[3]);

		return 1;
	}
}}}}