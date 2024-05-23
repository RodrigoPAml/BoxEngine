#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class FontConnection;
	typedef std::shared_ptr<FontConnection> FontConnectionPtr;
	typedef std::weak_ptr<FontConnection> FontConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle Font functions.
	/// </summary>
	class FontConnection
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
		/// Font maps
		/// </summary>
		std::unordered_map<long, Font::FontPtr> fonts;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<FontConnection> current;
	public:
		FontConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static FontConnectionPtr Get();
		static void Set(FontConnectionPtr instance);
	private:
		static int Create(lua_State* L);
		static int Destroy(lua_State* L);

		static int SetPosition(lua_State* L);
		static int GetPosition(lua_State* L);

		static int SetScale(lua_State* L);
		static int GetScale(lua_State* L);

		static int SetColor(lua_State* L);
		static int GetColor(lua_State* L);

		static int SetText(lua_State* L);
		static int GetText(lua_State* L);

		static int GetTextSize(lua_State* L);

		static int Draw(lua_State* L);

		static bool HaveFramebuffer();
	};
}}}}