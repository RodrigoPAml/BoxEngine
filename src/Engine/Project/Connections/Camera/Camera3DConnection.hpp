#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class Camera3DConnection;
	typedef std::shared_ptr<Camera3DConnection> Camera3DConnectionPtr;
	typedef std::weak_ptr<Camera3DConnection> Camera3DConnectionWeakPtr;

	using namespace Modules;

	/// <summary>
	/// Functions C++/LUA to handle 3d cameras.
	/// </summary>
	class Camera3DConnection
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
		/// Camera3Ds map
		/// </summary>
		std::unordered_map<long, Camera::Camera3DPtr> cameras;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<Camera3DConnection> current;
	public:
		Camera3DConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static Camera3DConnectionPtr Get();
		static void Set(Camera3DConnectionPtr instance);
	private:
		static int CreateCamera(lua_State* L);
		static int DestroyCamera(lua_State* L);

		static int TranslateCameraRelative(lua_State* L);
		static int TranslateCameraAbsolute(lua_State* L);
		static int RotateCamera(lua_State* L);

		static int UpdateCamera(lua_State* L);
		static int GetCamera(lua_State* L);

		static int GetViewMatrix(lua_State* L);
		static int GetProjectionMatrix(lua_State* L);
	
		static int SetCurrentCamera(lua_State* L);
		static int GetCurrentCamera(lua_State* L);
	};
}}}}