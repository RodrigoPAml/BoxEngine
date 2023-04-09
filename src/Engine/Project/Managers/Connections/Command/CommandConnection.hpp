#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class CommandConnection;
	typedef std::shared_ptr<CommandConnection> CommandConnectionPtr;
	typedef std::weak_ptr<CommandConnection> CommandConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle command functions.
	/// </summary>
	class CommandConnection
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
		static std::weak_ptr<CommandConnection> current;
	public:
		CommandConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static CommandConnectionPtr Get();
		static void Set(CommandConnectionPtr instance);
	private:
		static int EnableVSync(lua_State* L);
		static int DisableVSync(lua_State* L);

		static int EnableDepthTesting(lua_State* L);
		static int DisableDepthTesting(lua_State* L);
		static int SetDepthTestingMode(lua_State* L);

		static int EnableCullingFace(lua_State* L);
		static int DisableCullingFace(lua_State* L);
		static int SetCullingFaceMode(lua_State* L);

		static int SetPrimitivePointSize(lua_State* L);
		static int SetPrimitiveLineSize(lua_State* L);

		static int SetPolygonDrawMode(lua_State* L);

		static int EnableBlending(lua_State* L);
		static int DisableBlending(lua_State* L);
	};
}}}