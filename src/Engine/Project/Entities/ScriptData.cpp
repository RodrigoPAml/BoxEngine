#include <BoxEngine.hpp>
#include "Script.hpp"

namespace BoxEngine {
namespace Project {

	ScriptData::ScriptData(std::string name, std::string value, ScriptDataType type)
	{
		this->name = name;
		this->value = value;
		this->type = type;
		this->isModified = false;
	}

	void ScriptData::SetName(const std::string& name)
	{
		this->name = name;
	}

	std::string& ScriptData::GetName() 
	{
		return this->name;
	}

	void ScriptData::SetValue(const std::string& value)
	{
		this->value = value;
	}

	std::string& ScriptData::GetValue() 
	{
		return this->value;
	}

	void ScriptData::SetType(const ScriptDataType type)
	{
		this->type = type;
	}

	ScriptDataType& ScriptData::GetType() 
	{
		return this->type;
	}

	void ScriptData::SetModified(const bool value)
	{
		this->isModified = value;
	}
	
	bool ScriptData::IsModified()
	{
		return this->isModified;
	}
}}