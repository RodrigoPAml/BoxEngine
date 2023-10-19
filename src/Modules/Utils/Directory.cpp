#include <BoxEngine.hpp>
#include "Directory.hpp"

namespace BoxEngine {
namespace Modules {
namespace Utils {
namespace Directory {

	using namespace Engine;

	std::string ReadFile(const std::string& path, bool* success)
	{
		std::ifstream file(path);

		if (!file.is_open())
		{
			if(success)
				*success = false;

			return "";
		}

		std::stringstream buffer;

		buffer << file.rdbuf();

		if (success)
			*success = true;

		return buffer.str();
	}

	bool CreateDirectory(const std::string& path)
	{
		if (Exists(path))
			return true;

		return std::filesystem::create_directories(path);
	}

	bool CreateFile(const std::string& path, const std::string& content)
	{
		if (Exists(path))
			return true;

		std::ofstream outfile(path);

		if (!outfile.is_open())
			return false;

		outfile << content << std::endl;
		outfile.close();

		return true;
	}

	bool Move(const std::string& oldPath, const std::string& newPath)
	{
		return rename(oldPath.c_str(), newPath.c_str()) != -1;
	}

	bool Copy(const std::string& oldPath, const std::string& newPath)
	{
		try
		{
			std::filesystem::copy(oldPath, newPath);
			return true;
		}
		catch(std::exception)
		{
			return false;
		}
	}

	bool Delete(const std::string& path, bool deleteNonEmptyFolder)
	{
		if (deleteNonEmptyFolder)
			return std::filesystem::remove_all(path);

		return std::filesystem::remove(path);
	}

	std::string GetResourcePath()
	{
		std::string prodPath = GetCurrentPath() + '/' + "res";

		if (Exists(prodPath))
			return prodPath;

		return GetCurrentPath() + "/../../res"; // development
	}

	std::string GetDocsPath()
	{
		std::string prodPath = GetCurrentPath() + '/' + "docs";

		if (Exists(prodPath))
			return prodPath;

		return GetCurrentPath() + "/../../docs"; // development
	}

	std::string GetLogPath()
	{
		auto project = Project::Project::GetCurrentProject();

		if (project == nullptr)
			return "";

		return project->GetBasePath() + '/';
	}

	#include <Windows.h>
	std::string GetCurrentPath()
	{
		char buffer[MAX_PATH];

		GetModuleFileNameA(NULL, buffer, MAX_PATH);

		return RemovePartsFromPath(std::string(buffer), 1);
	}

	bool IsDirectory(const std::string& path)
	{
		return std::filesystem::is_directory(path);
	}

	bool IsFile(const std::string& path)
	{
		return std::filesystem::is_regular_file(path);
	}

	bool Exists(const std::string& path)
	{
		return std::filesystem::exists(path);
	}

	std::vector<std::string> ListDirectories(const std::string& root, const bool returnOnlyName)
	{
		std::vector<std::string> paths;

		for (auto& it : std::filesystem::directory_iterator(root))
		{
			if (returnOnlyName)
			{
				std::string name = GetLastPartFromPath(it.path().generic_string());

				paths.push_back(name);
			}
			else
				paths.push_back(it.path().generic_string());
		}

		return paths;
	}

	std::string GetLastPartFromPath(const std::string path)
	{
		int size = path.find_last_of('\\');

		if(size == -1)
			size = path.find_last_of('/');

		if (size != -1)
		{
			return path.substr(size + 1);
		}
		else
		{
			return path;
		}
	}

	std::string RemovePartsFromPath(const std::string& path, unsigned int parts)
	{
		if (!path.empty())
		{
			int cut = path.size();

			for (int i = path.size() - 1; i >= 0; i--)
			{
				if (parts == 0) break;

				if (path[i] == '/' || path[i] == '\\')
				{
					cut = i;
					parts--;
				}
			}

			return path.substr(0, cut);
		}

		return path;
	}

	std::string GetExtensionFromPath(const std::string& path)
	{
		std::string file = GetLastPartFromPath(path);

		auto pos = file.find('.');

		if (pos != -1)
			return file.substr(pos+1);

		return file;
	}

	std::string GetLastPartFromPathNoExtension(const std::string& path)
	{
		std::string file = GetLastPartFromPath(path);

		auto pos = file.find('.');

		if (pos != -1)
			return file.substr(0, pos);

		return file;
	}

	std::string NewGuid()
	{
		GUID guid;
		HRESULT hCreateGuid = CoCreateGuid(&guid);

		std::ostringstream os;
		os.width(8);
		os << std::hex << std::setfill('0') << guid.Data1 << '-';
		os.width(4);
		os << std::hex << std::setfill('0') << guid.Data2 << '-';
		os.width(4);
		os << std::hex << std::setfill('0') << guid.Data3 << '-';
		os.width(2);
		os << std::hex << std::setfill('0') << std::setw(2)
		   << static_cast<short>(guid.Data4[0]) << std::setw(2)
		   << static_cast<short>(guid.Data4[1]) << '-' << std::setw(2)
		   << static_cast<short>(guid.Data4[2]) << std::setw(2)
		   << static_cast<short>(guid.Data4[3]) << std::setw(2)
		   << static_cast<short>(guid.Data4[4]) << std::setw(2)
		   << static_cast<short>(guid.Data4[5]) << std::setw(2)
		   << static_cast<short>(guid.Data4[6]) << std::setw(2)
		   << static_cast<short>(guid.Data4[7]);

		return os.str();
	}

	void OpenExplorer(std::string path)
	{
		std::replace(path.begin(), path.end(), '/', '\\');

		system(("explorer " + path).c_str());
	}

	void Execute(std::string command)
	{
		std::replace(command.begin(), command.end(), '/', '\\');

		system(command.c_str());
	}

	void CopyClipboard(std::string content)
	{
		OpenClipboard(GetDesktopWindow());
		EmptyClipboard();
		HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, content.size() + 1);

		if (!hg) 
		{
			CloseClipboard();
			return;
		}

		memcpy(GlobalLock(hg), content.c_str(), content.size() + 1);
		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT, hg);
		CloseClipboard();
		GlobalFree(hg);
	}
}}}}
