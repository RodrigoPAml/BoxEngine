#include <BoxEngine.hpp>
#include "GoScriptConnection.hpp"

namespace BoxEngine {
namespace Engine {
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
		LuaUtils::RegTable(this->state, "current", GetId);
		LuaUtils::RegTable(this->state, "create", CreateGo);
		LuaUtils::RegTable(this->state, "destroy", DestroyGo);
		LuaUtils::RegTable(this->state, "create_copy", Copy);
		LuaUtils::RegTable(this->state, "get", GetGo);
		LuaUtils::RegTable(this->state, "set_active", SetActive);
		LuaUtils::RegTable(this->state, "set_name", SetName);
		LuaUtils::RegTable(this->state, "change_father", ChangeGoFather);
		LuaUtils::RegTable(this->state, "load_scripts", LoadScripts);
		LuaUtils::RegTable(this->state, "change_index", ChangeGoIndex);

		lua_setglobal(this->state, "_go_");

		// Script manager
		lua_newtable(this->state);

		LuaUtils::RegTable(this->state, "get", GetScript);
		LuaUtils::RegTable(this->state, "add", AddScript);
		LuaUtils::RegTable(this->state, "remove", RemoveScript);
		LuaUtils::RegTable(this->state, "change_index", RemoveScript);

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
			LuaUtils::GetTable(L, 1, "name", goName);
			LuaUtils::GetTable(L, 1, "active", active);

			if (top == 3)
			{
				if (!LuaUtils::GetTable(L, 1, "father_id", fatherId))
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
			LuaUtils::RegTable(L, "id", id);
			LuaUtils::RegTable(L, "active", go->GetActive());

			if (father != nullptr)
				LuaUtils::RegTable(L, "father_id", father->GetId());
			else
				LuaUtils::RegTable(L, "father_id");
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

	int GoScriptConnection::Copy(lua_State* L)
	{
		// Destroy go and return if succeed or not
		auto top = lua_gettop(L);

		if (top != 1 && top != 2)
			return luaL_error(L, "expecting 1 or 2 arguments in function call");

		std::string goId = "";
		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		std::string fatherId = "";
		if (lua_isstring(L, 2))
			fatherId = lua_tostring(L, 2);

		std::string result = Project::GetCurrentProject()->DuplicateGo(goId, fatherId);

		if (result == "")
			lua_pushnil(L);
		else
			lua_pushstring(L, result.c_str());

		return 1;
	}

	int GoScriptConnection::SetActive(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string goId = "";
		bool active = false;

		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		if (lua_isboolean(L, 2))
			active = lua_toboolean(L, 2);
		else return luaL_error(L, "argument 2 is expected to be bool");

		GameObjectPtr go = Project::GetCurrentProject()->GetGameObject(goId);

		if (go == nullptr)
			lua_pushboolean(L, false);
		else
		{
			go->SetActive(active);

			lua_pushboolean(L, true);
		}

		return 1;
	}

	int GoScriptConnection::SetName(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string goId = "";
		std::string name = "";

		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		if (lua_isstring(L, 2))
			name = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be string");

		GameObjectPtr go = Project::GetCurrentProject()->GetGameObject(goId);

		if (go == nullptr)
			lua_pushboolean(L, false);
		else
		{
			go->SetName(name);
			lua_pushboolean(L, true);
		}

		return 1;
	}

	int GoScriptConnection::ChangeGoFather(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2 && top != 1)
			return luaL_error(L, "expecting 1 or 2 arguments in function call");

		std::string goId = "";
		std::string fatherId = "";

		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		if (!lua_isnoneornil(L, 2) && !lua_isstring(L, 2))
			return luaL_error(L, "argument 2 is expected to be a string");
		else if(lua_isstring(L, 2))
			fatherId = lua_tostring(L, 2);

		GameObjectPtr go = Project::GetCurrentProject()->GetGameObject(goId);

		if (go == nullptr)
			lua_pushboolean(L, false);
		else
		{
			Project::GetCurrentProject()->ChangeGoFather(go->GetId(), fatherId);
			lua_pushboolean(L, true);
		}

		return 1;
	}

	int GoScriptConnection::ChangeGoIndex(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string goId = "";
		int index = 0;

		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		if (!lua_isnumber(L, 2))
			return luaL_error(L, "argument 2 is expected to be a number");
		else
			index = lua_tonumber(L, 2);

		GameObjectPtr go = Project::GetCurrentProject()->GetGameObject(goId);

		if (go == nullptr)
			lua_pushboolean(L, false);
		else
		{
			Project::GetCurrentProject()->ChangeGoPosition(go->GetId(), index);
			lua_pushboolean(L, true);
		}

		return 1;
	}

	int GoScriptConnection::LoadScripts(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string goId = "";

		if (lua_isstring(L, 1))
			goId = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");
		
		bool result = Project::GetCurrentProject()->PreLoadScripts(goId);
		
		if(!result)
			return luaL_error(L, "internal error when loading scripts at runtime");

		return 0;
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

			LuaUtils::RegTable(L, "id", go->GetId());
			LuaUtils::RegTable(L, "active", go->GetActive());
			LuaUtils::RegTable(L, "name", go->GetName());

			if (father != nullptr)
				LuaUtils::RegTable(L, "father_id", father->GetId());
			else
				LuaUtils::RegTable(L, "father_id");

			LuaUtils::RegTable(L, "is_to_destroy", go->IsToDestroy());

			// Inner table for scripts info
			int index = lua_gettop(L);
			lua_pushstring(L, "scripts");
			{
				lua_newtable(L);
				auto scripts = go->GetScripts();
				for (int i = 0; i < scripts.size(); i++)
					LuaUtils::RegTable(L, i+1, scripts[i]->GetName());
			}
			lua_settable(L, index);

			// childrens info
			index = lua_gettop(L);
			lua_pushstring(L, "childrens");
			{
				lua_newtable(L);

				auto childrens = go->GetChildrens();
				for (int i = 0; i < childrens.size(); i++)
					LuaUtils::RegTable(L, i+1, childrens[i]->GetId());
			}
			lua_settable(L, index);
		}

		return 1;
	}

	int GoScriptConnection::GetScript(lua_State* L)
	{
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

		LuaUtils::RegTable(L, "name", script->GetName());
		LuaUtils::RegTable(L, "path", script->GetPath());
		LuaUtils::RegTable(L, "state", ScriptStateToString(script->GetState()));
		LuaUtils::RegTable(L, "is_started", script->IsStarted());

		return 1;
	}

	int GoScriptConnection::AddScript(lua_State* L)
	{
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

	int GoScriptConnection::ChangeScriptIndex(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string goId = "";
		std::string scriptName = "";
		int newIndex = 0;

		if (lua_isstring(L, 1))
			scriptName = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		if (lua_isstring(L, 2))
			scriptName = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		if (lua_isnumber(L, 3))
			newIndex = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		Project::GetCurrentProject()->ChangeScriptPosition(goId, scriptName, newIndex);

		return 0;
	}
}}}}