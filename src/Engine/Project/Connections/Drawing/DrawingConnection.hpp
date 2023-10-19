#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class DrawingConnection;
	typedef std::shared_ptr<DrawingConnection> DrawingConnectionPtr;
	typedef std::weak_ptr<DrawingConnection> DrawingConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle drawing functions.
	/// </summary>
	class DrawingConnection
	{
	private:
		lua_State* state;

		/// <summary>
		/// The current visited go by the engine
		/// </summary>
		GameObjectWeakPtr currentGo;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<DrawingConnection> current;
	public:
		DrawingConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static DrawingConnectionPtr Get();
		static void Set(DrawingConnectionPtr instance);
	private:

		static int Draw2DRectangle(lua_State* L);
		static int Draw2DCircle(lua_State* L);
		static int Draw2DTriangle(lua_State* L);
		static int Draw2DPoint(lua_State* L);
		static int Draw2DLine(lua_State* L);

		static int Draw3DCube(lua_State* L);
		static int Draw3DSphere(lua_State* L);
		static int Draw3DPoint(lua_State* L);
		static int Draw3DLine(lua_State* L);
		static int Draw3DRect(lua_State* L);
		static int Draw3DTriangle(lua_State* L);
		static int Draw3DCircle(lua_State* L);
	
		static int DrawTexture(lua_State* L);
		static int DrawFrame(lua_State* L);

		static bool HaveFramebuffer();
	};
}}}}