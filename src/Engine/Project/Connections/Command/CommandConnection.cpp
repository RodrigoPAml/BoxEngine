#include <BoxEngine.hpp>
#include "CommandConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<CommandConnection> CommandConnection::current;

	CommandConnection::CommandConnection(lua_State* state)
	{
		this->state = state;
	}

	void CommandConnection::Bind()
	{
		lua_newtable(this->state);

		LuaUtils::RegTable(this->state, "enable_vsync", EnableVSync);
		LuaUtils::RegTable(this->state, "disable_vsync", DisableVSync);

		LuaUtils::RegTable(this->state, "enable_depth_testing", EnableDepthTesting);
		LuaUtils::RegTable(this->state, "disable_depth_testing", DisableDepthTesting);
		LuaUtils::RegTable(this->state, "set_depth_testing_mode", SetDepthTestingMode);

		LuaUtils::RegTable(this->state, "enable_culling_face", EnableCullingFace);
		LuaUtils::RegTable(this->state, "disable_culling_face", DisableCullingFace);
		LuaUtils::RegTable(this->state, "set_culling_face_mode", SetCullingFaceMode);

		LuaUtils::RegTable(this->state, "set_primitive_point_size", SetPrimitivePointSize);
		LuaUtils::RegTable(this->state, "set_primitive_line_size", SetPrimitiveLineSize);

		LuaUtils::RegTable(this->state, "set_polygon_draw_mode", SetPolygonDrawMode);

		LuaUtils::RegTable(this->state, "enable_blending", EnableBlending);
		LuaUtils::RegTable(this->state, "disable_blending", DisableBlending);

		lua_setglobal(this->state, "_command_");
	}

	void CommandConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	CommandConnectionPtr CommandConnection::Get()
	{
		return current.lock();
	}

	void CommandConnection::Set(CommandConnectionPtr instance)
	{
		current = instance;
	}
	
	int CommandConnection::EnableVSync(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		GPU::Command::EnableVSync();

		return 0;
	}
	
	int CommandConnection::DisableVSync(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		GPU::Command::DisableVSync();

		return 0;
	}
	
	int CommandConnection::EnableDepthTesting(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		GPU::Command::EnableDepthTesting();

		return 0;
	}

	int CommandConnection::DisableDepthTesting(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		GPU::Command::DisableDepthTesting();

		return 0;
	}
	
	int CommandConnection::SetDepthTestingMode(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isstring(L, 1))
		{
			GPU::DepthTestingMode mode = GPU::DepthTestingFromString(lua_tostring(L, 1));

			GPU::Command::SetDepthTestingMode(mode);
		}
		else return luaL_error(L, "argument 1 needs to be a string");

		return 0;
	}
	
	int CommandConnection::EnableCullingFace(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		GPU::Command::EnableCullingFace();

		return 0;
	}

	int CommandConnection::DisableCullingFace(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		GPU::Command::DisableCullingFace();

		return 0;
	}

	int CommandConnection::SetCullingFaceMode(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isstring(L, 1))
		{
			GPU::CullingFaceMode mode = GPU::CullingFaceFromString(lua_tostring(L, 1));

			GPU::Command::SetCullingFaceMode(mode);
		}
		else return luaL_error(L, "argument 1 needs to be a string");

		return 0;
	}

	int CommandConnection::SetPrimitivePointSize(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			int number = lua_tonumber(L, 1);

			GPU::Command::SetPrimitivePointSize(number);
		}
		else return luaL_error(L, "argument 1 needs to be a number");

		return 0;
	}

	int CommandConnection::SetPrimitiveLineSize(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			int number = lua_tonumber(L, 1);

			GPU::Command::SetPrimitiveLineSize(number);
		}
		else return luaL_error(L, "argument 1 needs to be a number");

		return 0;
	}

	int CommandConnection::SetPolygonDrawMode(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isstring(L, 1))
		{
			GPU::Command::SetPolygonDrawMode(GPU::PolygonModeFromString(lua_tostring(L, 1)));
		}
		else return luaL_error(L, "argument 1 needs to be a string");

		return 0;
	}

	int CommandConnection::EnableBlending(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		GPU::Command::EnableBlending();

		return 0;
	}

	int CommandConnection::DisableBlending(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		GPU::Command::DisableBlending();

		return 0;
	}
}}}}