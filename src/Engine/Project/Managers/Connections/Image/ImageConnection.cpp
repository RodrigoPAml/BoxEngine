#include <BoxEngine.hpp>
#include "ImageConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<ImageConnection> ImageConnection::current;

	ImageConnection::ImageConnection(lua_State* state)
	{
		this->state = state;
	}

	void ImageConnection::Bind()
	{
		lua_newtable(this->state);

		Utils::Lua::RegTable(this->state, "open", OpenImage);

		lua_setglobal(this->state, "_img_");
	}

	void ImageConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	ImageConnectionPtr ImageConnection::Get()
	{
		return current.lock();
	}

	void ImageConnection::Set(ImageConnectionPtr instance)
	{
		current = instance;
	}

	int ImageConnection::OpenImage(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string path = "";
		if (lua_isstring(L, 1))
			path = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be string");

		Utils::ImagePtr img = nullptr;

		try
		{
			img = Utils::ImagePtr(new Utils::Image(path));
		}
		catch (std::exception)
		{
			lua_pushnil(L);
			return 1;
		}

		if (img == nullptr)
			lua_pushnil(L);
		else
		{
			lua_newtable(L);
			Utils::Lua::RegTable(L, "size", img->GetSize());
			Utils::Lua::RegTable(L, "path", img->GetLoadedPath());
			
			auto format = img->GetFormat();
			auto formatStr = "";

			if (format == GPU::TextureFormat::RGB)
				formatStr = "RGB";
			else if (format == GPU::TextureFormat::RGBA)
				formatStr = "RGBA";
			else if (format == GPU::TextureFormat::R)
				formatStr = "R";
			else
				formatStr = "RGB";
			
			Utils::Lua::RegTable(L, "format", formatStr);
			Utils::Lua::RegTable(L, "data", img->GetData(), (int)(img->GetSize().x*img->GetSize().y));
		}

		return 1;
	}
}}}