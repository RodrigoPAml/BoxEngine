#include <BoxEngine.hpp>
#include "TextureConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<TextureConnection> TextureConnection::current;

	TextureConnection::TextureConnection(lua_State* state)
	{
		this->state = state;
	}

	void TextureConnection::Bind()
	{
		lua_newtable(this->state);
		
		LuaUtils::RegTable(this->state, "create", CreateTexture);
		LuaUtils::RegTable(this->state, "create_empty", CreateEmptyTexture);
		LuaUtils::RegTable(this->state, "create_multi_sampled", CreateMultiSampledTexture);

		LuaUtils::RegTable(this->state, "get_info", GetInfo);

		LuaUtils::RegTable(this->state, "destroy", DestroyTexture);

		LuaUtils::RegTable(this->state, "active", Active);
		LuaUtils::RegTable(this->state, "disable_texture_unit", DisableTextureUnit);

		lua_setglobal(this->state, "_texture_");
	}

	void TextureConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	TextureConnectionPtr TextureConnection::Get()
	{
		return current.lock();
	}

	void TextureConnection::Set(TextureConnectionPtr instance)
	{
		current = instance;
	}

	bool TextureConnection::Exists(long id)
	{
		return this->textures.contains(id);
	}

	GPU::TexturePtr TextureConnection::Get(long id)
	{
		return this->textures[id];
	}

	long TextureConnection::FindId(GPU::TexturePtr texture)
	{
		for (auto item : textures)
		{
			if (item.second == texture)
				return item.first;
		}

		return 0;
	}
	
	int TextureConnection::CreateEmptyTexture(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_istable(L, 1))
		{
			GPU::TextureConfiguration config;
			std::string str;
			
			if(LuaUtils::GetTable(L, 1, "minifying_filter", str))
				config.minifyingFilter = GPU::MinifyingFilterFromString(str);

			if (LuaUtils::GetTable(L, 1, "magnification_filter", str))
				config.magnificationFilter = GPU::MagnificationFilterFromString(str);

			if (LuaUtils::GetTable(L, 1, "texture_wrap_t", str))
				config.textureWrapT = GPU::TextureWrapFromString(str);

			if (LuaUtils::GetTable(L, 1, "texture_wrap_s", str))
				config.textureWrapS = GPU::TextureWrapFromString(str);

			if (LuaUtils::GetTable(L, 1, "texture_internal_format", str))
				config.internalFormat = GPU::TextureInternalFormatToString(str);

			if (LuaUtils::GetTable(L, 1, "texture_pixel_format", str))
				config.pixelFormat = GPU::TexturePixelFormatFromString(str);

			if (LuaUtils::GetTable(L, 1, "texture_format", str))
				config.format = GPU::TextureFormatFromString(str);

			LuaUtils::GetTable(L, 1, "ansiotropic_filter", config.ansiotropicFilter);
			LuaUtils::GetTable(L, 1, "border_color", config.borderColor);

			if (!LuaUtils::GetTable(L, 1, "texture_size", config.size))
				return luaL_error(L, "argument texture_size needs to be a vec2");

			GPU::TexturePtr texture = nullptr;
			auto instance = TextureConnection::Get();

			try
			{
				texture = GPU::TexturePtr(new GPU::Texture(config));
				instance->textures[++instance->currentId] = texture;
				lua_pushnumber(L, instance->currentId);
				return 1;
			}
			catch (std::exception)
			{
				lua_pushnil(L);
				texture = nullptr;
				instance = nullptr;
				return 1;
			}
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

		lua_pushnil(L);
		return 1;
	}

	int TextureConnection::CreateMultiSampledTexture(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_istable(L, 1))
		{
			GPU::MultisampleTextureConfiguration config;
			std::string str;

			if (!LuaUtils::GetTable(L, 1, "texture_samples", config.samples))
				return luaL_error(L, "argument samples needs to be a number");

			if (LuaUtils::GetTable(L, 1, "texture_internal_format", str))
				config.internalFormat = GPU::TextureInternalFormatToString(str);

			LuaUtils::GetTable(L, 1, "fixed_samples", config.fixedSamples);

			if (!LuaUtils::GetTable(L, 1, "texture_size", config.size))
				return luaL_error(L, "argument texture_size needs to be a vec2");

			GPU::TexturePtr texture = nullptr;
			auto instance = TextureConnection::Get();

			try
			{
				texture = GPU::TexturePtr(new GPU::Texture(config));
				instance->textures[++instance->currentId] = texture;
				lua_pushnumber(L, instance->currentId);
				return 1;
			}
			catch (std::exception)
			{
				lua_pushnil(L);
				texture = nullptr;
				instance = nullptr;
				return 1;
			}
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

		lua_pushnil(L);
		return 1;
	}

	int TextureConnection::CreateTexture(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_istable(L, 1))
		{
			GPU::TextureDataConfiguration config;
			std::string str;

			if (LuaUtils::GetTable(L, 1, "minifying_filter", str))
				config.minifyingFilter = GPU::MinifyingFilterFromString(str);

			if (LuaUtils::GetTable(L, 1, "magnification_filter", str))
				config.magnificationFilter = GPU::MagnificationFilterFromString(str);

			if (LuaUtils::GetTable(L, 1, "texture_wrap_t", str))
				config.textureWrapT = GPU::TextureWrapFromString(str);

			if (LuaUtils::GetTable(L, 1, "texture_wrap_s", str))
				config.textureWrapS = GPU::TextureWrapFromString(str);

			LuaUtils::GetTable(L, 1, "ansiotropic_filter", config.ansiotropicFilter);
			LuaUtils::GetTable(L, 1, "border_color", config.borderColor);

			if (!LuaUtils::GetTable(L, 1, "image_path", str))
				return luaL_error(L, "argument image_path needs to be a string");

			Utils::ImagePtr image = nullptr;

			try
			{
				image = Utils::ImagePtr(new Utils::Image(str, true));

				config.pixelFormat = GPU::TexturePixelFormat::UNSIGNED_BYTE;
				if (image->GetFormat() == GPU::TextureFormat::RGB)
					config.internalFormat = GPU::TextureInternalFormat::RGB;
				else if (image->GetFormat() == GPU::TextureFormat::R)
					config.internalFormat = GPU::TextureInternalFormat::R;
				else if (image->GetFormat() == GPU::TextureFormat::RGBA)
					config.internalFormat = GPU::TextureInternalFormat::RGBA;
			}
			catch (std::exception)
			{
				lua_pushnil(L);
				image = nullptr;
				return 1;
			}

			GPU::TexturePtr texture = nullptr;
			auto instance = TextureConnection::Get();

			try
			{
				texture = GPU::TexturePtr(new GPU::Texture(config, image));
				instance->textures[++instance->currentId] = texture;

				lua_pushnumber(L, instance->currentId);
				return 1;
			}
			catch (std::exception)
			{
				lua_pushnil(L);
				texture = nullptr;
				image = nullptr;
				instance = nullptr;
				return 1;
			}

			lua_pushnil(L);
		}
		else return luaL_error(L, "argument 1 is expected to be a table");
		
		lua_pushnil(L);
		return 1;
	}

	int TextureConnection::GetInfo(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		long id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be number");

		auto instance = TextureConnection::Get();
		GPU::TexturePtr texture = instance->textures.contains(id) ? instance->textures[id] : nullptr;

		if (texture == nullptr)
			lua_pushnil(L);
		else
		{
			// Table for the info
			lua_newtable(L);
			LuaUtils::RegTable(L, "gl_id", (int)texture->GetId());
			LuaUtils::RegTable(L, "samples", texture->GetNumberOfSamples());
			LuaUtils::RegTable(L, "multisampled", texture->IsMultiSampled());
			LuaUtils::RegTable(L, "size", texture->GetSize());
		} 

		return 1;
	}

	int TextureConnection::DestroyTexture(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			auto instance = TextureConnection::Get();
			lua_pushboolean(L, instance->textures.erase(lua_tonumber(L, 1)) > 0);
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
	}

	int TextureConnection::Active(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 1 argument in function call");

		int id = 0;
		int slot = 0;

		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (lua_isnumber(L, 2))
			slot = lua_tonumber(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a number");
		
		auto instance = TextureConnection::Get();
		auto texture = instance->textures[id];

		if (texture != nullptr)
			texture->Use(slot);


		lua_pushboolean(L, texture != nullptr);
		return 1;
	}

	int TextureConnection::DisableTextureUnit(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		int slot = 0;

		if (lua_isnumber(L, 1))
			slot = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		GPU::Texture::DisableTextureUnit(slot);

		return 0;
	}
}}}}