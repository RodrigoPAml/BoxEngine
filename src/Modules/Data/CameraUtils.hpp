#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine { 
namespace Modules {
namespace Camera
{
	/// <summary>
	/// Get Camera movement from from string
	/// </summary>
	static CameraMovement GetCameraMovementFromString(std::string key)
	{
		if (key == "BACKWARD")
			return CameraMovement::BACKWARD;
		else if (key == "DOWN")
			return CameraMovement::DOWN;
		else if (key == "FORWARD")
			return CameraMovement::FORWARD;
		else if (key == "LEFT")
			return CameraMovement::LEFT;
		else if (key == "RIGHT")
			return CameraMovement::RIGHT;
		else if (key == "UP")
			return CameraMovement::UP;

		Debug::Logging::Log(
			"Failed to map CameraMovement with value " + key + " instead the default value FORWARD will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return CameraMovement::FORWARD;
	}
}}}