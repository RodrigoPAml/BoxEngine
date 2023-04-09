#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class Camera2DConnection;
	typedef std::shared_ptr<Camera2DConnection> Camera2DConnectionPtr;
	typedef std::weak_ptr<Camera2DConnection> Camera2DConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle 2d cameras.
	/// </summary>
	class Camera2DConnection
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
		/// Camera2Ds map
		/// </summary>
		std::unordered_map<long, Camera::Camera2DPtr> cameras;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<Camera2DConnection> current;
	public:
		Camera2DConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static Camera2DConnectionPtr Get();
		static void Set(Camera2DConnectionPtr instance);
	private:
		static int CreateCamera(lua_State* L);
		static int DestroyCamera(lua_State* L);

		static int UpdateCamera(lua_State* L);
		static int GetCamera(lua_State* L);
		static int GetMatrix(lua_State* L);

		static int SetCurrentCamera(lua_State* L);
	};
}}}