#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
namespace Connection {

	class AudioConnection;
	typedef std::shared_ptr<AudioConnection> AudioConnectionPtr;
	typedef std::weak_ptr<AudioConnection> AudioConnectionWeakPtr;

	/// <summary>
	/// Functions C++/LUA to handle audio functions.
	/// </summary>
	class AudioConnection
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
		/// Audio maps
		/// </summary>
		std::unordered_map<long, Audio::AudioPtr> audios;

		/// <summary>
		/// Global reference.
		/// </summary>
		static std::weak_ptr<AudioConnection> current;
	public:
		AudioConnection(lua_State* state);

		void Bind();
		void SetCurrentGo(GameObjectPtr go);

		static AudioConnectionPtr Get();
		static void Set(AudioConnectionPtr instance);
	private:
		static int Create2DAudio(lua_State* L);
		static int Create3DAudio(lua_State* L);

		static int DestroyAudio(lua_State* L);

		static int Pause(lua_State* L);
		static int Resume(lua_State* L);
		static int Restart(lua_State* L);

		static int IsFinished(lua_State* L);

		static int SetPosition(lua_State* L);
		static int GetPosition(lua_State* L);

		static int SetVelocity(lua_State* L);
		static int GetVelocity(lua_State* L);

		static int SetLoop(lua_State* L);
		static int GetLoop(lua_State* L);

		static int SetMinDistance(lua_State* L);
		static int GetMinDistance(lua_State* L);

		static int SetMaxDistance(lua_State* L);
		static int GetMaxDistance(lua_State* L);

		static int SetPan(lua_State* L);
		static int GetPan(lua_State* L);

		static int SetSpeed(lua_State* L);
		static int GetSpeed(lua_State* L);

		static int SetPlayPosition(lua_State* L);
		static int GetPlayPosition(lua_State* L);

		static int GetPlayLength(lua_State* L);

		static int SetVolume(lua_State* L);
		static int GetVolume(lua_State* L);

		static int StopAllAudios(lua_State* L);

		static int SetListenerPosition(lua_State* L);
		static int GetTotalInstacesCount(lua_State* L);
	};
}}}}