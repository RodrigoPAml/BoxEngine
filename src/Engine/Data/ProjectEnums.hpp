#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {

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
	/// With type is the script data
	/// </summary>
	enum class ScriptDataType
	{
		boolean = 0,
		number = 1,
		string = 2
	};
}}