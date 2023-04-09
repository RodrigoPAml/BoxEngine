#include <BoxEngine.hpp>
#include "TimeConnection.hpp"

namespace BoxEngine {
namespace Project {
namespace Connection {

	std::weak_ptr<TimeConnection> TimeConnection::current;

	TimeConnection::TimeConnection(lua_State* state)
	{
		this->state = state;
	}

	void TimeConnection::Bind()
	{
		lua_newtable(this->state);

		Utils::Lua::RegTable(this->state, "get_timestamp", GetTimestamp);
		Utils::Lua::RegTable(this->state, "get_datetime", GetDateTime);

		lua_setglobal(this->state, "_time_");
	}

	void TimeConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	TimeConnectionPtr TimeConnection::Get()
	{
		return current.lock();
	}

	void TimeConnection::Set(TimeConnectionPtr instance)
	{
		current = instance;
	}

	int TimeConnection::GetTimestamp(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no arguments in function call");

		lua_pushnumber(L, Utils::Time::GetTimestamp());

		return 1;
	}
	
	int TimeConnection::GetDateTime(lua_State* L)
	{
		if (lua_gettop(L) != 0)
			return luaL_error(L, "expecting no arguments in function call");

		auto date = Utils::Time::GetDateTime();

		lua_newtable(L);

		Utils::Lua::RegTable(L, "day", date.day);
		Utils::Lua::RegTable(L, "hour", date.hour);
		Utils::Lua::RegTable(L, "month", date.month);
		Utils::Lua::RegTable(L, "minute", date.minute);
		Utils::Lua::RegTable(L, "second", date.second);
		Utils::Lua::RegTable(L, "year", (int)date.year);

		return 1;
	}
}}}