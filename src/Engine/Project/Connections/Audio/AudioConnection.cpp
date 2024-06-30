#include <BoxEngine.hpp>
#include "AudioConnection.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	std::weak_ptr<AudioConnection> AudioConnection::current;

	AudioConnection::AudioConnection(lua_State* state)
	{
		this->state = state;
	}

	void AudioConnection::Bind()
	{
		lua_newtable(this->state);
		
		LuaUtils::RegTable(this->state, "create_2d", Create2DAudio);
		LuaUtils::RegTable(this->state, "create_3d", Create3DAudio);
		LuaUtils::RegTable(this->state, "destroy", DestroyAudio);

		LuaUtils::RegTable(this->state, "resume", Resume);
		LuaUtils::RegTable(this->state, "pause", Pause);
		LuaUtils::RegTable(this->state, "restart", Restart);
		LuaUtils::RegTable(this->state, "stop", Stop);

		LuaUtils::RegTable(this->state, "is_finished", IsFinished);

		LuaUtils::RegTable(this->state, "get_position", GetPosition);
		LuaUtils::RegTable(this->state, "set_position", SetPosition);

		LuaUtils::RegTable(this->state, "set_velocity", SetVelocity);
		LuaUtils::RegTable(this->state, "get_velocity", GetVelocity);

		LuaUtils::RegTable(this->state, "set_loop", SetLoop);
		LuaUtils::RegTable(this->state, "get_loop", GetLoop);

		LuaUtils::RegTable(this->state, "set_min_distance", SetMinDistance);
		LuaUtils::RegTable(this->state, "get_min_distance", GetMinDistance);

		LuaUtils::RegTable(this->state, "set_max_distance", SetMaxDistance);
		LuaUtils::RegTable(this->state, "get_max_distance", GetMaxDistance);

		LuaUtils::RegTable(this->state, "set_pan", SetPan);
		LuaUtils::RegTable(this->state, "get_pan", GetPan);

		LuaUtils::RegTable(this->state, "set_speed", SetSpeed);
		LuaUtils::RegTable(this->state, "get_speed", GetSpeed);

		LuaUtils::RegTable(this->state, "get_length", GetPlayLength);

		LuaUtils::RegTable(this->state, "set_play_position", SetPlayPosition);
		LuaUtils::RegTable(this->state, "get_play_position", GetPlayPosition);

		LuaUtils::RegTable(this->state, "set_volume", SetVolume);
		LuaUtils::RegTable(this->state, "get_volume", GetVolume);

		LuaUtils::RegTable(this->state, "set_listener_position", SetListenerPosition);
		LuaUtils::RegTable(this->state, "stop_all", StopAllAudios);

		lua_setglobal(this->state, "_audio_");
	}

	void AudioConnection::SetCurrentGo(GameObjectPtr go)
	{
		this->currentGo = go;
	}

	AudioConnectionPtr AudioConnection::Get()
	{
		return current.lock();
	}

	void AudioConnection::Set(AudioConnectionPtr instance)
	{
		current = instance;
	}
	
	int AudioConnection::Create2DAudio(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string audioPath = "";

		if (lua_isstring(L, 1))
			audioPath = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		Audio::AudioPtr audio = nullptr;
		auto instance = AudioConnection::Get();

		try
		{
			audio = Audio::AudioPtr(new Audio::Audio(audioPath));
			audio->Instantiate2D();

			instance->audios[++instance->currentId] = audio;
			lua_pushnumber(L, instance->currentId);
			return 1;
		}
		catch (std::exception)
		{
			lua_pushnil(L);
			audio = nullptr;
			instance = nullptr;
			return 1;
		}

		lua_pushnil(L);
		return 1;
	}

	int AudioConnection::Create3DAudio(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		std::string audioPath = "";

		if (lua_isstring(L, 1))
			audioPath = lua_tostring(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a string");

		Audio::AudioPtr audio = nullptr;
		auto instance = AudioConnection::Get();

		try
		{
			audio = Audio::AudioPtr(new Audio::Audio(audioPath));
			audio->Instantiate3D();

			instance->audios[++instance->currentId] = audio;
			lua_pushnumber(L, instance->currentId);
			return 1;
		}
		catch (std::exception)
		{
			lua_pushnil(L);
			audio = nullptr;
			instance = nullptr;
			return 1;
		}

		lua_pushnil(L);
		return 1;
	}

	int AudioConnection::DestroyAudio(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 argument in function call");

		if (lua_isnumber(L, 1))
		{
			auto instance = AudioConnection::Get();
			lua_pushboolean(L, instance->audios.erase(lua_tonumber(L, 1)));
		}
		else return luaL_error(L, "argument 1 is expected to be a number");

		return 1;
	}

	int AudioConnection::Pause(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetPaused(true);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::Resume(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetPaused(false);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::Restart(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->Restart();

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::Stop(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->Stop();

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::IsFinished(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
			lua_pushboolean(L, true);
		else 
			lua_pushboolean(L, audio->IsFinished());

		return 1;
	}

	int AudioConnection::SetPosition(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		glm::vec3 vec;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, -1, "x", vec.x))
				return luaL_error(L, "argument x is expected to be a number");

			if (!LuaUtils::GetTable(L, -2, "y", vec.y))
				return luaL_error(L, "argument y is expected to be a number");

			if (!LuaUtils::GetTable(L, -3, "z", vec.z))
				return luaL_error(L, "argument z is expected to be a number");
		}
		else return luaL_error(L, "argument 2 is expected to be a table with vec3 format");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetPosition(vec);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::GetPosition(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0; 
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		auto vec = audio->GetPosition();

		lua_newtable(L);

		lua_pushstring(L, "x");
		lua_pushnumber(L, vec.x);
		lua_settable(L, -3);

		lua_pushstring(L, "y");
		lua_pushnumber(L, vec.y);
		lua_settable(L, -3);

		lua_pushstring(L, "z");
		lua_pushnumber(L, vec.z);
		lua_settable(L, -3);

		return 1;
	}

	int AudioConnection::SetVelocity(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		glm::vec3 vec;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, -1, "x", vec.x))
				return luaL_error(L, "argument x is expected to be a number");

			if (!LuaUtils::GetTable(L, -2, "y", vec.y))
				return luaL_error(L, "argument y is expected to be a number");

			if (!LuaUtils::GetTable(L, -3, "z", vec.z))
				return luaL_error(L, "argument z is expected to be a number");
		}
		else return luaL_error(L, "argument 2 is expected to be a table with vec3 format");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetVelocity(vec);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::GetVelocity(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		auto vec = audio->GeVelocity();

		lua_newtable(L);

		lua_pushstring(L, "x");
		lua_pushnumber(L, vec.x);
		lua_settable(L, -3);

		lua_pushstring(L, "y");
		lua_pushnumber(L, vec.y);
		lua_settable(L, -3);

		lua_pushstring(L, "z");
		lua_pushnumber(L, vec.z);
		lua_settable(L, -3);

		return 1;
	}

	int AudioConnection::SetLoop(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		bool value = false;
		if (lua_isboolean(L, 2))
			value = lua_toboolean(L, 2);
		else luaL_error(L, "argument 2 is expected to be a boolean");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetLoop(value);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::GetLoop(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		lua_pushboolean(L, audio->GetLoop());

		return 1;
	}

	int AudioConnection::SetMinDistance(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		float distance = 0;
		if (lua_isnumber(L, 2))
			distance = lua_tonumber(L, 2);
		else luaL_error(L, "argument 2 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetMinDistance(distance);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::GetMinDistance(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		lua_pushnumber(L, audio->GetMinDistance());

		return 1;
	}

	int AudioConnection::SetMaxDistance(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		float distance = 0;
		if (lua_isnumber(L, 2))
			distance = lua_tonumber(L, 2);
		else luaL_error(L, "argument 2 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetMaxDistance(distance);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::GetMaxDistance(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		lua_pushnumber(L, audio->GetMaxDistance());

		return 1;
	}

	int AudioConnection::SetPan(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		float distance = 0;
		if (lua_isnumber(L, 2))
			distance = lua_tonumber(L, 2);
		else luaL_error(L, "argument 2 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetMaxDistance(distance);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::GetPan(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		lua_pushnumber(L, audio->GetPan());

		return 1;
	}

	int AudioConnection::SetSpeed(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		float value = 0;
		if (lua_isnumber(L, 2))
			value = lua_tonumber(L, 2);
		else luaL_error(L, "argument 2 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetSpeed(value);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::GetSpeed(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		lua_pushnumber(L, audio->GetSpeed());

		return 1;
	}

	int AudioConnection::SetPlayPosition(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		float value = 0;
		if (lua_isnumber(L, 2))
			value = lua_tonumber(L, 2);
		else luaL_error(L, "argument 2 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetPlayPosition(value);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::GetPlayPosition(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		lua_pushnumber(L, audio->GetPlayPosition());
		return 1;
	}

	int AudioConnection::GetPlayLength(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		lua_pushnumber(L, audio->GetPlayLength());

		return 1;
	}

	int AudioConnection::SetVolume(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		float value = 0;
		if (lua_isnumber(L, 2))
			value = lua_tonumber(L, 2);
		else luaL_error(L, "argument 2 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio != nullptr)
			audio->SetVolume(value);

		lua_pushboolean(L, audio != nullptr);

		return 1;
	}

	int AudioConnection::GetVolume(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 1)
			return luaL_error(L, "expecting 1 arguments in function call");

		int id = 0;
		if (lua_isnumber(L, 1))
			id = lua_tonumber(L, 1);
		else return luaL_error(L, "argument 1 is expected to be a number");

		auto instance = AudioConnection::Get();
		auto audio = instance->audios[id];

		if (audio == nullptr)
		{
			lua_pushnil(L);
			return 1;
		}

		lua_pushnumber(L, audio->GetVolume());

		return 1;
	}

	int AudioConnection::StopAllAudios(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		Audio::Audio::StopAllAudios();

		return 0;
	}

	int AudioConnection::SetListenerPosition(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 2)
			return luaL_error(L, "expecting 2 arguments in function call");

		glm::vec3 vec1;
		if (lua_istable(L, 1))
		{
			if (!LuaUtils::GetTable(L, -1, "x", vec1.x))
				return luaL_error(L, "argument x is expected to be a number");

			if (!LuaUtils::GetTable(L, -2, "y", vec1.y))
				return luaL_error(L, "argument y is expected to be a number");

			if (!LuaUtils::GetTable(L, -3, "z", vec1.z))
				return luaL_error(L, "argument z is expected to be a number");
		}
		else return luaL_error(L, "argument 1 is expected to be a table with vec3 format");

		glm::vec3 vec2;
		if (lua_istable(L, 2))
		{
			if (!LuaUtils::GetTable(L, -1, "x", vec2.x))
				return luaL_error(L, "argument x is expected to be a number");

			if (!LuaUtils::GetTable(L, -2, "y", vec2.y))
				return luaL_error(L, "argument y is expected to be a number");

			if (!LuaUtils::GetTable(L, -3, "z", vec2.z))
				return luaL_error(L, "argument z is expected to be a number");
		}
		else return luaL_error(L, "argument 2 is expected to be a table with vec3 format");

		Audio::Audio::SetListenerPosition(vec1, vec2);
		return 0;
	}

	int AudioConnection::GetTotalInstacesCount(lua_State* L)
	{
		auto top = lua_gettop(L);

		if (top != 0)
			return luaL_error(L, "expecting no arguments in function call");

		lua_pushnumber(L, Audio::Audio::GetInstaceCount());

		return 1;
	}
}}}}