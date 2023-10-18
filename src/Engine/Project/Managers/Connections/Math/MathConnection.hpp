#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class MathConnection;
	typedef std::shared_ptr<MathConnection> MathConnectionPtr;
	typedef std::weak_ptr<MathConnection> MathConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle logs.
	/// </summary>
	class MathConnection
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
		static std::weak_ptr<MathConnection> current;
	public:
		MathConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static MathConnectionPtr Get();
		static void Set(MathConnectionPtr instance);
	private:
		static int MakeMat4(lua_State* L);
		static int MakeIdentityMat4(lua_State* L);
		static int TranslateMat4(lua_State* L);
		static int RotateMat4(lua_State* L);
		static int ScaleMat4(lua_State* L);

	};
}}}