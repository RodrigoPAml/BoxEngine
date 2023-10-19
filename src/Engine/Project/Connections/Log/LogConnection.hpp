#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class LogConnection;
	typedef std::shared_ptr<LogConnection> LogConnectionPtr;
	typedef std::weak_ptr<LogConnection> LogConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle logs.
	/// </summary>
	class LogConnection
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
		static std::weak_ptr<LogConnection> current;
	public:
		LogConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static LogConnectionPtr Get();
		static void Set(LogConnectionPtr instance);
	private:
		// Logging
		static int DebugLog(lua_State* L);
		static int DebugWarning(lua_State* L);
		static int DebugError(lua_State* L);
	};
}}}}