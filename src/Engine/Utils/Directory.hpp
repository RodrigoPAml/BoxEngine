#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Utils {
namespace Directory {

	/// <summary>
	/// Read file into string.
	/// </summary>
	std::string ReadFile(const std::string& file, bool* success = nullptr);

	/// <summary>
	/// Create directories provided by string.
	/// </summary>
	bool CreateDirectory(const std::string& path);

	/// <summary>
	/// Create file and write string content into it.
	/// </summary>
	bool CreateFile(const std::string& path, const std::string& content);

	/// <summary>
	/// Move path or folder to another location.
	/// </summary>
	bool Move(const std::string& oldPath, const std::string& newPath);

	/// <summary>
	/// Copy path or folder to another location.
	/// </summary>
	bool Copy(const std::string& oldPath, const std::string& newPath);

	/// <summary>
	/// Delete file or folder.
	/// </summary>
	/// <param name="deleteNonEmptyFolder"> If true, non empty folder will be deleted any way </param>
	bool Delete(const std::string& path, bool deleteNonEmptyFolder = false);

	/// <summary>
	/// Get the resource folder;
	/// </summary>
	std::string GetResourcePath();

	/// <summary>
	/// Get the documents folder;
	/// </summary>
	std::string GetDocsPath();

	/// <summary>
	/// Get the log path;
	/// </summary>
	std::string GetLogPath();

	/// <summary>
	/// Get .exe current path.
	/// </summary>
	std::string GetCurrentPath();

	/// <summary>
	/// Check if give path is a directory.
	/// </summary>
	bool IsDirectory(const std::string& path);

	/// <summary>
	/// Check if give path is a file.
	/// </summary>
	bool IsFile(const std::string& path);

	/// <summary>
	/// Check if file or folder exists.
	/// </summary>
	bool Exists(const std::string& path);

	/// <summary>
	/// List files in path provided by string.
	/// </summary>
	/// <param name="returnOnlyName"> if only files/folders should be returned </param>
	std::vector<std::string> ListDirectories(const std::string& root, const bool returnOnlyName = true);

	/// <summary>
	/// Return last name from path.
	/// </summary>
	/// <param name="path"></param>
	std::string GetLastPartFromPath(const std::string path);

	/// <summary>
	/// Remove parts of provided path.
	/// </summary>
	std::string RemovePartsFromPath(const std::string& path, unsigned int n = 0);

	/// <summary>
	/// Get extesion if path provided is a file.
	/// </summary>
	std::string GetExtensionFromPath(const std::string& path);

	/// <summary>
	/// Get filename from path without extension.
	/// </summary>
	std::string GetLastPartFromPathNoExtension(const std::string& path);

	/// <summary>
	/// Get new GUID.
	/// </summary>
	std::string NewGuid();

	/// <summary>
	/// Open explorer of system in particular path.
	/// </summary>
	/// <param name="path"></param>
	void OpenExplorer(std::string path);

	/// <summary>
	/// Execute a comand in cmd.
	/// </summary>
	/// <param name="path"></param>
	void Execute(std::string command);

	/// <summary>
	/// Copy to text to clipboard
	/// </summary>
	/// <param name="content"></param>
	void CopyClipboard(std::string content);
}}}