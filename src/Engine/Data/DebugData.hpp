#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Debug {

	/// <summary>
	/// Debug configuration.
	/// </summary>
	struct DebugConfiguration
	{
		/// <summary>
		/// Determines if GLFW will generate errors.
		/// </summary>
		bool enableGlfwDebugging = false;

		/// <summary>
		/// Determines if OpenGL will generate errors.
		/// </summary>
		bool enableOpenGLDebugging = false;

		/// <summary>
		/// If errors from GLFW will use the Logging automatically (depends on enableGlfwDebugging = true).
		/// </summary>
		bool autoLogGLFWErrors = false;

		/// <summary>
		/// If errors from OpenGL will use the Logging automatically (depends on enableOpenGLDebugging = true).
		/// </summary>
		bool autoLogOpenGLErrors = false;

		/// <summary>
		/// The severities that should be considered in auto log.
		/// </summary>
		std::set<OpenGlErrorSeverity> openGlSeverities = {
			OpenGlErrorSeverity::SEVERITY_LOW,
			OpenGlErrorSeverity::SEVERITY_MEDIUM,
			OpenGlErrorSeverity::SEVERITY_HIGH,
		};
	};

	/// <summary>
	/// Logging Configuration
	/// </summary>
	struct LoggingConfiguration
	{
		/// <summary>
		/// If logs will be showed in console.
		/// </summary>
		bool logConsole = false;

		/// <summary>
		/// If logs will be saved in log file.
		/// </summary>
		bool logFile = false;

		/// <summary>
		/// If logs will be propagated to callbacks that can be registered.
		/// </summary>
		bool logCallback = true;
	};
}}