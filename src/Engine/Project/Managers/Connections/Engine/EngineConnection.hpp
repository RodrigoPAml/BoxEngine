#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class EngineConnection;
	typedef std::shared_ptr<EngineConnection> EngineConnectionPtr;
	typedef std::weak_ptr<EngineConnection> EngineConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle engine functions.
	/// </summary>
	class EngineConnection
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
		static std::weak_ptr<EngineConnection> current;
	public:
		EngineConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static EngineConnectionPtr Get();
		static void Set(EngineConnectionPtr instance);
	private:
		static int GetFPS(lua_State* L);
		static int GetFrametime(lua_State* L);
		static int StopEngine(lua_State* L);
		static int RestartEngine(lua_State* L);
	};
}}}