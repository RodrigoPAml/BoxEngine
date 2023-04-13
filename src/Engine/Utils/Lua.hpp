#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Utils {	
namespace Lua {

	/* ----- Register values into tables ----- */

	// Register a str key with a function value into table
	static void RegTable(lua_State* state, const char* name, lua_CFunction function)
	{
		lua_pushstring(state, name);
		lua_pushcfunction(state, function);
		lua_settable(state, -3);
	}

	// Register a str key with a number value into table
	static void RegTable(lua_State* state, const char* name, double number)
	{
		lua_pushstring(state, name);
		lua_pushnumber(state, number);
		lua_settable(state, -3);
	}

	// Register a str key with a number value into table
	static void RegTable(lua_State* state, const char* name, int number)
	{
		lua_pushstring(state, name);
		lua_pushnumber(state, number);
		lua_settable(state, -3);
	}

	// Register a str key with a number value into table
	static void RegTable(lua_State* state, const char* name, float number)
	{
		lua_pushstring(state, name);
		lua_pushnumber(state, number);
		lua_settable(state, -3);
	}

	// Register a str key with a str value into table
	static void RegTable(lua_State* state, const char* name, const char* str)
	{
		lua_pushstring(state, name);
		lua_pushstring(state, str);
		lua_settable(state, -3);
	}

	// Register a str key with a nil value into table
	static void RegTable(lua_State* state, const char* name)
	{
		lua_pushstring(state, name);
		lua_pushnil(state);
		lua_settable(state, -3);
	}

	// Register a str key with a str value into table
	static void RegTable(lua_State* state, const char* name, std::string str)
	{
		lua_pushstring(state, name);
		lua_pushstring(state, str.c_str());
		lua_settable(state, -3);
	}

	// Register a str key with bool a value into table
	static void RegTable(lua_State* state, const char* name, bool val)
	{
		lua_pushstring(state, name);
		lua_pushboolean(state, val);
		lua_settable(state, -3);
	}

	// Register a str key with a table that represents an array of uchar into table
	static void RegTable(lua_State* L, const char* name, unsigned char* value, int size)
	{
		int index = lua_gettop(L);
		lua_pushstring(L, name);
		{
			lua_newtable(L);
			for (int i = 0; i < size; i++)
			{
				lua_pushnumber(L, i+1);
				lua_pushnumber(L, value[i]);
				lua_settable(L, -3);
			}
		}
		lua_settable(L, index);
	}

	// Register a str key with a table that represents an vec4
	static void RegTable(lua_State* L, const char* name, glm::vec4 vec)
	{
		int index = lua_gettop(L);
		lua_pushstring(L, name);
		{
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

			lua_pushstring(L, "z");
			lua_pushnumber(L, vec.w);
			lua_settable(L, -3);
		}
		lua_settable(L, index);
	}

	// Register a str key with a table that represents an vec3
	static void RegTable(lua_State* L, const char* name, glm::vec3 vec)
	{
		int index = lua_gettop(L);
		lua_pushstring(L, name);
		{
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
		}
		lua_settable(L, index);
	}

	// Register a str key with a table that represents an vec2
	static void RegTable(lua_State* L, const char* name, glm::vec2 vec)
	{
		int index = lua_gettop(L);
		lua_pushstring(L, name);
		{
			lua_newtable(L);

			lua_pushstring(L, "x");
			lua_pushnumber(L, vec.x);
			lua_settable(L, -3);

			lua_pushstring(L, "y");
			lua_pushnumber(L, vec.y);
			lua_settable(L, -3);
		}
		lua_settable(L, index);
	}

	// Register a integer key with a function value into table
	static void RegTable(lua_State* state, int name, lua_CFunction function)
	{
		lua_pushnumber(state, name);
		lua_pushcfunction(state, function);
		lua_settable(state, -3);
	}

	// Register a integer key with a number value into table
	static void RegTable(lua_State* state, int name, double number)
	{
		lua_pushnumber(state, name);
		lua_pushnumber(state, number);
		lua_settable(state, -3);
	}
	
	// Register a integer key with a number value into table
	static void RegTable(lua_State* state, int name, int number)
	{
		lua_pushnumber(state, name);
		lua_pushnumber(state, number);
		lua_settable(state, -3);
	}

	// Register a integer key with a number value into table
	static void RegTable(lua_State* state, int name, float number)
	{
		lua_pushnumber(state, name);
		lua_pushnumber(state, number);
		lua_settable(state, -3);
	}

	// Register a integer key with a str value into table
	static void RegTable(lua_State* state, int name, const char* str)
	{
		lua_pushnumber(state, name);
		lua_pushstring(state, str);
		lua_settable(state, -3);
	}

	// Register a integer key with a nil value into table
	static void RegTable(lua_State* state, int name)
	{
		lua_pushnumber(state, name);
		lua_pushnil(state);
		lua_settable(state, -3);
	}

	// Register a integer key with a str value into table
	static void RegTable(lua_State* state, int name, std::string str)
	{
		lua_pushnumber(state, name);
		lua_pushstring(state, str.c_str());
		lua_settable(state, -3);
	}

	// Register a integer key with a bool value into table
	static void RegTable(lua_State* state, int name, bool val)
	{
		lua_pushnumber(state, name);
		lua_pushboolean(state, val);
		lua_settable(state, -3);
	}

	// Register a str key with a table that represents an vec4
	static void RegTable(lua_State* L, int name, glm::vec4 vec)
	{
		int index = lua_gettop(L);
		lua_pushnumber(L, name);
		{
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

			lua_pushstring(L, "z");
			lua_pushnumber(L, vec.w);
			lua_settable(L, -3);
		}
		lua_settable(L, index);
	}

	/* ----- Get values from tables ----- */

	// Get double value from table with str key name
	static bool GetTable(lua_State* L, int table, const char* name, double& value)
	{
		lua_getfield(L, table, name);

		if (lua_isnumber(L, -1))
			value = lua_tonumber(L, -1);
		else
			return false;

		return true;
	}

	// Get float value from table with str key name
	static bool GetTable(lua_State* L, int table, const char* name, float& value)
	{
		lua_getfield(L, table, name);

		if (lua_isnumber(L, -1))
			value = lua_tonumber(L, -1);
		else
			return false;

		return true;
	}

	// Get int value from table with str key name
	static bool GetTable(lua_State* L, int table, const char* name, int& value)
	{
		lua_getfield(L, table, name);

		if (lua_isnumber(L, -1))
			value = lua_tonumber(L, -1);
		else
			return false;

		return true;
	}

	// Get uint value from table with str key name
	static bool GetTable(lua_State* L, int table, const char* name, unsigned int& value)
	{
		lua_getfield(L, table, name);

		if (lua_isnumber(L, -1))
			value = lua_tonumber(L, -1);
		else
			return false;

		return true;
	}

	// Get str value from table with str key name
	static bool GetTable(lua_State* L, int table, const char* name, std::string& value)
	{
		lua_getfield(L, table, name);

		if (lua_isstring(L, -1))
			value = lua_tostring(L, -1);
		else
			return false;

		return true;
	}

	// Get bool value from table with str key name
	static bool GetTable(lua_State* L, int table, const char* name, bool& value)
	{
		lua_getfield(L, table, name);

		if (lua_isboolean(L, -1))
			value = lua_toboolean(L, -1);
		else
			return false;

		return true;
	}

	// Get vec2 value from table with str key name
	static bool GetTable(lua_State* L, int table, const char* name, glm::vec2& value)
	{
		lua_getfield(L, table, name);

		if (lua_istable(L, -1))
		{
			if (!GetTable(L, -1, "x", value.x))
				return false;

			if (!GetTable(L, -2, "y", value.y))
				return false;
		}
		else
			return false;

		return true;
	}

	// Get vec3 value from table with str key name
	static bool GetTable(lua_State* L, int table, const char* name, glm::vec3& value)
	{
		lua_getfield(L, table, name);

		if (lua_istable(L, -1))
		{
			if (!GetTable(L, -1, "x", value.x))
				return false;

			if (!GetTable(L, -2, "y", value.y))
				return false;

			if (!GetTable(L, -3, "z", value.z))
				return false;
		}
		else
			return false;

		return true;
	}

	// Get vec4 value from table with str key name
	static bool GetTable(lua_State* L, int table, const char* name, glm::vec4& value)
	{
		lua_getfield(L, table, name);

		if (lua_istable(L, -1))
		{
			if (!GetTable(L, -1, "x", value.x))
				return false;

			if (!GetTable(L, -2, "y", value.y))
				return false;

			if (!GetTable(L, -3, "z", value.z))
				return false;

			if (!GetTable(L, -4, "w", value.z))
				return false;
		}
		else
			return false;

		return true;
	}

	// Get vec2 value from table with number key name
	static bool GetTable(lua_State* L, int table, int name, glm::vec2& value)
	{
		lua_rawgeti(L, table, name);

		if (lua_istable(L, -1))
		{
			if (!GetTable(L, -1, "x", value.x))
				return false;

			if (!GetTable(L, -2, "y", value.y))
				return false;
		}
		else
			return false;

		return true;
	}

	// Get vec3 value from table with number key name
	static bool GetTable(lua_State* L, int table, int name, glm::vec3& value)
	{
		lua_rawgeti(L, table, name);

		if (lua_istable(L, -1))
		{
			if (!GetTable(L, -1, "x", value.x))
				return false;

			if (!GetTable(L, -2, "y", value.y))
				return false;

			if (!GetTable(L, -3, "z", value.z))
				return false;
		}
		else
			return false;

		return true;
	}

	// Get vec4 value from table with number key name
	static bool GetTable(lua_State* L, int table, int name, glm::vec4& value)
	{
		lua_rawgeti(L, table, name);

		if (lua_istable(L, -1))
		{
			if (!GetTable(L, -1, "x", value.x))
				return false;

			if (!GetTable(L, -2, "y", value.y))
				return false;

			if (!GetTable(L, -3, "z", value.z))
				return false;

			if (!GetTable(L, -4, "w", value.w))
				return false;
		}
		else
			return false;

		return true;
	}

	// Get float array of number from table with str key name
	static bool GetTable(
		lua_State* L, 
		int table, 
		const char* name, 
		float* arr, 
		int size
	)
	{
		lua_getfield(L, table, name);

		if (lua_istable(L, -1))
		{
			for (int i = 1; i <= size; i++)
			{
				lua_rawgeti(L, -i, i);

				if (lua_isnumber(L, -1))
					arr[i] = (lua_tonumber(L, -1));
				else return false;
			}
		}
		else
			return false;

		return true;
	}

	// Get double array of number from table with str key name
	static bool GetTable(
		lua_State* L,
		int table,
		const char* name,
		double* arr,
		int size
	)
	{
		lua_getfield(L, table, name);

		if (lua_istable(L, -1))
		{
			for (int i = 1; i <= size; i++)
			{
				lua_rawgeti(L, -i, i);

				if (lua_isnumber(L, -1))
					arr[i] = (lua_tonumber(L, -1));
				else return false;
			}
		}
		else
			return false;

		return true;
	}

	// Get int array of number from table with str key name
	static bool GetTable(
		lua_State* L,
		int table,
		const char* name,
		int* arr,
		int size
	)
	{
		lua_getfield(L, table, name);

		if (lua_istable(L, -1))
		{
			for (int i = 1; i <= size; i++)
			{
				lua_rawgeti(L, -i, i);

				if (lua_isnumber(L, -1))
					arr[i] = (lua_tonumber(L, -1));
				else return false;
			}
		}
		else
			return false;

		return true;
	}

	// Get uint array of number from table with str key name
	static bool GetTable(
		lua_State* L,
		int table,
		const char* name,
		unsigned int* arr,
		int size
	)
	{
		lua_getfield(L, table, name);

		if (lua_istable(L, -1))
		{
			for (int i = 1; i <= size; i++)
			{
				lua_rawgeti(L, -i, i);

				if (lua_isnumber(L, -1))
					arr[i] = (lua_tonumber(L, -1));
				else return false;
			}
		}
		else
			return false;

		return true;
	}
}}}