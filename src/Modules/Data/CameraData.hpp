#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine { 
namespace Modules { 
namespace Camera
{
	/// <summary>
	/// Represents initial configuration of a 3D Camera.
	/// </summary>
	struct CameraConfiguration
	{
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

		float yaw = 0.0f, pitch = 0.0f, fov = 70.0f, aspectRatio = 16.0f / 9.0f, zFar = 1000.0f, zNear = 0.1f;
	};
}}}