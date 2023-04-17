#include <BoxEngine.hpp>
#include "Script.hpp"

namespace BoxEngine {
namespace Project {

	int Script::Total = 0;

	Script::Script(std::string name)
	{
		this->isStarted = false;
		this->haveWarningInLoad = false;
		this->state = ScriptState::ToLoad;
		this->name = name;
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
		this->name = Utils::Directory::GetLastPartFromPathNoExtension(path);
	}

	std::string Script::GetPath() const
	{
		return this->path;
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

		if (state == this->state)
			return;

		this->state = state;
	}

	ScriptState Script::GetState() const
	{
		return this->state;
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

	bool Script::IsStarted() const
	{
		return this->isStarted;
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

	int Script::GetCurrentScriptsCount()
	{
		return Total;
	}
}}
