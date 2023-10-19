#include <BoxEngine.hpp>
#include "ImporterConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<ImporterConnection> ImporterConnection::current;

	ImporterConnection::ImporterConnection(lua_State* state)
	{
		this->state = state;
	}

	void ImporterConnection::Bind()
	{
		lua_newtable(this->state);

		LuaUtils::RegTable(this->state, "open", Open);

		lua_setglobal(this->state, "_importer_");
	}

	void ImporterConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	ImporterConnectionPtr ImporterConnection::Get()
	{
		return current.lock();
	}

	void ImporterConnection::Set(ImporterConnectionPtr instance)
	{
		current = instance;
	}

	int ImporterConnection::Open(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");
		
		std::string path = "";
		if (lua_isstring(L, 1))
			path = lua_tostring(L, 1);
		else return luaL_error(L, "expecting 1 to be a string");

		Importer::ObjectPtr obj = nullptr;
		auto instance = ImporterConnection::Get();

		try
		{
			obj = Importer::Importer::Load(path);

			instance->objs[++instance->currentId] = obj;
			lua_pushnumber(L, instance->currentId);
			return 1;
		}
		catch (std::exception)
		{
			lua_pushnil(L);
			obj = nullptr;
			instance = nullptr;
			return 1;
		}

		return 1;
	}
}}}}