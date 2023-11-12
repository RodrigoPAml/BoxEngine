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
		LuaUtils::RegTable(this->state, "destroy", Close);

		LuaUtils::RegTable(this->state, "get_obj_info", GetObject);
		LuaUtils::RegTable(this->state, "get_meshes", GetMeshes);
		LuaUtils::RegTable(this->state, "get_materials", GetMaterials);

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

	Importer::ObjectPtr ImporterConnection::FindObj(long id)
	{
		auto instance = ImporterConnection::Get();

		return instance->objs.contains(id) ? instance->objs[id] : nullptr;
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
		auto textureConnection = TextureConnection::Get();
		auto vertexConnection = VertexConnection::Get();

		try
		{
			obj = Importer::Importer::Load(path);

			for (auto& mesh : obj->meshes)
				vertexConnection->Register(mesh->GetMesh());

			for (auto& mtl : obj->materials)
				textureConnection->Register(mtl->GetAlbedoTexture());

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

	int ImporterConnection::Close(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1 && top != 2)
			return luaL_error(L, "expecting 1 or 2 arguments in function call");

		bool deleteRefs = true;

		if (lua_isboolean(L, 2) && !lua_isnoneornil(L, 2))
			deleteRefs = lua_toboolean(L, 2);

		if (lua_isnumber(L, 1))
		{
			auto instance = ImporterConnection::Get();
			auto id = lua_tonumber(L, 1);

			if (deleteRefs)
			{
				Importer::ObjectPtr obj = instance->objs.contains(id) ? instance->objs[id] : nullptr;

				if (obj == nullptr)
					return 0;

				auto textureConnection = TextureConnection::Get();
				auto vertexConnection = VertexConnection::Get();

				for (auto& mesh : obj->meshes)
					vertexConnection->Delete(mesh->GetMesh());

				for (auto& mtl : obj->materials)
					textureConnection->Delete(mtl->GetAlbedoTexture());
			}

			instance->objs.erase(id);
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 0;
	}
	
	int ImporterConnection::GetObject(lua_State* L)
	{
		// Return information of meshes
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		long objId = 0;
		if (lua_isnumber(L, 1))
			objId = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be number");

		auto instance = ImporterConnection::Get();
		Importer::ObjectPtr obj = instance->objs.contains(objId) ? instance->objs[objId] : nullptr;

		if (obj == nullptr)
			lua_pushnil(L);
		else
		{
			// Table for the go info
			lua_newtable(L);
			LuaUtils::RegTable(L, "path", obj->basePath);
			LuaUtils::RegTable(L, "name", Utils::Directory::GetLastPartFromPath(obj->basePath));
			LuaUtils::RegTable(L, "mesh_count", (int)obj->meshes.size());
			LuaUtils::RegTable(L, "material_count", (int)obj->materials.size());
		}

		return 1;
	}

	int ImporterConnection::GetMeshes(lua_State* L)
	{
		// Return information of meshes
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		long objId = 0;
		if (lua_isnumber(L, 1))
			objId = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be number");

		auto instance = ImporterConnection::Get();
		Importer::ObjectPtr obj = instance->objs.contains(objId) ? instance->objs[objId] : nullptr;

		if (obj == nullptr)
			lua_pushnil(L);
		else
		{
			auto meshes = obj->meshes;
			auto vertexConnection = VertexConnection::Get();

			// Table for the go info
			lua_newtable(L); 
			for (int i = 0; i < meshes.size(); i++)
			{
				int index = lua_gettop(L);
				lua_pushnumber(L, i+1);
				{
					lua_newtable(L);

					lua_pushstring(L, "name");
					lua_pushstring(L, meshes[i]->GetName().c_str());
					lua_settable(L, -3);

					auto mesh = meshes[i]->GetMesh();

					if (mesh != nullptr)
					{
						lua_pushstring(L, "vertex_id");
						lua_pushnumber(L, vertexConnection->FindId(mesh));
						lua_settable(L, -3);
					}

					lua_pushstring(L, "material_index");
					lua_pushnumber(L, meshes[i]->GetMaterialIndex());
					lua_settable(L, -3);

					lua_pushstring(L, "index");
					lua_pushnumber(L, i);
					lua_settable(L, -3);

					LuaUtils::RegTable(L, "min_box", meshes[i]->GetMinBox());
					LuaUtils::RegTable(L, "max_box", meshes[i]->GetMaxBox());
				}
				lua_settable(L, index);
			}
		}

		return 1;
	}

	int ImporterConnection::GetMaterials(lua_State* L)
	{
		// Return information of meshes
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		long objId = 0;
		if (lua_isnumber(L, 1))
			objId = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be number");

		auto instance = ImporterConnection::Get();
		Importer::ObjectPtr obj = instance->objs.contains(objId) ? instance->objs[objId] : nullptr;

		if (obj == nullptr)
			lua_pushnil(L);
		else
		{
			auto materials = obj->materials;
			auto textureConnection = TextureConnection::Get();

			// Table for the go info
			lua_newtable(L);
			for (int i = 0; i < materials.size(); i++)
			{
				int index = lua_gettop(L);
				lua_pushnumber(L, i + 1);
				{
					lua_newtable(L);

					lua_pushstring(L, "name");
					lua_pushstring(L, materials[i]->GetName().c_str());
					lua_settable(L, -3);

					auto texAlbedo = materials[i]->GetAlbedoTexture();

					if (texAlbedo != nullptr)
					{
						lua_pushstring(L, "albedo_texture_id");
						lua_pushnumber(L, textureConnection->FindId(texAlbedo));
						lua_settable(L, -3);
					}

					lua_pushstring(L, "index");
					lua_pushnumber(L, i);
					lua_settable(L, -3);

					LuaUtils::RegTable(L, "color", materials[i]->GetColor());
				}
				lua_settable(L, index);
			}
		}

		return 1;
	}
}}}}