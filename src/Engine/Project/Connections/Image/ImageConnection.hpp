#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class ImageConnection;
	typedef std::shared_ptr<ImageConnection> ImageConnectionPtr;
	typedef std::weak_ptr<ImageConnection> ImageConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle image functions.
	/// </summary>
	class ImageConnection
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
		static std::weak_ptr<ImageConnection> current;
	public:
		ImageConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static ImageConnectionPtr Get();
		static void Set(ImageConnectionPtr instance);
	private:
		static int OpenImage(lua_State* L);
	};
}}}}