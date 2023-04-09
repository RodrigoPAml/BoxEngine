#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {
namespace Connection {

	class TextureConnection;
	typedef std::shared_ptr<TextureConnection> TextureConnectionPtr;
	typedef std::weak_ptr<TextureConnection> TextureConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle texture functions.
	/// </summary>
	class TextureConnection
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
		/// Textures map
		/// </summary>
		std::unordered_map<long, GPU::TexturePtr> textures;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<TextureConnection> current;
	public:
		TextureConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static TextureConnectionPtr Get();
		static void Set(TextureConnectionPtr instance);

		bool Exists(long id);
		GPU::TexturePtr Get(long id);
		long FindId(GPU::TexturePtr texture);
	private:
		static int CreateEmptyTexture(lua_State* L);
		static int CreateTexture(lua_State* L);

		static int DestroyTexture(lua_State* L);

		static int Active(lua_State* L);
		static int DisableTextureUnit(lua_State* L);
	};
}}}