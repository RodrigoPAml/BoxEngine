#include <BoxEngine.hpp>
#include "FramebufferConnection.hpp"

namespace BoxEngine {
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
		
		Utils::Lua::RegTable(this->state, "create", CreateFramebuffer);
		Utils::Lua::RegTable(this->state, "destroy", DestroyFramebuffer);

		Utils::Lua::RegTable(this->state, "set_current", SetCurrent);
		Utils::Lua::RegTable(this->state, "get_current", GetCurrent);

		Utils::Lua::RegTable(this->state, "active", Active);
		Utils::Lua::RegTable(this->state, "get_attachments_size", GetAttachmentSize);
		Utils::Lua::RegTable(this->state, "get_attachment", GetAttachment);

		Utils::Lua::RegTable(this->state, "clear", Clear);
		Utils::Lua::RegTable(this->state, "set_clear_modes", SetClearModes);
		Utils::Lua::RegTable(this->state, "set_viewport", SwitchViewPort);

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
			if (!Utils::Lua::GetTable(L, 1, "texture_count", textureCount))
				return luaL_error(L, "argument texture_count needs to be a number");

			if (textureCount > 0)
			{
				unsigned int* textures = new unsigned int[textureCount];

				if (Utils::Lua::GetTable(L, 1, "textures", textures, textureCount))
				{
					for (int i = 1; i <= textureCount; i++)
					{
						if (!TextureConnection::Get()->Exists(textures[i]))
						{
							Debug::Logging::Log(
								"Failed to create framebuffer because texture " + std::to_string(textures[i]) + " dont exist",
								Debug::LogSeverity::Warning,
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
					return luaL_error(L, "argument texture_count needs to be a table");
				}
			}
			else return luaL_error(L, "argument texture_count needs to greater than zero");
			
			// depth attachment
			unsigned int depthTexture;
			if (Utils::Lua::GetTable(L, 1, "depth_attachment", depthTexture))
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

				if (!Utils::Lua::GetTable(L, -1, "type", str))
					return luaL_error(L, "argument type needs to be a string");

				config.renderBufferAttachment.type = GPU::GetRenderBufferAttachmentTypeFromString(str);

				if (!Utils::Lua::GetTable(L, -1, "format", str))
					return luaL_error(L, "argument format needs to be a string");
				
				config.renderBufferAttachment.format = GPU::GetRenderBufferFormatFromString(str);

				if (!Utils::Lua::GetTable(L, -1, "size", config.renderBufferAttachment.size))
					return luaL_error(L, "argument size needs to be a vec2");
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
			instance->framebuffers.erase(lua_tonumber(L, 1));
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 0;
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
			}
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 0;
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

		return 0;
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
			lua_pushnumber(L, 1);
		else lua_pushnumber(L, framebuffer->GetAttachmentSize());

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

	int FramebufferConnection::Clear(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		glm::vec4 color;;
		if (!lua_isnumber(L, 1))
			color.x = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (!lua_isnumber(L, 2))
			color.y = lua_tonumber(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a number");

		if (!lua_isnumber(L, 3))
			color.z = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		if (!lua_isnumber(L, 4))
			color.w = lua_tonumber(L, 4);
		else return luaL_error(L, "argument 4 is expected to be a number");

		GPU::Framebuffer::Clear(color);

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
			
			if (!Utils::Lua::GetTable(L, 1, "COLOR", value))
			{
				if (value)
					modes.insert(GPU::ClearMode::COLOR);
			}
			else return luaL_error(L, "expecting argument COLOR to be a boolean");

			if (!Utils::Lua::GetTable(L, 1, "DEPTH", value))
			{
				if (value)
					modes.insert(GPU::ClearMode::DEPTH);
			}
			else return luaL_error(L, "expecting argument DEPTH to be a boolean");

			if (!Utils::Lua::GetTable(L, 1, "STENCIL", value))
			{
				if (value)
					modes.insert(GPU::ClearMode::STENCIL);
			}
			else return luaL_error(L, "expecting argument STENCIL to be a boolean");

			GPU::Framebuffer::SetClearModes(modes);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int FramebufferConnection::SwitchViewPort(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 4)
			return luaL_error(L, "expecting 4 arguments in function call");

		glm::vec4 vec;
		if (lua_isnumber(L, 1))
			vec.x = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		if (lua_isnumber(L, 2))
			vec.y = lua_tonumber(L, 2);
		else return luaL_error(L, "argument 2 is expected to be a number");

		if (lua_isnumber(L, 3))
			vec.z = lua_tonumber(L, 3);
		else return luaL_error(L, "argument 3 is expected to be a number");

		if (lua_isnumber(L, 4))
			vec.w = lua_tonumber(L, 4);
		else return luaL_error(L, "argument 4 is expected to be a number");

		GPU::Framebuffer::SwitchViewPort({ vec.x, vec.y }, { vec.z, vec.w });

		return 1;
	}
}}}