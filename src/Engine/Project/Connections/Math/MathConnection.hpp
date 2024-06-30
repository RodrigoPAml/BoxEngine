#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
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
		static int Random(lua_State* L);
		
		static int MakeVec2(lua_State* L);
		static int MakeVec3(lua_State* L);
		static int MakeVec4(lua_State* L);

		static int MakeMat2(lua_State* L);
		static int MakeMat3(lua_State* L);
		static int MakeMat4(lua_State* L);

		static int MakeIdentityMat2(lua_State* L);
		static int MakeIdentityMat3(lua_State* L);
		static int MakeIdentityMat4(lua_State* L);

		static int Translate(lua_State* L);
		static int Rotate(lua_State* L);
		static int Scale(lua_State* L);
		static int Multiply(lua_State* L);

		static int MagnitudeVec2(lua_State* L);
		static int MagnitudeVec3(lua_State* L);

		static int NormalizeVec2(lua_State* L);
		static int NormalizeVec3(lua_State* L);
	};
}}}}