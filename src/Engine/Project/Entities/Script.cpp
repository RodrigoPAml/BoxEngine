#include <BoxEngine.hpp>
#include "Script.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {

	int Script::Total = 0;

	Script::Script(std::string name)
	{
		this->isStarted = false;
		this->haveWarningInLoad = false;
		this->state = ScriptState::ToLoad;
		this->name = name;
		this->active = true;

		Total++;
	}

	Script::~Script()
	{
		Total--;
	}

	std::string Script::GetName() const
	{
		return this->name;
	}

	void Script::SetPath(const std::string& path)
	{
		this->path = path;
		this->name = Modules::Utils::Directory::GetLastPartFromPathNoExtension(path);
	}

	std::string Script::GetPath() const
	{
		return this->path;
	}

	void Script::SetActive(const bool active)
	{
		this->active = active;
	}

	bool Script::GetActive() const
	{
		return this->active;
	}

	void Script::SetState(ScriptState state)
	{
		if (this->state == ScriptState::Destroyed)
			return;

		if (state == ScriptState::ToLoad)
			return;

		if (state == ScriptState::ToStart && this->state != ScriptState::ToLoad)
			return;

		if (state == ScriptState::Updating && this->state != ScriptState::ToStart)
			return;

		if (state == ScriptState::Updating)
			this->isStarted = true;

		if (state == ScriptState::ToStart)
			this->isLoaded = true;

		if (state == this->state)
			return;

		this->state = state;
	}

	ScriptState Script::GetState() const
	{
		return this->state;
	}

	void Script::SetRunMode(RunMode mode)
	{
		this->mode = mode;
	}

	RunMode Script::GetRunMode() const
	{
		return this->mode;
	}

	void Script::AddScriptData(ScriptData data)
	{
		std::string name = data.GetName();

		if (name.empty())
			return;

		auto iter = std::find_if(this->datas.begin(), this->datas.end(), [name](ScriptData item) {return item.GetName() == name; });

		if(iter == this->datas.end())
			this->datas.push_back(data);
	}

	void Script::RemoveScriptData(const std::string& name)
	{
		auto& data = this->datas;

		data.erase(std::remove_if(data.begin(), data.end(), [name](ScriptData& item) {return item.GetName() == name; }), data.end());
	}

	void Script::SetScriptData(std::vector<ScriptData>& data)
	{
		this->datas = data;
	}

	std::vector<ScriptData>& Script::GetScriptData()
	{
		return this->datas;
	}

	void Script::AddDataNotShowed(const std::string& dataName)
	{
		auto it = std::find(this->cantShowDatas.begin(), this->cantShowDatas.end(), dataName);

		bool founded = it != this->cantShowDatas.end();

		if (!founded)
			this->cantShowDatas.push_back(dataName);
	}

	void Script::RemoveDataNotShowed(const std::string& dataName)
	{
		auto it = std::find(this->cantShowDatas.begin(), this->cantShowDatas.end(), dataName);

		bool founded = it != this->cantShowDatas.end();

		if (founded)
		{
			this->cantShowDatas.erase(std::remove_if(this->cantShowDatas.begin(), this->cantShowDatas.end(), [dataName](const std::string& element) {
				return element == dataName;
			}), this->cantShowDatas.end());
		}
	}

	bool Script::HaveDataNotShowed(const std::string& dataName)
	{
		auto it = std::find(this->cantShowDatas.begin(), this->cantShowDatas.end(), dataName);

		return it != this->cantShowDatas.end();
	}

	void Script::AddDataNotPersisted(const std::string& dataName)
	{
		auto it = std::find(this->cantPersistDatas.begin(), this->cantPersistDatas.end(), dataName);

		bool founded = it != this->cantPersistDatas.end();

		if (!founded)
			this->cantPersistDatas.push_back(dataName);
	}

	void Script::RemoveDataNotPersisted(const std::string& dataName)
	{
		auto it = std::find(this->cantPersistDatas.begin(), this->cantPersistDatas.end(), dataName);

		bool founded = it != this->cantPersistDatas.end();

		if (founded)
		{
			this->cantPersistDatas.erase(std::remove_if(this->cantPersistDatas.begin(), this->cantPersistDatas.end(), [dataName](const std::string& element) {
				return element == dataName;
				}), this->cantPersistDatas.end());
		}
	}

	bool Script::HaveDataNotPersisted(const std::string& dataName)
	{
		auto it = std::find(this->cantPersistDatas.begin(), this->cantPersistDatas.end(), dataName);

		return it != this->cantPersistDatas.end();
	}

	bool Script::IsStarted() const
	{
		return this->isStarted;
	}

	bool Script::IsLoaded() const
	{
		return this->isLoaded;
	}

	bool Script::HaveWarningToLoad()
	{
		return this->haveWarningInLoad;
	}

	void Script::MarkAsFailedToLoad()
	{
		this->haveWarningInLoad = true;
	}

	void Script::SetUpdateScriptData(bool value)
	{
		this->updateScriptData = value;
	}

	bool Script::GetUpdateScriptData() const
	{
		return this->updateScriptData;
	}

	bool Script::IsPersisted() const
	{
		return this->persist;
	}

	void Script::SetPersisted(bool value)
	{
		this->persist = value;
	}

	bool Script::IsRemovedAfterDestroyed() const
	{
		return this->removeWhenDestroyed;
	}

	void Script::SetRemovedAfterDestroyed(bool value)
	{
		this->removeWhenDestroyed = value;
	}

	int Script::GetCurrentScriptsCount()
	{
		return Total;
	}
}}}