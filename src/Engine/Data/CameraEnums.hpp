#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine { 
namespace Camera
{
	/// <summary>
	/// Represents the direction of the movement of a camera.
	/// </summary>
	enum class CameraMovement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};
}}