#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class InputConnection;
	typedef std::shared_ptr<InputConnection> InputConnectionPtr;
	typedef std::weak_ptr<InputConnection> InputConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle input.
	/// </summary>
	class InputConnection
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
		static std::weak_ptr<InputConnection> current;
	public:
		InputConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static InputConnectionPtr Get();
		static void Set(InputConnectionPtr instance);
	private:
		// Input
		static int GetKey(lua_State* L);
		static int GetMod(lua_State* L);
		static int GetMousePos(lua_State* L);
		static int GetMouseVar(lua_State* L);
		static int GetMouseButton(lua_State* L);
	};
}}}