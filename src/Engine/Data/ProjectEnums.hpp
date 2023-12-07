#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {

	/// <summary>
	/// Represents an execution type
	/// </summary>
	enum class ExecutionType
	{
		Normal, // Start, Update, Destroy (scripts)
		Destroy, // Destroy (go)
	};

	/// <summary>
	/// Represents the project state.
	/// </summary>
	enum class ProjectState
	{
		Idle, // In editor
		Loading, // Loading Scene, gos, scripts..
		Running, // Running
		Stoping // When deleting everything to stop
	};

	/// <summary>
	/// Represents the project running mode.
	/// </summary>
	enum class ProjectMode
	{
		PlayMode,
		EditorMode
	};

	/// <summary>
	/// Represents the script state.
	/// </summary>
	enum class ScriptState
	{
		ToLoad, // Script needs to be loaded
		ToStart, // Script needs to start
		Updating, // Script is running
		ToDestroy, // Script needs to be destroy
		Destroyed // Script is destroyed
	};

	/// <summary>
	/// Witch type is the script data
	/// </summary>
	enum class ScriptDataType
	{
		boolean = 0,
		number = 1,
		string = 2
	};

	/// <summary>
	/// Run mode for gos
	/// </summary>
	enum class RunMode
	{
		Normal,
		PlayModeDestroyed,
		EditorModeDestroyed,
		PlayModeRemoved,
	};
}}}