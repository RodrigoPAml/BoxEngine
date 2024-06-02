#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Audio {

	class Audio;
	typedef std::shared_ptr<Audio> AudioPtr;

	/// <summary>
	/// Represents an instance of an audio file
	/// </summary>
	class Audio
	{
	private:
		// Internal reference
		static irrklang::ISoundEngine* engine;

		// Total Instances 
		static int TotalInstances;

		// The path of this file
		std::string path;

		// Sound internal reference
		irrklang::ISound* sound = nullptr;

		// If was loaded as 2d or 3d
		bool is2D = true;
	public:
		Audio(std::string path);
		~Audio();

		void Instantiate2D();
		void Instantiate3D();

		void Stop();
		void Restart();

		bool IsFinished();

		void SetPosition(const glm::vec3& pos);
		glm::vec3 GetPosition();

		void SetVelocity(const glm::vec3& pos);
		glm::vec3 GeVelocity();

		void SetLoop(bool loop);
		bool GetLoop();

		void SetPaused(bool paused);
		bool GetPaused();
		
		void SetMinDistance(float dist);
		float GetMinDistance();

		void SetMaxDistance(float dist);
		float GetMaxDistance();

		void SetPan(float pan);
		float GetPan();

		void SetSpeed(float speed);
		float GetSpeed();

		void SetPlayPosition(float position);
		float GetPlayPosition();

		float GetPlayLength();

		void SetVolume(float volume);
		float GetVolume();

		static void SetListenerPosition(const glm::vec3& pos, const glm::vec3& dir);
		static void StopAllAudios();
		static int GetInstaceCount();
		static void ReleaseEngine();
	};
}}}
