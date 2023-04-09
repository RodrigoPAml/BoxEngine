#include <BoxEngine.hpp>
#include "Debugging.hpp"

namespace BoxEngine { 
namespace Debug {

	DebugConfiguration Debugging::GetConfiguration()
	{
		return Instance().config;
	}

	void Debugging::SetConfiguration(const DebugConfiguration& config)
	{
		Instance().config = config;
	}

	GLFWError Debugging::GetGLFWError(std::string& errorMsg)
	{
		const char* description;

		GLFWError error = (GLFWError)glfwGetError(&description);

		if(description)
			errorMsg = description;

		return error;
	}

	OpenGlError Debugging::GetOpenGlError()
	{
		return (OpenGlError)glGetError();
	}

	void Debugging::RegisterGLFWErrorCallbac(const std::string& identifier, GLFWErrorCallback callback)
	{
		if(callback != nullptr)
			Instance().glfwCallbacks[identifier] = callback;
	}

	void Debugging::RegisterOpenGlErrorCallback(const std::string& identifier, OpenGlErrorCallback callback)
	{
		if(callback != nullptr)
			Instance().openGlCallbacks[identifier] = callback;
	}

	void Debugging::RemoveGLFWErrorCallback(const std::string& identifier)
	{
		auto& instance = Instance();

		if(instance.glfwCallbacks.contains(identifier))
			instance.glfwCallbacks.erase(identifier);
	}

	void Debugging::RemoveOpenGlErrorCallback(const std::string& identifier)
	{
		auto& instance = Instance();

		if(instance.openGlCallbacks.contains(identifier))
			instance.openGlCallbacks.erase(identifier);
	}

	Debugging& Debugging::Instance()
	{
		static Debugging* instance = new Debugging();

		return *instance;
	}

	void Debugging::Release()
	{
		this->glfwCallbacks.clear();
		this->openGlCallbacks.clear();
		this->config = DebugConfiguration();
	}

	void Debugging::GLFW_ERROR_CALLBACK(int code, const char* description)
	{
		auto& instance = Instance();

		if(instance.config.autoLogGLFWErrors)
		{
			std::ostringstream stream;

			stream << ErrorToString((GLFWError)code) + " - " << description;

			Logging::Log(stream.str(), LogSeverity::Error, LogOrigin::GLFW);
		}

		for(auto callback : instance.glfwCallbacks)
			callback.second((GLFWError)code, description);
	}

	void GLAPIENTRY Debugging::OPENGL_ERROR_CALLBACK(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		auto& instance = Instance();
			
		if(instance.config.autoLogOpenGLErrors)
		{
			OpenGlErrorSeverity severityEnum = (OpenGlErrorSeverity)severity;

			if(instance.config.openGlSeverities.find(severityEnum) != instance.config.openGlSeverities.end())
			{
				std::ostringstream stream;

				stream << ErrorToString((OpenGlErrorType)type) << '|'
						<< ErrorToString((OpenGlErrorSource)source) << '|'
						<< ErrorToString(severityEnum) << '|'
						<< message;

				switch(severityEnum)
				{
					case OpenGlErrorSeverity::SEVERITY_HIGH:
						Logging::Log(stream.str(), LogSeverity::Error, LogOrigin::OpenGL);
						break;
					case OpenGlErrorSeverity::SEVERITY_MEDIUM:
						Logging::Log(stream.str(), LogSeverity::Warning, LogOrigin::OpenGL);
						break;
					case OpenGlErrorSeverity::SEVERITY_LOW:
						Logging::Log(stream.str(), LogSeverity::Warning, LogOrigin::OpenGL);
						break;
					case OpenGlErrorSeverity::SEVERITY_NOTIFICATION:
						Logging::Log(stream.str(), LogSeverity::Notify, LogOrigin::OpenGL);
						break;
					default:
						break;
				}
			}
		}

		for(auto callback : instance.openGlCallbacks)
			callback.second((OpenGlErrorType)type, (OpenGlErrorSource)source, (OpenGlErrorSeverity)severity, message);
	}
}}