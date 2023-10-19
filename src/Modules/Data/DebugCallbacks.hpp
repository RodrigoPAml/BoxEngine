#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Debug {

	/// <summary>
	/// Callback to recieve logs
	/// </summary>
	typedef std::function<void(
		const Utils::DateTime&,
		const std::string&,
		const LogSeverity,
		const LogOrigin,
		const std::unordered_map<std::string, std::string>&,
		const std::string&, 
		const std::string&)> 
	LogCallback;

	/// <summary>
	/// GLFW Callback to recieve errors events
	/// </summary>
	typedef std::function<void(const GLFWError, const std::string&)> GLFWErrorCallback;

	/// <summary>
	/// OpenGL Callback to recieve errors events
	/// </summary>
	typedef std::function<void(const OpenGlErrorType, const OpenGlErrorSource, const OpenGlErrorSeverity, const std::string&)> OpenGlErrorCallback;
}}}