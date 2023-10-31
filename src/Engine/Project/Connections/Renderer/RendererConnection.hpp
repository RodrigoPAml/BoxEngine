#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class RendererConnection;
	typedef std::shared_ptr<RendererConnection> RendererConnectionPtr;
	typedef std::weak_ptr<RendererConnection> RendererConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle renderer functions.
	/// </summary>
	class RendererConnection
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
		static std::weak_ptr<RendererConnection> current;
	public:
		RendererConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static RendererConnectionPtr Get();
		static void Set(RendererConnectionPtr instance);
	private:
		static int Render(lua_State* L);

		static bool HaveFramebuffer();
	};
}}}}