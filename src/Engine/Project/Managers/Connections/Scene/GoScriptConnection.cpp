#include <BoxEngine.hpp>
#include "GoScriptConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<GoScriptConnection> GoScriptConnection::current;

	GoScriptConnection::GoScriptConnection(lua_State* state)
	{
		this->state = state;
	}

	void GoScriptConnection::Bind()
	{
		// Go manager
		lua_newtable(this->state);

		// Current go id
		Utils::Lua::RegTable(this->state, "current", GetId);
		Utils::Lua::RegTable(this->state, "create", CreateGo);
		Utils::Lua::RegTable(this->state, "destroy", DestroyGo);
		Utils::Lua::RegTable(this->state, "get", GetGo);
		Utils::Lua::RegTable(this->state, "update", UpdateGo);
	
		lua_setglobal(this->state, "_go_");

		// Script manager
		lua_newtable(this->state);

		Utils::Lua::RegTable(this->state, "get", GetScript);
		Utils::Lua::RegTable(this->state, "add", AddScript);
		Utils::Lua::RegTable(this->state, "remove", RemoveScript);

		lua_setglobal(this->state, "_script_");
	}

	void GoScriptConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	GoScriptConnectionPtr GoScriptConnection::Get()
	{
		return current.lock();
	}

	void GoScriptConnection::Set(GoScriptConnectionPtr instance)
	{
		current = instance;
	}

	int GoScriptConnection::GetId(lua_State* L)
	{
		// Get current id
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no arguments in function");

		auto go = GoScriptConnection::current.lock()->currentGo.lock();

		if (go != nullptr)
			lua_pushstring(L, go->GetId().c_str());
		else
			lua_pushnil(L);

		return 1;
	}

	int GoScriptConnection::CreateGo(lua_State* L)
	{
		// Create go function
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string goName = "";
		std::string fatherId = "";
		bool active = false;

		if (lua_istable(L, 1))
		{
			if (!Utils::Lua::GetTable(L, 1, "name", goName))
				return luaL_error(L, "argument name needs to exists and be a string");

			if (!Utils::Lua::GetTable(L, 1, "active", active))
				return luaL_error(L, "argument active needs to exists and be a boolean");

			if (top == 3)
			{
				if (!Utils::Lua::GetTable(L, 1, "father_id", fatherId))
					return luaL_error(L, "argument father_id needs to be a string");
			}
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

		GameObjectPtr go = Project::GetCurrentProject()->AddGameObject(goName, active, fatherId);

		// If failed for some reason return nil
		if (go == nullptr)
			lua_pushnil(L);
		else
		{
			auto id = go->GetId();
			auto father = go->GetFather();

			lua_newtable(L);
			Utils::Lua::RegTable(L, "id", id);
			Utils::Lua::RegTable(L, "active", go->GetActive());

			if (father != nullptr)
				Utils::Lua::RegTable(L, "father_id", father->GetId());
			else
				Utils::Lua::RegTable(L, "father_id");
		}

		return 1;
	}

	int GoScriptConnection::DestroyGo(lua_State* L)
	{
		// Destroy go and return if succeed or not
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string goId = "";
		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		bool ret = Project::GetCurrentProject()->DestroyGameObject(goId);

		lua_pushboolean(L, ret);

		return 1;
	}

	int GoScriptConnection::UpdateGo(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string goId = "";
		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		if (!lua_istable(L, 2))
			return luaL_error(L, "argument 2 is expected to be a table");

		GameObjectPtr go = Project::GetCurrentProject()->GetGameObject(goId);

		if (go == nullptr)
			lua_pushboolean(L, false);
		else
		{
			// changes active of go
			lua_getfield(L, 2, "active");

			if (lua_isboolean(L, -1))
				go->SetActive(lua_toboolean(L, -1));
			else if (!lua_isnil(L, -1))
			{
				go = nullptr;
				return luaL_error(L, "argument active needs to be a boolean");
			}

			// changes name of go
			lua_getfield(L, 2, "name");

			if (lua_isstring(L, -1))
				go->SetName(lua_tostring(L, -1));
			else if (!lua_isnil(L, -1))
			{
				go = nullptr;
				return luaL_error(L, "argument name needs to be a string");
			}

			lua_pushboolean(L, true);
		}

		return 1;
	}

	int GoScriptConnection::GetGo(lua_State* L)
	{
		// Return information of the go, it childrens and scripts
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string goId = "";
		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		GameObjectPtr go = Project::GetCurrentProject()->GetGameObject(goId);

		if (go == nullptr)
			lua_pushnil(L);
		else
		{
			auto father = go->GetFather();
			auto scripts = go->GetScripts();

			// Table for the go info
			lua_newtable(L);

			Utils::Lua::RegTable(L, "id", go->GetId());
			Utils::Lua::RegTable(L, "active", go->GetActive());

			if (father != nullptr)
				Utils::Lua::RegTable(L, "father_id", father->GetId());
			else
				Utils::Lua::RegTable(L, "father_id");

			Utils::Lua::RegTable(L, "is_to_destroy", go->IsToDestroy());

			// Inner table for scripts info
			int index = lua_gettop(L);
			lua_pushstring(L, "scripts");
			{
				lua_newtable(L);
				auto scripts = go->GetScripts();
				for (int i = 0; i < scripts.size(); i++)
					Utils::Lua::RegTable(L, i, scripts[i]->GetName());
			}
			lua_settable(L, index);

			// childrens info
			index = lua_gettop(L);
			lua_pushstring(L, "childrens");
			{
				lua_newtable(L);

				auto childrens = go->GetChildrens();
				for (int i = 0; i < childrens.size(); i++)
					Utils::Lua::RegTable(L, i, childrens[i]->GetId());
			}
			lua_settable(L, index);
		}

		return 1;
	}

	int GoScriptConnection::GetScript(lua_State* L)
	{
		// Return information of the script
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string goId = "";
		std::string scriptName = "";

		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		if (lua_isstring(L, 2))
			scriptName = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be string");

		GameObjectPtr go = Project::GetCurrentProject()->GetGameObject(goId);

		if (go == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		auto scripts = go->GetScripts();
		auto scriptIt = std::find_if(scripts.begin(), scripts.end(), [scriptName](const ScriptPtr& script) { return scriptName == script->GetName(); });

		ScriptPtr script = *scriptIt;

		if (script == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		// Table for the go info
		lua_newtable(L);

		Utils::Lua::RegTable(L, "name", script->GetName());
		Utils::Lua::RegTable(L, "path", script->GetPath());
		Utils::Lua::RegTable(L, "state", ScriptStateToString(script->GetState()));
		Utils::Lua::RegTable(L, "is_started", script->IsStarted());

		return 1;
	}

	int GoScriptConnection::AddScript(lua_State* L)
	{
		// Return information of the script
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string goId = "";
		std::string scriptName = "";

		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		if (lua_isstring(L, 2))
			scriptName = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be string");

		lua_pushboolean(L, Project::GetCurrentProject()->AddScript(goId, scriptName));

		return 1;
	}

	int GoScriptConnection::RemoveScript(lua_State* L)
	{
		// Return information of the script
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string goId = "";
		std::string scriptName = "";

		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		if (lua_isstring(L, 2))
			scriptName = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be string");

		lua_pushboolean(L, Project::GetCurrentProject()->DestroyScript(goId, scriptName));

		return 1;
	}
}}}