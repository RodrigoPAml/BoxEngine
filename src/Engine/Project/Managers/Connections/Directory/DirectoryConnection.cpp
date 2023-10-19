#include <BoxEngine.hpp>
#include "DirectoryConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<DirectoryConnection> DirectoryConnection::current;

	DirectoryConnection::DirectoryConnection(lua_State* state)
	{
		this->state = state;
	}

	void DirectoryConnection::Bind()
	{
		lua_newtable(this->state);

		LuaUtils::RegTable(this->state, "read_file", ReadFile);
		LuaUtils::RegTable(this->state, "create_file", CreateFile);
		LuaUtils::RegTable(this->state, "create_folder", CreateFolder);

		LuaUtils::RegTable(this->state, "move", Move);
		LuaUtils::RegTable(this->state, "copy", Copy);
		LuaUtils::RegTable(this->state, "delete", Delete);

		LuaUtils::RegTable(this->state, "is_file", IsFile);
		LuaUtils::RegTable(this->state, "is_dir", IsDir);
		LuaUtils::RegTable(this->state, "exists", Exists);

		LuaUtils::RegTable(this->state, "get_current_path", GetCurrentPath);
		LuaUtils::RegTable(this->state, "get_base_path", GetBasePath);
		LuaUtils::RegTable(this->state, "get_assets_path", GetAssetsPath);
		LuaUtils::RegTable(this->state, "get_logs_path", GetLogsPath);

		LuaUtils::RegTable(this->state, "list_dir", ListDirectories);

		LuaUtils::RegTable(this->state, "reduce_path_by", RemovePartsFromPath);
		LuaUtils::RegTable(this->state, "get_path_or_file_name", GetLastPartFromPath);
		LuaUtils::RegTable(this->state, "get_file_name_ext", GetExtensionFromPath);
		LuaUtils::RegTable(this->state, "get_file_name_no_ext", GetLastPartFromPathNoExt);

		LuaUtils::RegTable(this->state, "exec", Exec);

		lua_setglobal(this->state, "_dir_");
	}

	void DirectoryConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	DirectoryConnectionPtr DirectoryConnection::Get()
	{
		return current.lock();
	}

	void DirectoryConnection::Set(DirectoryConnectionPtr instance)
	{
		current = instance;
	}

	int DirectoryConnection::ReadFile(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string content = "";
		bool open = false;
		if (lua_isstring(L, 1))
		{
			std::string filename = lua_tostring(L, 1);
			
			content = Utils::Directory::ReadFile(filename, &open);
		}
		else 
			return luaL_error(L, "argument 1 needs to be a string");

		lua_newtable(L);
		LuaUtils::RegTable(L, "open", open);
		LuaUtils::RegTable(L, "content", content);

		return 1;
	}
	
	int DirectoryConnection::CreateFile(lua_State* L)
	{
		if (lua_gettop(L) != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string filename = "";
		std::string content = "";
		bool success = false;

		if (lua_isstring(L, 2))
		{
			content = lua_tostring(L, 2);
		}
		else if(!lua_isnoneornil(L, 2))
			return luaL_error(L, "argument 2 needs to be a string if informed");

		if (lua_isstring(L, 1))
		{
			filename = lua_tostring(L, 1);

			success = Utils::Directory::CreateFile(filename, content);
		}
		else
			return luaL_error(L, "argument 1 needs to be a string");

		lua_pushboolean(L, success);
		return 1;
	}

	int DirectoryConnection::CreateFolder(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string foldername = "";
		bool success = false;

		if (lua_isstring(L, 1))
		{
			foldername = lua_tostring(L, 1);

			success = Utils::Directory::CreateDirectory(foldername);
		}
		else
			return luaL_error(L, "argument 1 needs to be a string");

		lua_pushboolean(L, success);
		return 1;
	}

	int DirectoryConnection::Move(lua_State* L)
	{
		if (lua_gettop(L) != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string from = "";
		std::string to = "";

		if (lua_isstring(L, 1))
			from = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		if (lua_isstring(L, 2))
			to = lua_tostring(L, 2);
		else
			return luaL_error(L, "argument 2 needs to be a string");

		lua_pushboolean(L, Utils::Directory::Move(from, to));
		return 1;
	}

	int DirectoryConnection::Copy(lua_State* L)
	{
		if (lua_gettop(L) != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string from = "";
		std::string to = "";

		if (lua_isstring(L, 1))
			from = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		if (lua_isstring(L, 2))
			to = lua_tostring(L, 2);
		else
			return luaL_error(L, "argument 2 needs to be a string");

		lua_pushboolean(L, Utils::Directory::Copy(from, to));
		return 1;
	}

	int DirectoryConnection::Delete(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string filename = "";

		if (lua_isstring(L, 1))
			filename = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		lua_pushboolean(L, Utils::Directory::Delete(filename));
		return 1;
	}

	int DirectoryConnection::IsFile(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string filename = "";

		if (lua_isstring(L, 1))
			filename = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		lua_pushboolean(L, Utils::Directory::IsFile(filename));
		return 1;
	}

	int DirectoryConnection::IsDir(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string filename = "";

		if (lua_isstring(L, 1))
			filename = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		lua_pushboolean(L, Utils::Directory::IsDirectory(filename));
		return 1;
	}

	int DirectoryConnection::Exists(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string filename = "";

		if (lua_isstring(L, 1))
			filename = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		lua_pushboolean(L, Utils::Directory::Exists(filename));
		return 1;
	}

	int DirectoryConnection::GetCurrentPath(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		lua_pushstring(L, Utils::Directory::GetCurrentPath().c_str());
		return 1;
	}

	int DirectoryConnection::GetBasePath(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		lua_pushstring(L, Project::GetCurrentProject()->GetBasePath().c_str());
		return 1;
	}

	int DirectoryConnection::GetAssetsPath(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		lua_pushstring(L, Project::GetCurrentProject()->GetAssetsPath().c_str());
		return 1;
	}

	int DirectoryConnection::GetLogsPath(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no argument in function call");

		lua_pushstring(L, Project::GetCurrentProject()->GetLogsPath().c_str());
		return 1;
	}

	int DirectoryConnection::ListDirectories(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string path = "";

		if (lua_isstring(L, 1))
			path = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		if (Utils::Directory::IsDirectory(path))
		{
			lua_newtable(L);
			int idx = 0;
			for (std::string& item : Utils::Directory::ListDirectories(path, false))
			{
				LuaUtils::RegTable(L, idx, item);
				idx++;
			}
		}
		else lua_pushnil(L);


		return 1;
	}

	int DirectoryConnection::RemovePartsFromPath(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string filename = "";
		unsigned int n = 0;

		if (lua_isstring(L, 1))
			filename = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		if (lua_isnumber(L, 2))
			n = lua_tonumber(L, 2);
		else
			return luaL_error(L, "argument 2 needs to be a number");

		lua_pushstring(L, Utils::Directory::RemovePartsFromPath(filename, n).c_str());
		return 1;
	}

	int DirectoryConnection::GetExtensionFromPath(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string filename = "";

		if (lua_isstring(L, 1))
			filename = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		lua_pushstring(L, Utils::Directory::GetExtensionFromPath(filename).c_str());
		return 1;
	}

	int DirectoryConnection::GetLastPartFromPath(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string filename = "";

		if (lua_isstring(L, 1))
			filename = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		lua_pushstring(L, Utils::Directory::GetLastPartFromPath(filename).c_str());
		return 1;
	}

	int DirectoryConnection::GetLastPartFromPathNoExt(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string filename = "";

		if (lua_isstring(L, 1))
			filename = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		lua_pushstring(L, Utils::Directory::GetLastPartFromPathNoExtension(filename).c_str());
		return 1;
	}
	
	int DirectoryConnection::Exec(lua_State* L)
	{
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string command = "";

		if (lua_isstring(L, 1))
			command = lua_tostring(L, 1);
		else
			return luaL_error(L, "argument 1 needs to be a string");

		Utils::Directory::Execute(command);

		return 0;
	}
}}}}