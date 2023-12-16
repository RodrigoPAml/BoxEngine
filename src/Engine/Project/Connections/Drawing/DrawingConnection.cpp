#include <BoxEngine.hpp>
#include "DrawingConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<DrawingConnection> DrawingConnection::current;

	DrawingConnection::DrawingConnection(lua_State* state)
	{
		this->state = state;
	}

	void DrawingConnection::Bind()
	{
		lua_newtable(this->state);
		
		LuaUtils::RegTable(this->state, "circle", Draw2DCircle);
		LuaUtils::RegTable(this->state, "line", Draw2DLine);
		LuaUtils::RegTable(this->state, "point", Draw2DPoint);
		LuaUtils::RegTable(this->state, "rect", Draw2DRectangle);
		LuaUtils::RegTable(this->state, "triangle", Draw2DTriangle);
		LuaUtils::RegTable(this->state, "texture", DrawTexture);
		LuaUtils::RegTable(this->state, "frame", DrawFrame);

		lua_setglobal(this->state, "_draw2d_");

		lua_newtable(this->state);

		LuaUtils::RegTable(this->state, "circle", Draw3DCircle);
		LuaUtils::RegTable(this->state, "cube", Draw3DCube);
		LuaUtils::RegTable(this->state, "line", Draw3DLine);
		LuaUtils::RegTable(this->state, "point", Draw3DPoint);
		LuaUtils::RegTable(this->state, "rect", Draw3DRect);
		LuaUtils::RegTable(this->state, "sphere", Draw3DSphere);
		LuaUtils::RegTable(this->state, "triangle", Draw3DTriangle);

		lua_setglobal(this->state, "_draw3d_");
	}

	void DrawingConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	DrawingConnectionPtr DrawingConnection::Get()
	{
		return current.lock();
	}

	void DrawingConnection::Set(DrawingConnectionPtr instance)
	{
		current = instance;
	}

	int DrawingConnection::Draw2DRectangle(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec2 position, size;
			glm::vec4 color = { 1, 0, 0, 1 };
			float rotation = 0;
			bool filled = true;

			LuaUtils::GetTable(L, 1, "color", color);

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec2");

			if (!LuaUtils::GetTable(L, 1, "size", size))
				return luaL_error(L, "expecting size argument to be a vec2");

			LuaUtils::GetTable(L, 1, "rotation", rotation);
			LuaUtils::GetTable(L, 1, "filled", filled);

			Drawing::Primitives2D::DrawRectangle(position, size, rotation, color, filled);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw2DCircle(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec2 position, size;
			float rotation = 0;
			bool filled = true;

			LuaUtils::GetTable(L, 1, "color", color);

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec2");

			if (!LuaUtils::GetTable(L, 1, "size", size))
				return luaL_error(L, "expecting size argument to be a vec2");

			LuaUtils::GetTable(L, 1, "rotation", rotation);
			LuaUtils::GetTable(L, 1, "filled", filled);

			Drawing::Primitives2D::DrawCircle(position, size, rotation, color, filled);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}
	
	int DrawingConnection::Draw2DTriangle(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");
	
		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec2 position, size;
			float rotation = 0;
			bool filled = true;

			if (!LuaUtils::GetTable(L, 1, "size", size))
				return luaL_error(L, "expecting size argument to be a vec2");

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec2");

			LuaUtils::GetTable(L, 1, "color", color);
			LuaUtils::GetTable(L, 1, "rotation", rotation);
			LuaUtils::GetTable(L, 1, "filled", filled);

			Drawing::Primitives2D::DrawRectangle(position, size, rotation, color, filled);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw2DPoint(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec2 position;

			if (!LuaUtils::GetTable(L, 1, "color", color))
				return luaL_error(L, "expecting color argument to be a vec3");

			LuaUtils::GetTable(L, 1, "position", position);

			Drawing::Primitives2D::DrawPoint(position, color);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw2DLine(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec2 pos1, pos2;

			LuaUtils::GetTable(L, 1, "color", color);

			if (!LuaUtils::GetTable(L, 1, "position_start", pos1))
				return luaL_error(L, "expecting position_start argument to be a vec2");

			if (!LuaUtils::GetTable(L, 1, "position_end", pos2))
				return luaL_error(L, "expecting position_end argument to be a vec2");

			Drawing::Primitives2D::DrawLine(pos1, pos2, color);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw3DCube(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec3 position, size, rotation = { 0, 0, 0 };
			bool filled = false;

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec3");

			if (!LuaUtils::GetTable(L, 1, "size", size))
				return luaL_error(L, "expecting size argument to be a vec3");

			LuaUtils::GetTable(L, 1, "color", color);
			LuaUtils::GetTable(L, 1, "rotation", rotation);
			LuaUtils::GetTable(L, 1, "filled", filled);

			Drawing::Primitives3D::DrawCube(position, size, rotation, color, filled);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw3DSphere(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec3 position, size, rotation = { 0, 0, 0 };
			bool filled = false;

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec3");

			if (!LuaUtils::GetTable(L, 1, "size", size))
				return luaL_error(L, "expecting size argument to be a vec3");

			LuaUtils::GetTable(L, 1, "rotation", rotation);
			LuaUtils::GetTable(L, 1, "color", color);
			LuaUtils::GetTable(L, 1, "filled", filled);

			Drawing::Primitives3D::DrawSphere(position, size, rotation, color, filled);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw3DPoint(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec3 position;

			LuaUtils::GetTable(L, 1, "color", color);

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec3");

			Drawing::Primitives3D::DrawPoint(position, color);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw3DLine(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec3 position1, position2;

			LuaUtils::GetTable(L, 1, "color", color);

			if (!LuaUtils::GetTable(L, 1, "position_start", position1))
				return luaL_error(L, "expecting position_start argument to be a vec3");

			if (!LuaUtils::GetTable(L, 1, "position_end", position2))
				return luaL_error(L, "expecting position_end argument to be a vec3");

			Drawing::Primitives3D::DrawLine(position1, position2, color);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw3DRect(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec3 position, size, rotation = { 0, 0, 0 };
			bool filled = false;

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec3");

			if (!LuaUtils::GetTable(L, 1, "size", size))
				return luaL_error(L, "expecting size argument to be a vec3");
			
			LuaUtils::GetTable(L, 1, "color", color);
			LuaUtils::GetTable(L, 1, "rotation", rotation);
			LuaUtils::GetTable(L, 1, "filled", filled);

			Drawing::Primitives3D::DrawRect(position, size, rotation, color, filled);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw3DTriangle(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec3 position, size, rotation = { 0, 0, 0 };
			bool filled = false;

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec3");

			if (!LuaUtils::GetTable(L, 1, "size", size))
				return luaL_error(L, "expecting size argument to be a vec3");

			LuaUtils::GetTable(L, 1, "rotation", rotation);
			LuaUtils::GetTable(L, 1, "filled", filled);
			LuaUtils::GetTable(L, 1, "color", color);

			Drawing::Primitives3D::DrawTriangle(position, size, rotation, color, filled);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::Draw3DCircle(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec4 color = { 1, 0, 0, 1 };
			glm::vec3 position, size, rotation = { 0, 0, 0 };
			bool filled = false;

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec3");

			if (!LuaUtils::GetTable(L, 1, "size", size))
				return luaL_error(L, "expecting size argument to be a vec3");

			LuaUtils::GetTable(L, 1, "rotation", rotation);
			LuaUtils::GetTable(L, 1, "filled", filled);
			LuaUtils::GetTable(L, 1, "color", color);

			Drawing::Primitives3D::DrawCircle(position, size, rotation, color, filled);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::DrawTexture(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_istable(L, 1))
		{
			glm::vec2 position, size;
			glm::vec4 color = { 0, 0, 0 ,0 };
			float rotation = 0;
			unsigned int textureId;

			if (!LuaUtils::GetTable(L, 1, "position", position))
				return luaL_error(L, "expecting position argument to be a vec2");

			if (!LuaUtils::GetTable(L, 1, "size", size))
				return luaL_error(L, "expecting size argument to be a vec2");

			if (!LuaUtils::GetTable(L, 1, "texture_id", textureId))
				return luaL_error(L, "expecting texture_id argument to be a number");

			LuaUtils::GetTable(L, 1, "rotation", rotation);
			LuaUtils::GetTable(L, 1, "color", color);

			auto texture = TextureConnection::Get()->Get(textureId);
		
			if(texture != nullptr)
				Drawing::TextureRenderer::Draw(texture, position, size, color, rotation);
		}
		else return luaL_error(L, "expecting argument 1 to be a table");

		return 0;
	}

	int DrawingConnection::DrawFrame(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			unsigned int textureId = lua_tonumber(L, 1);

			auto windowLimits = Project::GetCurrentProject()->GetScreenLimits();
			auto windowSize = glm::vec2(std::abs(windowLimits.x - windowLimits.z), std::abs(windowLimits.y - windowLimits.w));

			glm::vec2 position = glm::vec2(windowLimits.x + windowSize.x / 2, windowLimits.y + windowSize.y / 2);
			glm::vec4 color = { 0, 0, 0 ,0 };
			float rotation = 0;

			auto texture = TextureConnection::Get()->Get(textureId);

			if (texture != nullptr)
				Drawing::TextureRenderer::Draw(texture, position, windowSize, color, rotation);
		}
		else return luaL_error(L, "expecting argument 1 to be a number");

		return 0;
	}

	bool DrawingConnection::HaveFramebuffer()
	{
		return GPU::Framebuffer::GetCurrendUsedId() != 0;
	}
}}}}