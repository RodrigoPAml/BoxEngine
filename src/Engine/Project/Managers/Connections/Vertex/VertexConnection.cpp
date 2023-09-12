#include <BoxEngine.hpp>
#include "VertexConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<VertexConnection> VertexConnection::current;

	VertexConnection::VertexConnection(lua_State* state)
	{
		this->state = state;
	}

	void VertexConnection::Bind()
	{
		lua_newtable(this->state);
		
		Utils::Lua::RegTable(this->state, "create", CreateVertex);
		Utils::Lua::RegTable(this->state, "destroy", DestroyVertex);

		Utils::Lua::RegTable(this->state, "activate", Active);
		Utils::Lua::RegTable(this->state, "modify", Modify);
		Utils::Lua::RegTable(this->state, "draw", Draw);

		lua_setglobal(this->state, "_vertex_");

		lua_newtable(this->state);

		Utils::Lua::RegTable(this->state, "gen_2d_point", Generate2DPoint);
		Utils::Lua::RegTable(this->state, "gen_2d_line", Generate2DLine);
		Utils::Lua::RegTable(this->state, "gen_2d_circle", Generate2DCircle);
		Utils::Lua::RegTable(this->state, "gen_2d_triangle", Generate2DTriangle);

		Utils::Lua::RegTable(this->state, "gen_3d_circle", Generate3DCircle);
		Utils::Lua::RegTable(this->state, "gen_3d_cube", Generate3DCube);
		Utils::Lua::RegTable(this->state, "gen_3d_line", Generate3DLine);
		Utils::Lua::RegTable(this->state, "gen_3d_point", Generate3DPoint);
		Utils::Lua::RegTable(this->state, "gen_3d_rect", Generate3DRect);
		Utils::Lua::RegTable(this->state, "gen_3d_sphere", Generate3DSphere);
		Utils::Lua::RegTable(this->state, "gen_3d_triangle", Generate3DTriangle);
	
		lua_setglobal(this->state, "_generator_");
	}

	void VertexConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	VertexConnectionPtr VertexConnection::Get()
	{
		return current.lock();
	}

	void VertexConnection::Set(VertexConnectionPtr instance)
	{
		current = instance;
	}
	
	int VertexConnection::CreateVertex(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1 && top != 2)
			return luaL_error(L, "expecting 1 or 2 arguments in function call");
		
		GPU::VertexDescriptor vd;
		GPU::VertexIndicesDescriptor vi;
		std::string str;
		bool haveIndices = false;

		// Vertices
		if (lua_istable(L, 1))
		{
			int buffersCount = 0;

			// Read the amount of vertices used
			if (!Utils::Lua::GetTable(L, 1, "vertices_count", vd.verticesCount) || vd.verticesCount <= 0)
				return luaL_error(L, "argument vertices_count needs to be a number and greater than zero in first table");
			lua_pop(L, 1);

			// Read the number of buffers used
			if (!Utils::Lua::GetTable(L, 1, "buffers_count", buffersCount) || buffersCount <= 0)
				return luaL_error(L, "argument buffers_count needs to be a number and greater than zero in first table");
			lua_pop(L, 1);

			// Read each buffers
			lua_getfield(L, 1, "buffers");
			if (lua_istable(L, 1))
			{
				// Iterate buffers
				for (int i = 1; i <= buffersCount; i++)
				{
					GPU::VertexBufferDescriptor buffer;
					int elementsCount = 0;

					lua_rawgeti(L, -1, i);

					if (lua_istable(L, -1))
					{
						if (Utils::Lua::GetTable(L, -1, "use", str))
							buffer.use = GPU::DataUseFromString(str);
						lua_pop(L, 1);

						if (!Utils::Lua::GetTable(L, -1, "type", str))
							return ReturnErrorSafe(vd, vi, "argument type needs to be a string in first table", L);
						lua_pop(L, 1);

						buffer.type = GPU::VertexBufferTypeFromString(str);

						if (!Utils::Lua::GetTable(L, -1, "layouts_count", elementsCount) || elementsCount <= 0 )
							return ReturnErrorSafe(vd, vi, "argument layouts_count needs to be a number and positive in first table", L);
						lua_pop(L, 1);

						// Read elements of buffer
						lua_getfield(L, -1, "layouts");
						int layoutCount = 0;
						if (lua_istable(L, -1))
						{
							for (int j = 1; j <= elementsCount; j++)
							{
								GPU::VertexElement element;

								lua_rawgeti(L, -1, j);

								// Read element
								if (lua_istable(L, -1))
								{
									if (!Utils::Lua::GetTable(L, -1, "count", element.count) || element.count <= 0)
										return ReturnErrorSafe(vd, vi, "argument count needs to be a number and positive in first table", L);
									lua_pop(L, 1);

									layoutCount += element.count;
									Utils::Lua::GetTable(L, -1, "normalized", element.isNormalized);
									lua_pop(L, 1);

									buffer.elements.push_back(element);
								}
								else return ReturnErrorSafe(vd, vi, "argument layout at index needs to be a table in first table", L);

								lua_pop(L, 1);
							}
						}
						else return ReturnErrorSafe(vd, vi, "argument layouts needs to be a table in first table", L);
						lua_pop(L, 1);
				
						if (buffer.type == GPU::VertexBufferType::DOUBLE)
						{
							buffer.data = new double[vd.verticesCount * layoutCount];

							if (!Utils::Lua::GetTable(L, -1, "data", (double*)buffer.data, vd.verticesCount * layoutCount))
								return ReturnErrorSafe(vd, vi, "argument data needs to be a table in first table", L);
							lua_pop(L, 1);
						}
						else if (buffer.type == GPU::VertexBufferType::FLOAT)
						{
							buffer.data = new float[vd.verticesCount * layoutCount];
							if (!Utils::Lua::GetTable(L, -1, "data", (float*)buffer.data, vd.verticesCount * layoutCount))
								return ReturnErrorSafe(vd, vi, "argument data needs to be a table in first table", L);
							lua_pop(L, 1);
						}
						else if (buffer.type == GPU::VertexBufferType::INT)
						{
							buffer.data = new int[vd.verticesCount * layoutCount];

							if (!Utils::Lua::GetTable(L, -1, "data", (int*)buffer.data, vd.verticesCount * layoutCount))
								return ReturnErrorSafe(vd, vi, "argument data needs to be a table in first table", L);
							lua_pop(L, 1);
						}
						else return ReturnErrorSafe(vd, vi, "buffer only support types of INT, DOUBLE or FLOAT", L);
					}
					else return ReturnErrorSafe(vd, vi, "argument buffer at index needs to be a table in first table", L);

					vd.buffers.push_back(buffer);
					lua_pop(L, 1);
				}
			}
			else return ReturnErrorSafe(vd, vi, "argument buffers needs to be a table in first table", L);
		
			lua_pop(L, 1);
		}
		else return ReturnErrorSafe(vd, vi, "argument 1 is expected to be a table", L);

		// Indices
		if (lua_istable(L, 2))
		{
			if (Utils::Lua::GetTable(L, 2, "use", str))
				vi.use = GPU::DataUseFromString(str);
			lua_pop(L, 1);

			if (!Utils::Lua::GetTable(L, 2, "count", vi.count) || vi.count <= 0)
				return ReturnErrorSafe(vd, vi, "argument type needs to be a number and positive in second table", L);
			lua_pop(L, 1);

			vi.indices = new unsigned int[vi.count];

			if (!Utils::Lua::GetTable(L, 2, "data", (unsigned int*)vi.indices, vi.count))
				return ReturnErrorSafe(vd, vi, "argument data needs to be a table in second table", L);
			lua_pop(L, 1);

			haveIndices = true;
		}
		else if (!lua_isnoneornil(L, 2))
			return ReturnErrorSafe(vd, vi, "argument 2 needs to be a table", L);

		GPU::VertexPtr vertex = nullptr;
		auto instance = VertexConnection::Get();

		try
		{
			if(haveIndices)
				vertex = GPU::VertexPtr(new GPU::Vertex(vd, vi));
			else 
				vertex = GPU::VertexPtr(new GPU::Vertex(vd));

			instance->vertices[++instance->currentId] = vertex;
			lua_pushnumber(L, instance->currentId);
			return 1;
		}
		catch (std::exception)
		{
			lua_pushnil(L);
			vertex = nullptr;
			instance = nullptr;
			return 1;
		}

		lua_pushnil(L);
		return 1;
	}

	int VertexConnection::DestroyVertex(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			auto instance = VertexConnection::Get();
			lua_pushboolean(L, instance->vertices.erase(lua_tonumber(L, 1)) > 0);
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
	}

	int VertexConnection::Active(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = VertexConnection::Get();
		auto vertex = instance->vertices[id];

		if (vertex != nullptr)
			vertex->Use();

		lua_pushboolean(L, vertex != nullptr);
		return 1;
	}

	int VertexConnection::Draw(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 1 argument in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		std::string drawTypeStr;
		if (lua_isstring(L, 2))
			drawTypeStr = lua_tostring(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a string");

		auto instance = VertexConnection::Get();
		auto vertex = instance->vertices[id];

		if (vertex != nullptr)
			vertex->Draw(GPU::DrawingTypeFromString(drawTypeStr));

		lua_pushboolean(L, vertex != nullptr);

		return 1;
	}

	int VertexConnection::Modify(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (lua_istable(L, 2))
		{
			unsigned int start, tam, buffer;
			std::string typeStr;
			GPU::VertexBufferType type;

			if (!Utils::Lua::GetTable(L, 2, "start", start))
				return luaL_error(L, "argument start in second table is expected to be a number");

			if (Utils::Lua::GetTable(L, 2, "size", tam))
				return luaL_error(L, "argument tam in second table is expected to be a number");

			if (Utils::Lua::GetTable(L, 2, "buffer", buffer))
				return luaL_error(L, "argument buffer in second table is expected to be a number");
			
			if (!Utils::Lua::GetTable(L, 2, "type", typeStr))
				return luaL_error(L, "argument buffer in second table is expected to be a number");

			if (typeStr == "DOUBLE")
				type = GPU::VertexBufferType::DOUBLE;
			else if (typeStr == "FLOAT")
				type = GPU::VertexBufferType::FLOAT;
			else if (typeStr == "INT")
				type = GPU::VertexBufferType::INT;
			else return luaL_error(L, "argument type of second table is expected to be a FLOAT, DOUBLE or INT");

			if(tam <= 0)
				 return luaL_error(L, "argument tam should be greater than zero");

			void* data = nullptr;

			if (type == GPU::VertexBufferType::DOUBLE)
			{
				data = new double[tam];

				if (!Utils::Lua::GetTable(L, -1, "data", (double*)data, tam))
				{
					delete[] data;
					return luaL_error(L, "arguments data needs to be a valid number array in second table");
				}
			}
			else if (type == GPU::VertexBufferType::FLOAT)
			{
				data = new float[tam];

				if (!Utils::Lua::GetTable(L, -1, "data", (float*)data, tam))
				{
					delete[] data;
					return luaL_error(L, "arguments data needs to be a valid number array in second table");
				}
			}
			else if (type == GPU::VertexBufferType::INT)
			{
				data = new int[tam];

				if (!Utils::Lua::GetTable(L, -1, "data", (int*)data, tam))
				{
					delete[] data;
					return luaL_error(L, "arguments data needs to be a valid number array in second table");
				}
			}

			auto instance = VertexConnection::Get();
			auto vertex = instance->vertices[id];

			if (vertex != nullptr)
				vertex->ModifyData(buffer, start, tam, data);

			if (data != nullptr)
				delete[] data;

			lua_pushboolean(L, vertex != nullptr);
		}
		else return luaL_error(L, "argument 2 is expected to be a table");

		return 1;
	}

	int VertexConnection::Generate2DPoint(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		auto vertex = Utils::Generator::Generate2DPoint(GPU::DataUseFromString(str));
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate2DLine(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		auto vertex = Utils::Generator::Generate2DLine(GPU::DataUseFromString(str));
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate2DRect(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		bool filled;
		if (lua_isboolean(L, 2))
			filled = lua_toboolean(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a boolean");

		auto vertex = Utils::Generator::Generate2DRect(GPU::DataUseFromString(str), filled);
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate2DCircle(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		bool filled;
		if (lua_isboolean(L, 2))
			filled = lua_toboolean(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a boolean");

		int segments;
		if (lua_isnumber(L, 3))
			segments = lua_isnumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		auto vertex = Utils::Generator::Generate2DCircle(segments, GPU::DataUseFromString(str), filled);
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate2DTriangle(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		bool filled;
		if (lua_isboolean(L, 2))
			filled = lua_toboolean(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a boolean");

		auto vertex = Utils::Generator::Generate2DTriangle(GPU::DataUseFromString(str), filled);
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate3DPoint(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		auto vertex = Utils::Generator::Generate3DPoint(GPU::DataUseFromString(str));
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate3DLine(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		auto vertex = Utils::Generator::Generate3DLine(GPU::DataUseFromString(str));
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate3DRect(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		bool filled;
		if (lua_isboolean(L, 2))
			filled = lua_toboolean(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a boolean");

		auto vertex = Utils::Generator::Generate3DRect(GPU::DataUseFromString(str), filled);
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate3DCircle(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		bool filled;
		if (lua_isboolean(L, 2))
			filled = lua_toboolean(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a boolean");

		int segments;
		if (lua_isnumber(L, 3))
			segments = lua_isnumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		auto vertex = Utils::Generator::Generate3DCircle(segments, GPU::DataUseFromString(str), filled);
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate3DTriangle(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		bool filled;
		if (lua_isboolean(L, 2))
			filled = lua_toboolean(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a boolean");

		auto vertex = Utils::Generator::Generate3DTriangle(GPU::DataUseFromString(str), filled);
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate3DSphere(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 3)
			return luaL_error(L, "expecting 3 arguments in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		bool filled;
		if (lua_isboolean(L, 2))
			filled = lua_toboolean(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a boolean");

		int segments;
		if (lua_isnumber(L, 3))
			segments = lua_isnumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		auto vertex = Utils::Generator::Generate3DSphere(GPU::DataUseFromString(str), segments, filled);
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::Generate3DCube(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		std::string str;
		if (lua_isstring(L, 1))
			str = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		bool filled;
		if (lua_isboolean(L, 2))
			filled = lua_toboolean(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a boolean");

		auto vertex = Utils::Generator::Generate3DCube(GPU::DataUseFromString(str), filled);
		auto instance = VertexConnection::Get();

		instance->vertices[++instance->currentId] = vertex;
		lua_pushnumber(L, instance->currentId);
		return 1;
	}

	int VertexConnection::ReturnErrorSafe(
		GPU::VertexDescriptor& vd, 
		GPU::VertexIndicesDescriptor& vi,
		const char* message, 
		lua_State* L
	)
	{
		for (auto& item : vd.buffers)
			if(item.data != nullptr)
				delete[] item.data;

		if (vi.indices != nullptr)
			delete[] vi.indices;

		return luaL_error(L, message);
	}
}}}