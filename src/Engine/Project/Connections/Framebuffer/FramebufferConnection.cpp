#include <BoxEngine.hpp>
#include "FramebufferConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<FramebufferConnection> FramebufferConnection::current;

	FramebufferConnection::FramebufferConnection(lua_State* state)
	{
		this->state = state;
	}

	void FramebufferConnection::Bind()
	{
		lua_newtable(this->state);
		
		LuaUtils::RegTable(this->state, "create", CreateFramebuffer);
		LuaUtils::RegTable(this->state, "destroy", DestroyFramebuffer);

		LuaUtils::RegTable(this->state, "active", Active);
		LuaUtils::RegTable(this->state, "get_attachments_size", GetAttachmentSize);
		LuaUtils::RegTable(this->state, "get_attachment", GetAttachment);

		LuaUtils::RegTable(this->state, "set_current", SetCurrent);
		LuaUtils::RegTable(this->state, "get_current", GetCurrent);
		LuaUtils::RegTable(this->state, "active_none", ActiveNone);

		LuaUtils::RegTable(this->state, "clear", Clear);
		LuaUtils::RegTable(this->state, "set_clear_modes", SetClearModes);
		LuaUtils::RegTable(this->state, "set_viewport", SwitchViewPort);

		lua_setglobal(this->state, "_framebuffer_");
	}

	void FramebufferConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	FramebufferConnectionPtr FramebufferConnection::Get()
	{
		return current.lock();
	}

	void FramebufferConnection::Set(FramebufferConnectionPtr instance)
	{
		current = instance;
	}
	
	int FramebufferConnection::CreateFramebuffer(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_istable(L, 1))
		{
			GPU::FramebufferConfiguration config;
			
			// texture count
			unsigned int textureCount = 0;
			if (!LuaUtils::GetTable(L, 1, "texture_attachments_count", textureCount))
				return luaL_error(L, "argument texture_attachments_count needs to be a number");

			if (textureCount > 0)
			{
				unsigned int* textures = new unsigned int[textureCount];

				if (LuaUtils::GetTable(L, 1, "texture_attachments", textures, textureCount))
				{
					for (int i = 0; i < textureCount; i++)
					{
						if (!TextureConnection::Get()->Exists(textures[i]))
						{
							Debug::Logging::Log(
								"Failed to create framebuffer because texture " + std::to_string(textures[i]) + " dont exist",
								Debug::LogSeverity::Error,
								Debug::LogOrigin::Engine
							);
							
							delete[] textures;
							lua_pushnil(L);
							return 1;
						}

						config.textureAttachments.push_back(TextureConnection::Get()->Get(textures[i]));
					}

					delete[] textures;
				}
				else
				{
					delete[] textures;
					return luaL_error(L, "argument texture_attachments needs to be a table");
				}
			}
			else return luaL_error(L, "argument texture_attachments_count needs to greater than zero");
			
			// depth attachment
			unsigned int depthTexture;
			if (LuaUtils::GetTable(L, 1, "depth_attachment", depthTexture))
			{
				if (!TextureConnection::Get()->Exists(depthTexture))
				{
					Debug::Logging::Log(
						"Failed to create framebuffer because depth texture attachment " + std::to_string(depthTexture) + " dont exist",
						Debug::LogSeverity::Warning,
						Debug::LogOrigin::Engine
					);

					lua_pushnil(L);
					return 1;
				}

				config.depthAttachment = TextureConnection::Get()->Get(depthTexture);
			}
			else if (!lua_isnoneornil(L, -1))
				return luaL_error(L, "argument depth_attachment needs to be a number");

			// render buffer attachment
			lua_getfield(L, 1, "renderbuffer_attachment");
			if (lua_istable(L, -1))
			{
				std::string str;

				if (!LuaUtils::GetTable(L, -1, "type", str))
					return luaL_error(L, "argument type needs to be a string");

				config.renderBufferAttachment.type = GPU::GetRenderBufferAttachmentTypeFromString(str);

				if (!LuaUtils::GetTable(L, -2, "format", str))
					return luaL_error(L, "argument format needs to be a string");
				
				config.renderBufferAttachment.format = GPU::GetRenderBufferFormatFromString(str);

				if (!LuaUtils::GetTable(L, -3, "size", config.renderBufferAttachment.size))
					return luaL_error(L, "argument size needs to be a vec2");

				LuaUtils::GetTable(L, -4, "aliasing", config.renderBufferAttachment.aliasing);
			}
			else if(!lua_isnoneornil(L, -1)) 
				return luaL_error(L, "argument renderbuffer_attachment needs to be a table");
			
			GPU::FramebufferPtr framebuffer = nullptr;

			try
			{
				auto fb = Get();

				framebuffer = GPU::FramebufferPtr(new GPU::Framebuffer(config));

				fb->framebuffers[++fb->currentId] = framebuffer;
				lua_pushnumber(L, fb->currentId);
				return 1;
			}
			catch (std::exception)
			{
				lua_pushnil(L);
				framebuffer = nullptr;
				return 1;
			}
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

		lua_pushnil(L);
		return 1;
	}

	int FramebufferConnection::DestroyFramebuffer(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			auto instance = FramebufferConnection::Get();
			lua_pushboolean(L, instance->framebuffers.erase(lua_tonumber(L, 1)) > 0);
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
	}

	int FramebufferConnection::SetCurrent(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			auto id = lua_tonumber(L, 1);

			if (Get()->framebuffers.contains(id))
			{
				auto instance = Get()->framebuffers[id];
				Project::GetCurrentProject()->SetCurrentFramebuffer(instance);
				lua_pushboolean(L, true);
			}
			else lua_pushboolean(L, false);
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
	}

	int FramebufferConnection::GetCurrent(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		auto instance = Project::GetCurrentProject()->GetCurrentFramebuffer();

		if (instance != nullptr)
		{
			for (auto item : Get()->framebuffers)
			{
				if (item.second == instance)
				{
					lua_pushnumber(L, item.first);
					break;
				}
			}
		}
		else lua_pushnil(L);

		return 1;
	}

	int FramebufferConnection::Active(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");
		
		auto instance = FramebufferConnection::Get();
		auto framebuffer = instance->framebuffers[id];

		if (framebuffer != nullptr)
			framebuffer->Use();

		lua_pushboolean(L, framebuffer != nullptr);
		return 1;
	}

	int FramebufferConnection::GetAttachmentSize(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = FramebufferConnection::Get();
		auto framebuffer = instance->framebuffers[id];

		if (framebuffer != nullptr)
			lua_pushnumber(L, framebuffer->GetAttachmentSize());
		else lua_pushnil(L);

		return 1;
	}

	int FramebufferConnection::GetAttachment(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		int pos = 0;
		if (lua_isnumber(L, 2))
			pos = lua_tonumber(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a number");

		auto instance = FramebufferConnection::Get();
		auto framebuffer = instance->framebuffers[id];

		if (framebuffer != nullptr)
		{
			auto texture = framebuffer->GetTextureAttachment(pos);

			if (texture != nullptr)
				lua_pushnumber(L, TextureConnection::Get()->FindId(texture));
			else lua_pushnil(L);
		}
		else lua_pushnil(L);

		return 1;
	}

	int FramebufferConnection::ActiveNone(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting 0 argument in function call");

		GPU::Framebuffer::ActiveDefault();

		return 0;
	}

	int FramebufferConnection::Clear(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		glm::vec4 value;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, -1, "x", value.x))
				return luaL_error(L, "argument x is expected to be a number");

			if (!LuaUtils::GetTable(L, -2, "y", value.y))
				return luaL_error(L, "argument y is expected to be a number");

			if (!LuaUtils::GetTable(L, -3, "z", value.z))
				return luaL_error(L, "argument z is expected to be a number");

			if (!LuaUtils::GetTable(L, -4, "w", value.w))
				return luaL_error(L, "argument w is expected to be a number");
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

		GPU::Framebuffer::Clear(value);

		return 1;
	}

	int FramebufferConnection::SetClearModes(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::set<GPU::ClearMode> modes;
		if (lua_istable(L, 1))
		{
			bool value;
			
			if (LuaUtils::GetTable(L, 1, "color", value))
			{
				if (value)
					modes.insert(GPU::ClearMode::COLOR);
			}
			else return luaL_error(L, "expecting argument color to be a boolean");

			if (LuaUtils::GetTable(L, 1, "depth", value))
			{
				if (value)
					modes.insert(GPU::ClearMode::DEPTH);
			}
			else return luaL_error(L, "expecting argument depth to be a boolean");

			if (LuaUtils::GetTable(L, 1, "stencil", value))
			{
				if (value)
					modes.insert(GPU::ClearMode::STENCIL);
			}
			else return luaL_error(L, "expecting argument stencil to be a boolean");

			GPU::Framebuffer::SetClearModes(modes);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int FramebufferConnection::SwitchViewPort(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		glm::vec4 vec;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, -1, "x", vec.x))
				return luaL_error(L, "argument x is expected to be a number");

			if (!LuaUtils::GetTable(L, -2, "y", vec.y))
				return luaL_error(L, "argument y is expected to be a number");

			if (!LuaUtils::GetTable(L, -3, "z", vec.z))
				return luaL_error(L, "argument z is expected to be a number");

			if (!LuaUtils::GetTable(L, -4, "w", vec.w))
				return luaL_error(L, "argument w is expected to be a number");
		}
		else return luaL_error(L, "argument 1 is expected to be a table");

		GPU::Framebuffer::SwitchViewPort({ vec.x, vec.y }, { vec.z, vec.w });

		return 1;
	}
}}}}