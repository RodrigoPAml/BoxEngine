#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	using namespace Engine;

	/// <summary>
	/// Represents the file manager tab in bottom window.
	/// </summary>
	class FilesTab : public Layout
	{
	private:
		bool shouldUpdate = true;

		std::string basePath;
		std::string guid = "";
		std::string filter = "";
		std::string inputRename = "";
		std::string inputCreateFile = "";
		std::string inputCreateFolder = "";

		TreeItem popUpItem;

		bool openPopUp = false;
		bool isCut = false;
		float fontScale = 1.0f;
		std::string toCopy = "";
		
		std::vector<TreeItem> tree;
	public:
		FilesTab() = default;
		~FilesTab() = default;

		void Start();
		void Update();
	private:
		void UpdateTree();
		bool UpdateTree(TreeItem& father);

		void DrawTree(const TreeItem& father);
		void DrawPopUps();
		std::string GetScriptFile(const std::string& name);
	};
}}