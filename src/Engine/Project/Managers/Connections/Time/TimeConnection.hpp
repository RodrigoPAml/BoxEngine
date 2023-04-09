#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class TimeConnection;
	typedef std::shared_ptr<TimeConnection> TimeConnectionPtr;
	typedef std::weak_ptr<TimeConnection> TimeConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle time functions.
	/// </summary>
	class TimeConnection
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
		static std::weak_ptr<TimeConnection> current;
	public:
		TimeConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static TimeConnectionPtr Get();
		static void Set(TimeConnectionPtr instance);
	private:
		static int GetTimestamp(lua_State* L);
		static int GetDateTime(lua_State* L);
	};
}}}