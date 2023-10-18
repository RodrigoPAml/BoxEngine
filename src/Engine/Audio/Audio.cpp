#include <BoxEngine.hpp>
#include "Audio.hpp"

namespace BoxEngine {
namespace Audio {

	irrklang::ISoundEngine* Audio::engine = nullptr;

	int Audio::TotalInstances = 0;

	Audio::Audio(std::string path)
	{
		using namespace irrklang;

		this->path = path;

		if (engine == nullptr)
			engine = createIrrKlangDevice();

		if(engine == nullptr)
			Debug::Logging::LogException("[Audio]: Failed to initialize audio module", Debug::LogOrigin::Engine);

		TotalInstances++;
	}

	Audio::~Audio()
	{
		TotalInstances--;

		if (this->sound != nullptr)
		{
			this->sound->drop();
			this->sound = nullptr;
		}

		Debug::Logging::Log("[Audio]: Destroyed audio from " + this->path, Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

	void Audio::Instantiate2D()
	{
		if (engine == nullptr || this->sound != nullptr)
			return;

		using namespace irrklang;

		if(!Utils::Directory::Exists(this->path))
			return;

		this->sound = engine->play2D(this->path.c_str(), false, true, true, ESM_AUTO_DETECT, false);

		if(this->sound != nullptr)
			Debug::Logging::Log("[Audio]: Created 2D audio from " + this->path, Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
		else 
			Debug::Logging::LogException("[Audio]: Failed to create audio from " + this->path, Debug::LogOrigin::Engine);
	}

	void Audio::Instantiate3D()
	{
		if (engine == nullptr || this->sound != nullptr)
			return;

		if (!Utils::Directory::Exists(this->path))
			return;

		using namespace irrklang;
		this->sound = engine->play3D(this->path.c_str(), { 0, 0, 0 }, false, true, true, ESM_AUTO_DETECT, false);

		if (this->sound != nullptr)
			Debug::Logging::Log("[Audio]: Created 3D audio from " + this->path, Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
		else
			Debug::Logging::LogException("[Audio]: Failed to create audio from " + this->path, Debug::LogOrigin::Engine);
	}

	void Audio::Stop()
	{
		using namespace irrklang;

		if (engine == nullptr || this->sound == nullptr)
			return;

		this->sound->stop();
	}

	bool Audio::IsFinished()
	{
		if (this->sound == nullptr || engine == nullptr)
			return true;

		return this->sound->isFinished();
	}

	void Audio::SetPosition(const glm::vec3& pos)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setPosition({ pos.x, pos.y, pos.z });
	}

	glm::vec3 Audio::GetPosition()
	{
		if (this->sound == nullptr || engine == nullptr)
			return { 0, 0, 0 };

		auto pos = this->sound->getPosition();

		return { pos.X, pos.Y, pos.Z };
	}

	void Audio::SetVelocity(const glm::vec3& pos)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setVelocity({ pos.x, pos.y, pos.z });
	}

	glm::vec3 Audio::GeVelocity()
	{
		if (this->sound == nullptr || engine == nullptr)
			return { 0, 0, 0 };

		auto pos = this->sound->getVelocity();

		return { pos.X, pos.Y, pos.Z };
	}

	void Audio::SetLoop(bool loop)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setIsLooped(loop);
	}

	bool Audio::GetLoop()
	{
		if (this->sound == nullptr || engine == nullptr)
			return false;

		return this->sound->isLooped();
	}

	void Audio::SetPaused(bool paused)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setIsPaused(paused);
	}

	bool Audio::GetPaused()
	{
		if (this->sound == nullptr || engine == nullptr)
			return false;

		return this->sound->isLooped();
	}

	void Audio::SetMinDistance(float dist)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setMinDistance(dist);
	}

	float Audio::GetMinDistance()
	{
		if (this->sound == nullptr || engine == nullptr)
			return 0;

		return this->sound->getMinDistance();
	}

	void Audio::SetMaxDistance(float dist)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setMaxDistance(dist);
	}

	float Audio::GetMaxDistance()
	{
		if (this->sound == nullptr || engine == nullptr)
			return 0;

		return this->sound->getMaxDistance();
	}

	void Audio::SetPan(float pan)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setPan(pan);
	}

	float Audio::GetPan()
	{
		if (this->sound == nullptr || engine == nullptr)
			return 0;

		return this->sound->getPan();
	}

	void Audio::SetSpeed(float speed)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setPlaybackSpeed(speed);
	}

	float Audio::GetSpeed()
	{
		if (this->sound == nullptr || engine == nullptr)
			return 0;

		return this->sound->getPlaybackSpeed();
	}

	void Audio::SetPlayPosition(float position)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setPlayPosition(position);
	}

	float Audio::GetPlayPosition()
	{
		if (this->sound == nullptr || engine == nullptr)
			return 0;

		return this->sound->getPlayPosition();
	}

	float Audio::GetPlayLength()
	{
		if (this->sound == nullptr || engine == nullptr)
			return 0;

		return this->sound->getPlayLength();
	}

	void Audio::SetVolume(float volume)
	{
		if (this->sound == nullptr || engine == nullptr)
			return;

		this->sound->setVolume(volume);
	}

	float Audio::GetVolume()
	{
		if (this->sound == nullptr || engine == nullptr)
			return 0;

		return this->sound->getVolume();
	}

	void Audio::SetListenerPosition(const glm::vec3& pos, const glm::vec3& dir)
	{
		engine->setListenerPosition({ pos.x, pos.y, pos.z }, {dir.x, dir.y, dir.z});
	}

	void Audio::StopAllAudios()
	{
		if (engine != nullptr)
			engine->stopAllSounds();
	}

	int Audio::GetInstaceCount()
	{
		return TotalInstances;
	}

	void Audio::ReleaseEngine()
	{
		if (engine != nullptr)
			engine->drop();
	}
}}