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
	static std::string ScriptStateToStringForEditor(ScriptState state, bool active)
	{
		switch (state)
		{
			case ScriptState::ToLoad:
				return "Waiting to load";
			case ScriptState::ToStart:
				return "Waiting to start";
			case ScriptState::Updating:
				if (active)
					return "Executing";
				else
					return "Executing (currently disabled)";
			case ScriptState::ToDestroy:
				return "Waiting to be destroyed";
			case ScriptState::Destroyed:
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
}}}