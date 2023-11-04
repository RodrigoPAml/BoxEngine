#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {

	/// <summary>
	/// Script Data Type enum to string
	/// </summary>
	static std::string ScriptDataTypeToStringForEditor(ScriptDataType type)
	{
		switch (type)
		{
		case ScriptDataType::boolean:
			return "boolean";
		case ScriptDataType::number:
			return "number";
		case ScriptDataType::string:
			return "string";
		default:
			return "?";
		}
	}

	/// <summary>
	/// Transform enum to string
	/// </summary>
	static std::string ScriptStateToStringForEditor(ScriptState state, bool active, RunMode mode, ProjectMode projectMode)
	{
		std::string result = "";

		switch (state)
		{
			case ScriptState::ToLoad:
				result = "Waiting to load";
				break;
			case ScriptState::ToStart:
				result = "Waiting to start";
				break;
			case ScriptState::Updating:
				result = "Executing";
				break;
			case ScriptState::ToDestroy:
				result = "Waiting to be destroyed";
				break;
			case ScriptState::Destroyed:
				result = "Destroyed";
				break;
			default:
				result = "?";
				break;
		}

		if (mode == RunMode::PlayModeDestroyed && projectMode == ProjectMode::PlayMode)
			result += " (Ignored by run mode)";
		else if (mode == RunMode::EditorModeDestroyed && projectMode == ProjectMode::EditorMode)
			result += " (Ignored by run mode)";
		else if (mode == RunMode::PlayModeRemoved && projectMode == ProjectMode::PlayMode)
			result += " (Ignored by run mode)";
		else if (!active)
			result += " (currently disabled)";

		return result;
	}

	/// <summary>
	/// Transform enum to string
	/// </summary>
	static std::string GoStateToStringForEditor(bool active, RunMode mode, ProjectMode projectMode)
	{
		std::string result = "";
	
		if (mode == RunMode::PlayModeDestroyed && projectMode == ProjectMode::PlayMode)
			result += "Ignored by run mode";
		else if (mode == RunMode::EditorModeDestroyed && projectMode == ProjectMode::EditorMode)
			result += "Ignored by run mode";
		else if (mode == RunMode::PlayModeRemoved && projectMode == ProjectMode::PlayMode)
			result += "Ignored by run mode";
		else if (active)
			result = "Normal";
		else if (!active)
			result += "Currently disabled";
		
		return result;
	}

	/// <summary>
	/// Transform enum to string
	/// </summary>
	static std::string ScriptStateToString(ScriptState state)
	{
		switch (state)
		{
			case ScriptState::ToLoad:
				return "TO_LOAD";
			case ScriptState::ToStart:
				return "TO_START";
			case ScriptState::Updating:
				return "UPDATING";
			case ScriptState::ToDestroy:
				return "TO_DESTROY";
			case ScriptState::Destroyed:
				return "DESTROYED";
			default:
				return "?";
		}
	}

	/// <summary>
	/// Transform enum to string
	/// </summary>
	static std::string ProjectModeToString(ProjectMode mode)
	{
		switch (mode)
		{
			case ProjectMode::EditorMode:
				return "EDITOR";
			case ProjectMode::PlayMode:
				return "PLAY";
			default:
				return "?";
		}
	}

	/// <summary>
	/// Transform enum to string
	/// </summary>
	static std::string RunModeToString(RunMode mode)
	{
		switch (mode)
		{
			case RunMode::Normal:
				return "Normal";
			case RunMode::EditorModeDestroyed:
				return "Ignored on Editor Mode";
			case RunMode::PlayModeDestroyed:
				return "Ignored on Play Mode";
			case RunMode::PlayModeRemoved:
				return "Removed on Play mode";
			default:
				return "?";
		}
	}
}}}