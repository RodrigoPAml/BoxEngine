#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {
	
	using namespace Modules;

	/// <summary>
	/// Represents an item of the tree of files of project
	/// </summary>
	struct TreeItem
	{
		std::string path = "";

		std::string name = "";

		std::vector<TreeItem> childs;

		bool filtered = false;

		bool isDir = false;

		bool isRoot = false;
	};

	/// <summary>
	/// Represents an item of the list in the logs of project
	/// </summary>
	struct LogTabItem
	{
		std::string message;

		Debug::LogSeverity severity;
		
		Debug::LogOrigin origin;

		LogTabItem(const std::string& message, Debug::LogSeverity severity, Debug::LogOrigin origin)
		{
			this->message = message;
			this->severity = severity;
			this->origin = origin;
		}
	};
}}