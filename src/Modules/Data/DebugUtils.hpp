#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Debug {

	static std::string ErrorToString(const OpenGlError value)
	{
		switch (value)
		{
			case OpenGlError::NO_ERROR:
				return "NO_ERROR";
			case OpenGlError::INVALID_ENUM:
				return "INVALID_ENUM";
			case OpenGlError::INVALID_VALUE:
				return "INVALID_VALUE";
			case OpenGlError::INVALID_OPERATION:
				return "INVALID_OPERATION";
			case OpenGlError::STACK_OVERFLOW:
				return "STACK_OVERFLOW";
			case OpenGlError::STACK_UNDERFLOW:
				return "STACK_UNDERFLOW";
			case OpenGlError::OUT_OF_MEMORY:
				return "OUT_OF_MEMORY";
			case OpenGlError::INVALID_FRAMEBUFFER_OPERATION:
				return "INVALID_FRAMEBUFFER_OPERATION";
			default:
				return "?";
		}
	}

	static std::string ErrorToString(const GLFWError value)
	{
		switch (value)
		{
			case GLFWError::NO_ERROR:
				return "NO_ERROR";
			case GLFWError::API_UNAVAILABLE:
				return "API_UNAVAILABLE";
			case GLFWError::FORMAT_UNAVAILABLE:
				return "FORMAT_UNAVAILABLE";
			case GLFWError::INVALID_ENUM:
				return "INVALID_ENUM";
			case GLFWError::INVALID_VALUE:
				return "INVALID_VALUE";
			case GLFWError::NO_CURRENT_CONTEXT:
				return "NO_CURRENT_CONTEXT";
			case GLFWError::NOT_INITIALIZED:
				return "NOT_INITIALIZED";
			case GLFWError::OUT_OF_MEMORY:
				return "OUT_OF_MEMORY";
			case GLFWError::PLATFORM_ERROR:
				return "PLATFORM_ERROR";
			case GLFWError::VERSION_UNAVAILABLE:
				return "VERSION_UNAVAILABLE";
			default:
				return "?";
		}
	}

	static std::string ErrorToString(const OpenGlErrorSource value)
	{
		switch (value)
		{
			case OpenGlErrorSource::SOURCE_API:
				return "SOURCE_API";
			case OpenGlErrorSource::SOURCE_WINDOW_SYSTEM:
				return "SOURCE_WINDOW_SYSTEM";
			case OpenGlErrorSource::SOURCE_SHADER_COMPILER:
				return "SOURCE_SHADER_COMPILER";
			case OpenGlErrorSource::SOURCE_THIRD_PARTY:
				return "SOURCE_THIRD_PARTY";
			case OpenGlErrorSource::SOURCE_APPLICATION:
				return "SOURCE_APPLICATION";
			case OpenGlErrorSource::SOURCE_OTHER:
				return "SOURCE_OTHER";
			default:
				return "?";
		}
	}

	static std::string ErrorToString(const OpenGlErrorType value)
	{
		switch (value)
		{
			case OpenGlErrorType::TYPE_ERROR:
				return "TYPE_ERROR";
			case OpenGlErrorType::TYPE_DEPRECATED_BEHAVIOR:
				return "TYPE_DEPRECATED_BEHAVIOR";
			case OpenGlErrorType::TYPE_UNDEFINED_BEHAVIOR:
				return "TYPE_UNDEFINED_BEHAVIOR";
			case OpenGlErrorType::TYPE_PORTABILITY:
				return "TYPE_PORTABILITY";
			case OpenGlErrorType::TYPE_PERFORMANCE:
				return "TYPE_PERFORMANCE";
			case OpenGlErrorType::TYPE_MARKER:
				return "TYPE_MARKER";
			case OpenGlErrorType::TYPE_PUSH_GROUP:
				return "TYPE_PUSH_GROUP";
			case OpenGlErrorType::TYPE_POP_GROUP:
				return "TYPE_POP_GROUP";
			case OpenGlErrorType::TYPE_OTHER:
				return "TYPE_OTHER";
			default:
				return "?";
		}
	}

	static std::string ErrorToString(const OpenGlErrorSeverity value)
	{
		switch (value)
		{
			case OpenGlErrorSeverity::SEVERITY_HIGH:
				return "SEVERITY_HIGH";
			case OpenGlErrorSeverity::SEVERITY_MEDIUM:
				return "SEVERITY_MEDIUM";
			case OpenGlErrorSeverity::SEVERITY_LOW:
				return "SEVERITY_LOW";
			case OpenGlErrorSeverity::SEVERITY_NOTIFICATION:
				return "SEVERITY_NOTIFICATION";
			default:
				return "?";
		}
	}

	static std::string LogOriginToString(const LogOrigin value)
	{
		switch (value)
		{
			case LogOrigin::Engine:
				return "Engine";
			case LogOrigin::GLFW:
				return "GLFW";
			case LogOrigin::OpenGL:
				return "OpenGL";
			case LogOrigin::UserGenerated:
				return "UserGenerated";
			case LogOrigin::EngineInternal:
				return "Engine Internal";
			default:
				return "?";
		}
	}

	static std::string LogSeverityToString(const LogSeverity value)
	{
		switch (value)
		{
			case LogSeverity::Error:
				return "Error";
			case LogSeverity::Notify:
				return "Notify";
			case LogSeverity::Warning:
				return "Warning";
			default:
				return "?";
		}
	}
}}}