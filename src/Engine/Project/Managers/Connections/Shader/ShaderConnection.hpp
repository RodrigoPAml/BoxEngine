#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class ShaderConnection;
	typedef std::shared_ptr<ShaderConnection> ShaderConnectionPtr;
	typedef std::weak_ptr<ShaderConnection> ShaderConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle shaders functions.
	/// </summary>
	class ShaderConnection
	{
	private:
		lua_State* state;

		/// <summary>
		/// The current visited go by the engine
		/// </summary>
		GameObjectWeakPtr currentGo;

		/// <summary>
		/// Id count
		/// </summary>
		long currentId = 0;

		/// <summary>
		/// Shaders map
		/// </summary>
		std::unordered_map<long, GPU::ShaderPtr> shaders;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<ShaderConnection> current;
	public:
		ShaderConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static ShaderConnectionPtr Get();
		static void Set(ShaderConnectionPtr instance);
	private:
		static int CreateShader(lua_State* L);
		static int DestroyShader(lua_State* L);
		
		static int Active(lua_State* L);
		static int UnactiveAll(lua_State* L);

		static int SetShaderBool(lua_State* L);
		static int SetShaderInt(lua_State* L);
		static int SetShaderFloat(lua_State* L);

		static int SetShaderXY(lua_State* L);
		static int SetShaderXYZ(lua_State* L);
		static int SetShaderXYZW(lua_State* L);

		static int SetShaderVec2(lua_State* L);
		static int SetShaderVec3(lua_State* L);
		static int SetShaderVec4(lua_State* L);

		static int SetShaderMat2(lua_State* L);
		static int SetShaderMat3(lua_State* L);
		static int SetShaderMat4(lua_State* L);
	};
}}}