#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class UtilsConnection;
	typedef std::shared_ptr<UtilsConnection> UtilsConnectionPtr;
	typedef std::weak_ptr<UtilsConnection> UtilsConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle utility functions.
	/// </summary>
	class UtilsConnection
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
		static std::weak_ptr<UtilsConnection> current;
	public:
		UtilsConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static UtilsConnectionPtr Get();
		static void Set(UtilsConnectionPtr instance);
	private:
		static int GetFPS(lua_State* L);
		static int GetFrametime(lua_State* L);
	};
}}}