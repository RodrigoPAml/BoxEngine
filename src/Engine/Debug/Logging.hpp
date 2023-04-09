#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Debug {

	/// <summary>
	/// Used to logs events of the program.
	/// Allows to log events of openGL, GLFW and user provided.
	/// This class is a Singleton.
	/// </summary>
	class Logging
	{
		friend class BoxEngine::Window::Window;
	private:
		/// <summary>
		/// File to output log.
		/// </summary>
		std::ofstream file;

		/// <summary>
		/// The current logging configuration;
		/// </summary>
		LoggingConfiguration config;

		/// <summary>
		/// Callbacks for user recieve generated logs.
		/// </summary>
		std::map<std::string, LogCallback> callbacks;
	public:
		/// <summary>
		/// Returns the configuration.
		/// </summary>
		/// <returns></returns>
		static LoggingConfiguration GetConfiguration();

		/// <summary>
		/// Sets the configuration.
		/// </summary>
		/// <param name="config"></param>
		static void SetConfiguration(const LoggingConfiguration& config);

		/// <summary>
		/// Register and remove callbacks to recieve logs.
		/// </summary>
		static void RegisterLogCallback(const std::string& identifier, LogCallback callback);
		static void RemoveLogCallback(const std::string& identifier);

		/// <summary>
		/// Internal Log.
		/// </summary>
		static void Log(
			const std::string& content,
			const LogSeverity severity,
			const LogOrigin origin,
			const std::unordered_map<std::string, std::string>& additionalData = std::unordered_map<std::string, std::string>(),
			const std::source_location& location = std::source_location::current()
		);

		/// <summary>
		/// Internal log and throw exception.
		/// </summary>
		static void LogException(
			const std::string& content,
			const LogOrigin origin,
			const std::unordered_map<std::string, std::string>& additionalData = std::unordered_map<std::string, std::string>(),
			const std::source_location& location = std::source_location::current()
		);
	private:
		Logging() {};
		Logging(Logging const&);

		/// <summary>
		/// Returns current instance.
		/// </summary>
		/// <returns></returns>
		static Logging& Instance();

		/// <summary>
		/// Set configuration.
		/// Used from Window Context initialization.
		/// </summary>
		void Init(const LoggingConfiguration& logConfig);

		/// <summary>
		/// Release resources, like closing the log file.
		/// </summary>
		void Release();
	};
}}