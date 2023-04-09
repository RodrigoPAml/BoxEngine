#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {

	/// <summary>
	/// Script Data Type enum to string
	/// </summary>
	static std::string ScriptDataTypeToStringForEditor(ScriptDataType type)
	{
		switch (type)
		{
		case BoxEngine::Project::ScriptDataType::boolean:
			return "boolean";
		case BoxEngine::Project::ScriptDataType::number:
			return "number";
		case BoxEngine::Project::ScriptDataType::string:
			return "string";
		default:
			return "?";
		}
	}

	/// <summary>
	/// Transform enum to string
	/// </summary>
	static std::string ScriptStateToStringForEditor(ScriptState state, bool active)
	{
		switch (state)
		{
			case BoxEngine::Project::ScriptState::ToLoad:
				return "Waiting to load";
			case BoxEngine::Project::ScriptState::ToStart:
				return "Waiting to start";
			case BoxEngine::Project::ScriptState::Updating:
				if (active)
					return "Executing";
				else
					return "Executing (currently disabled)";
			case BoxEngine::Project::ScriptState::ToDestroy:
				return "Waiting to be destroyed";
			case BoxEngine::Project::ScriptState::Destroyed:
				return "Destroyed";
			default:
				return "?";
		}
	}

	/// <summary>
	/// Transform enum to string
	/// </summary>
	static std::string ScriptStateToString(ScriptState state)
	{
		switch (state)
		{
			case BoxEngine::Project::ScriptState::ToLoad:
				return "TO_LOAD";
			case BoxEngine::Project::ScriptState::ToStart:
				return "TO_START";
			case BoxEngine::Project::ScriptState::Updating:
				return "UPDATING";
			case BoxEngine::Project::ScriptState::ToDestroy:
				return "TO_DESTROY";
			case BoxEngine::Project::ScriptState::Destroyed:
				return "DESTROYED";
			default:
				return "?";
		}
	}
}}