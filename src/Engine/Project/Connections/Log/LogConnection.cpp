#include <BoxEngine.hpp>
#include "LogConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<LogConnection> LogConnection::current;

	LogConnection::LogConnection(lua_State* state)
	{
		this->state = state;
	}

	void LogConnection::Bind()
	{
		// Logs
		lua_register(this->state, "__log__", DebugLog);
		lua_register(this->state, "__error__", DebugError);
		lua_register(this->state, "__warning__", DebugWarning);
	}

	void LogConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	LogConnectionPtr LogConnection::Get()
	{
		return current.lock();
	}

	void LogConnection::Set(LogConnectionPtr instance)
	{
		current = instance;
	}

	int LogConnection::DebugLog(lua_State* L)
	{
		// Show logs
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in log function");

		std::string message;

		if (lua_isstring(L, 1))
			message = lua_tostring(L, 1);
		else if (lua_isnumber(L, 1))
			message = lua_tonumber(L, 1);
		else if (lua_isboolean(L, 1))
			message = lua_toboolean(L, 1) == 0 ? "false" : "true";
		else if (lua_isnoneornil(L, 1))
			message = "nil";
		else
			return luaL_error(L, "argument with unexpected type in log function");

		auto treatedMessage = "[Script]: " + message;
		Debug::Logging::Log(
			treatedMessage,
			Debug::LogSeverity::Notify,
			Debug::LogOrigin::UserGenerated,
			{
				{"go_id", Get()->currentGo.lock()->GetId()}
			}
		);

		return 0;
	}

	int LogConnection::DebugWarning(lua_State* L)
	{
		// Show warnings
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in warning function");

		std::string message;

		if (lua_isstring(L, 1))
			message = lua_tostring(L, 1);
		else if (lua_isnumber(L, 1))
			message = lua_tonumber(L, 1);
		else if (lua_isboolean(L, 1))
			message = lua_toboolean(L, 1) == 0 ? "false" : "true";
		else if (lua_isnoneornil(L, 1))
			message = "nil";
		else
			return luaL_error(L, "argument with unexpected type in warning function");

		auto treatedMessage = "[Script]: " + message;
		Debug::Logging::Log(treatedMessage, Debug::LogSeverity::Warning, Debug::LogOrigin::UserGenerated,
		{
			{"go_id", Get()->currentGo.lock()->GetId()}
		});

		return 0;
	}

	int LogConnection::DebugError(lua_State* L)
	{
		// Show errors
		if (lua_gettop(L) != 1)
			return luaL_error(L, "expecting 1 argument in error function");

		std::string message;

		if (lua_isstring(L, 1))
			message = lua_tostring(L, 1);
		else if (lua_isnumber(L, 1))
			message = lua_tonumber(L, 1);
		else if (lua_isboolean(L, 1))
			message = lua_toboolean(L, 1) == 0 ? "false" : "true";
		else if (lua_isnoneornil(L, 1))
			message = "nil";
		else
			return luaL_error(L, "argument with unexpected type in error function");

		auto treatedMessage = "[Script]: " + message;
		Debug::Logging::Log(treatedMessage, Debug::LogSeverity::Error, Debug::LogOrigin::UserGenerated,
		{
			{"go_id", Get()->currentGo.lock()->GetId()}
		});

		return 0;
	}
}}}}