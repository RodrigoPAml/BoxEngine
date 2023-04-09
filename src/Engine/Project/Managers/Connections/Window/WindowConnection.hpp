#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class WindowConnection;
	typedef std::shared_ptr<WindowConnection> WindowConnectionPtr;
	typedef std::weak_ptr<WindowConnection> WindowConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle window functions.
	/// </summary>
	class WindowConnection
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
		static std::weak_ptr<WindowConnection> current;
	public:
		WindowConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static WindowConnectionPtr Get();
		static void Set(WindowConnectionPtr instance);
	private:
		static int GetWindowSize(lua_State* L);
		static int GetWindowLimits(lua_State* L);
	};
}}}