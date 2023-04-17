#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {

	/// <summary>
	/// Stores project multiple data information
	/// </summary>
	struct ProjectData
	{
		/// <summary>
		/// Current FPS
		/// </summary>
		double fps = 0;

		/// <summary>
		/// Current FPS
		/// </summary>
		double fpsCounter = 0;

		/// <summary>
		/// Controller for fps
		/// </summary>
		double currentTime = 0;

		/// <summary>
		/// Current freamtime
		/// </summary>
		double frameTime = 0;

		/// <summary>
		/// Controller for frame time
		/// </summary>
		double lastFrameTime = 0;

		/// <summary>
		/// Start coordinates to draw (top left)
		/// </summary>
		glm::vec2 topLeft;

		/// <summary>
		/// End coordinates to draw (bottom right)
		/// </summary>
		glm::vec2 bottomRight;

		/// <summary>
		/// The project current framebuffer
		/// </summary>
		GPU::FramebufferWeakPtr current;

		/// <summary>
		/// Store all the requested go movements
		/// </summary>
		std::vector<GoMovement> frameMovements;
	};
}}