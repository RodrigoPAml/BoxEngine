#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Debug {

	/// <summary>
	/// Allows to get errors from GLFW and OpenGL.
	/// Also allows to convert errors enums to string.
	/// This class is a singleton.
	/// </summary>
	class Debugging
	{
	private:
		/// <summary>
		/// Callbacks for user recieve errors of GLFW.
		/// </summary>
		std::map<std::string, GLFWErrorCallback> glfwCallbacks;

		/// <summary>
		/// Callbacks for user recieve errors of GLFW.
		/// </summary>
		std::map<std::string, OpenGlErrorCallback> openGlCallbacks;

		/// <summary>
		/// The current debugging configuration;
		/// </summary>
		DebugConfiguration config;
	public:
		/// <summary>
		/// Returns the configuration.
		/// </summary>
		/// <returns></returns>
		static DebugConfiguration GetConfiguration();
			
		/// <summary>
		/// Sets the configuration.
		/// </summary>
		/// <param name="config"></param>
		static void SetConfiguration(const DebugConfiguration& config);

		/// <summary>
		/// Get if there is an GLFW error at runtime.
		/// </summary>
		static GLFWError GetGLFWError(std::string& errorMsg);

		/// <summary>
		/// Get if there is an OpenGL error at runtime.
		/// </summary>
		static OpenGlError GetOpenGlError();

		/// <summary>
		/// Register callbacks to recieve errors or warnings from openGL
		/// </summary>
		static void RegisterGLFWErrorCallbac(const std::string& identifier, GLFWErrorCallback callback);
				
		/// <summary>
		/// Register callbacks to recieve errors or warnings from openGL
		/// </summary>
		static void RegisterOpenGlErrorCallback(const std::string& identifier, OpenGlErrorCallback callback);

		// Callback removing
		static void RemoveGLFWErrorCallback(const std::string& identifier);
		static void RemoveOpenGlErrorCallback(const std::string& identifier);
	private:
		Debugging() {};
		Debugging(Debugging const&);
	
	public:
		/// <summary>
		/// Returns current instance.
		/// </summary>
		static Debugging& Instance();

		/// <summary>
		/// Release data, like registered callbacks.
		/// </summary>
		void Release();

		/// <summary>
		/// Callbacks to recieve errors of GLFW.
		/// </summary>
		static void GLFW_ERROR_CALLBACK(int code, const char* description);

		/// <summary>
		/// Callbacks to recieve errors of OpenGL.
		/// Internal usage.
		/// </summary>
		static void GLAPIENTRY OPENGL_ERROR_CALLBACK(
			GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam
		);
	};
}}