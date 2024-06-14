#include <BoxEngine.hpp>
#include "RendererConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<RendererConnection> RendererConnection::current;

	RendererConnection::RendererConnection(lua_State* state)
	{
		this->state = state;
	}

	void RendererConnection::Bind()
	{
		lua_newtable(this->state);
		
		LuaUtils::RegTable(this->state, "render_obj", Render);

		lua_setglobal(this->state, "_renderer_");
	}

	void RendererConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	RendererConnectionPtr RendererConnection::Get()
	{
		return current.lock();
	}

	void RendererConnection::Set(RendererConnectionPtr instance)
	{
		current = instance;
	}

	int RendererConnection::Render(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (!HaveFramebuffer())
			return luaL_error(L, "no current framebuffer to draw");

		if (lua_isnumber(L, 1))
		{
			long id = lua_tonumber(L, 1);

			auto obj = ObjectConnection::FindObj(id);

			Modules::Drawing::Renderer::Draw(obj);
		}
		else return luaL_error(L, "expecting argument 1 to be a number");

		return 0;
	}

	bool RendererConnection::HaveFramebuffer()
	{
		return GPU::Framebuffer::GetCurrendUsedId() != 0;
	}
}}}}