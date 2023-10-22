#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class VertexConnection;
	typedef std::shared_ptr<VertexConnection> VertexConnectionPtr;
	typedef std::weak_ptr<VertexConnection> VertexConnectionWeakPtr;

	using namespace Modules;

	/// <summary>
	/// Functions C++/LUA to handle vertex functions.
	/// </summary>
	class VertexConnection
	{
	private:
		lua_State* state;

		/// <summary>
		/// The current visited go by the engine
		/// </summary>
		GameObjectWeakPtr currentGo;

		/// <summary>
		/// Id count
		/// </summary>
		long currentId = 0;

		/// <summary>
		/// Vertexs map
		/// </summary>
		std::unordered_map<long, GPU::VertexPtr> vertices;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<VertexConnection> current;
	public:
		VertexConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static VertexConnectionPtr Get();
		static void Set(VertexConnectionPtr instance);
	private:
		static int CreateVertex(lua_State* L);
		static int DestroyVertex(lua_State* L);
	
		static int GetInfo(lua_State* L);

		static int Active(lua_State* L);
		static int Draw(lua_State* L);
		static int Modify(lua_State* L);

		static int Generate2DPoint(lua_State* L);
		static int Generate2DLine(lua_State* L);
		static int Generate2DRect(lua_State* L);
		static int Generate2DCircle(lua_State* L);
		static int Generate2DTriangle(lua_State* L);

		static int Generate3DPoint(lua_State* L);
		static int Generate3DLine(lua_State* L);
		static int Generate3DRect(lua_State* L);
		static int Generate3DCircle(lua_State* L);
		static int Generate3DTriangle(lua_State* L);
		static int Generate3DSphere(lua_State* L);
		static int Generate3DCube(lua_State* L);

		static int ReturnErrorSafe(
			GPU::VertexDescriptor& vd, 
			GPU::VertexIndicesDescriptor& vi,
			const char* message,
			lua_State* L
		);
	};
}}}}