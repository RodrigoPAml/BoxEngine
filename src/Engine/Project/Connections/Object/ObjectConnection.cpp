#include <BoxEngine.hpp>
#include "ObjectConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<ObjectConnection> ObjectConnection::current;

	ObjectConnection::ObjectConnection(lua_State* state)
	{
		this->state = state;
	}

	void ObjectConnection::Bind()
	{
		lua_newtable(this->state);

		LuaUtils::RegTable(this->state, "open", Open);
		LuaUtils::RegTable(this->state, "create", Create);
		LuaUtils::RegTable(this->state, "destroy", Destroy);

		LuaUtils::RegTable(this->state, "get", Get);
		LuaUtils::RegTable(this->state, "get_meshes", GetMeshes);
		LuaUtils::RegTable(this->state, "get_materials", GetMaterials);

		lua_setglobal(this->state, "_object_");
	}

	void ObjectConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	ObjectConnectionPtr ObjectConnection::Get()
	{
		return current.lock();
	}

	void ObjectConnection::Set(ObjectConnectionPtr instance)
	{
		current = instance;
	}

	Importer::ObjectPtr ObjectConnection::FindObj(long id)
	{
		auto instance = ObjectConnection::Get();

		return instance->objs.contains(id) ? instance->objs[id] : nullptr;
	}

	int ObjectConnection::Open(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");
		
		std::string path = "";
		if (lua_isstring(L, 1))
			path = lua_tostring(L, 1);
		else return luaL_error(L, "expecting 1 to be a string");

		Importer::ObjectPtr obj = nullptr;

		auto instance = ObjectConnection::Get();
		auto textureConnection = TextureConnection::Get();
		auto vertexConnection = VertexConnection::Get();

		try
		{
			obj = Importer::Importer::Load(path);

			for (auto& mesh : obj->GetMeshes())
				vertexConnection->Register(mesh->GetMesh());

			for (auto& mtl : obj->GetMaterials())
				textureConnection->Register(mtl->GetAlbedoTexture());

			obj->ClearRefs();

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

	int ObjectConnection::Create(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string name = "";
		if (lua_isstring(L, 1))
			name = lua_tostring(L, 1);
		else return luaL_error(L, "expecting 1 to be a string");

		Importer::ObjectPtr obj = nullptr;

		auto instance = ObjectConnection::Get();
		auto textureConnection = TextureConnection::Get();
		auto vertexConnection = VertexConnection::Get();

		try
		{
			obj = Importer::ObjectPtr(new Importer::Object());
			obj->SetName(name);

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

	int ObjectConnection::Destroy(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			auto instance = ObjectConnection::Get();
			auto id = lua_tonumber(L, 1);
			instance->objs.erase(id);
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 0;
	}
	
	int ObjectConnection::Get(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		long objId = 0;
		if (lua_isnumber(L, 1))
			objId = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be number");

		auto instance = ObjectConnection::Get();
		Importer::ObjectPtr obj = instance->objs.contains(objId) ? instance->objs[objId] : nullptr;

		if (obj == nullptr)
			lua_pushnil(L);
		else
		{
			lua_newtable(L);
			LuaUtils::RegTable(L, "base_path", obj->GetBasePath());
			LuaUtils::RegTable(L, "path", obj->GetPath());
			LuaUtils::RegTable(L, "name", obj->GetName());
			LuaUtils::RegTable(L, "mesh_count", (int)obj->GetMeshes().size());
			LuaUtils::RegTable(L, "material_count", (int)obj->GetMaterials().size());
		}

		return 1;
	}

	int ObjectConnection::GetMeshes(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		long objId = 0;
		if (lua_isnumber(L, 1))
			objId = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be number");

		auto instance = ObjectConnection::Get();
		Importer::ObjectPtr obj = instance->objs.contains(objId) ? instance->objs[objId] : nullptr;

		if (obj == nullptr)
			lua_pushnil(L);
		else
		{
			auto meshes = obj->GetMeshes();
			auto vertexConnection = VertexConnection::Get();

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

					lua_pushstring(L, "material_name");
					lua_pushstring(L, meshes[i]->GetMaterial().c_str());
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

	int ObjectConnection::GetMaterials(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		long objId = 0;
		if (lua_isnumber(L, 1))
			objId = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be number");

		auto instance = ObjectConnection::Get();
		Importer::ObjectPtr obj = instance->objs.contains(objId) ? instance->objs[objId] : nullptr;

		if (obj == nullptr)
			lua_pushnil(L);
		else
		{
			auto materials = obj->GetMaterials();
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

					LuaUtils::RegTable(L, "color", materials[i]->GetColor());
				}
				lua_settable(L, index);
			}
		}

		return 1;
	}
}}}}