#include <BoxEngine.hpp>
#include "Logging.hpp"

namespace BoxEngine {
namespace Modules {
namespace Debug {

	LoggingConfiguration Logging::GetConfiguration()
	{
		return Instance().config;
	}

	void Logging::SetConfiguration(const LoggingConfiguration& config)
	{
		Instance().config = config;
	}

	void Logging::RegisterLogCallback(const std::string& identifier, LogCallback callback)
	{
		if(callback != nullptr)
			Instance().callbacks[identifier] = callback;
	}

	void Logging::RemoveLogCallback(const std::string& identifier)
	{
		auto& instance = Instance();

		if(instance.callbacks.contains(identifier))
			instance.callbacks.erase(identifier);
	}

	void Logging::Log(
		const std::string& content,
		const LogSeverity severity,
		const LogOrigin origin,
		const std::unordered_map<std::string, std::string>& additionalData,
		const std::source_location& location
	)
	{
		auto& instance = Instance();
		
		if (instance.config.logConsole || instance.config.logFile)
		{
			std::string contentId = {
				Utils::Time::GetDateTime().ToStringDateTime() + "|" +
				location.file_name() + "|" +
				location.function_name() + ':' + std::to_string(location.line()) + "|" +
				LogOriginToString(origin) + "|" +
				LogSeverityToString(severity) + "|"
			};

			for (auto& item : additionalData)
				contentId += item.first + ":" + item.second + ",";

			if (instance.config.logConsole)
				std::cout << contentId << content << '\n';

			if (instance.config.logFile && instance.file.is_open())
			{
				instance.file << contentId << content << '\n';
				instance.file.flush();
			}
		}

		if(instance.config.logCallback)
			for(auto callback : instance.callbacks)
				callback.second(
					Utils::Time::GetDateTime(), 
					content, 
					severity, 
					origin,
					additionalData,
					location.function_name() + ':' + std::to_string(location.line()), 
					location.file_name()
				);
	}

	void Logging::LogException(
		const std::string& content, 
		const LogOrigin origin,
		const std::unordered_map<std::string, std::string>& additionalData,
		const std::source_location& location
	)
	{
		Log(content, LogSeverity::Error, origin, additionalData, location);

		throw std::runtime_error(content.c_str());
	}

	Logging& Logging::Instance()
	{
		static Logging* instance = new Logging();

		return *instance;
	}

	void Logging::Init(const LoggingConfiguration& logConfig)
	{
		this->config = logConfig;

		if(logConfig.logFile)
		{
			std::string filename = Utils::Time::GetDateTime().ToFileNameDateTime() + ".csv";

			Utils::Directory::CreateDirectory(Utils::Directory::GetLogPath() + "logs");

			this->file = std::ofstream((Utils::Directory::GetLogPath() + "logs/" + filename).c_str());
		}

		Log("[Logging]: Initialized", LogSeverity::Notify, LogOrigin::Engine);
	}

	void Logging::Release()
	{
		this->callbacks.clear();

		Log("[Logging]: Released", LogSeverity::Notify, LogOrigin::Engine);

		if(this->file.is_open())
			this->file.close();

		this->config = LoggingConfiguration();
	}
}}}