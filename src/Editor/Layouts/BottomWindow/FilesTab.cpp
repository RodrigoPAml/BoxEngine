#include <BoxEngine.hpp>
#include "FilesTab.hpp"

namespace BoxEngine {
namespace Editor {

	void FilesTab::Start()
	{
		using Project = BoxEngine::Project::Project;

		this->basePath = Project::GetCurrentProject()->GetBasePath();
		this->guid = Utils::Directory::NewGuid();
		this->filter = "";
	}

	void FilesTab::Update()
	{
		using GUI = BoxEngine::Window::GUI;

		if (this->shouldUpdate)
		{
			this->UpdateTree();
			this->shouldUpdate = false;
		}

		GUI::Text("Search: ");
		GUI::ContinueSameLine();
		
		if (GUI::Input(this->guid + "filter", this->filter))
			this->shouldUpdate = true;

		GUI::ContinueSameLine();
		if (GUI::ImageButton(this->guid + "refresh", GUI::GetIcon("refresh.png")))
		{
			this->UpdateTree();
			this->filter = "";
			this->toCopy = "";
		}

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Refresh files");
			GUI::EndHintWindow();
		}

		GUI::Separator();

		this->DrawTree(this->tree[0]);

		this->DrawPopUps();
	}

	void FilesTab::UpdateTree()
	{
		using GUI = BoxEngine::Window::GUI;
		using namespace Window;

		this->tree.clear();

		TreeItem father;
		father.path = this->basePath;
		this->tree.push_back(father);

		this->UpdateTree(this->tree[0]);
	}

	bool FilesTab::UpdateTree(TreeItem& father)
	{
		using GUI = BoxEngine::Window::GUI;
		using namespace Window;

		bool isFiltered = true;

		for (const std::string& path : Utils::Directory::ListDirectories(father.path, false))
		{
			TreeItem child;

			child.name = Utils::Directory::GetLastPartFromPath(path);
			child.isDir = Utils::Directory::IsDirectory(path);
			child.path = path;
			child.isRoot = father.path == this->basePath;

			if (child.isDir)
				child.filtered = this->UpdateTree(child) && this->filter != "";
			else
				child.filtered = this->filter != "" && child.name.find(this->filter) == -1;

			if (!child.filtered)
				isFiltered = false;

			father.childs.push_back(child);
		}

		return isFiltered;
	}

	void FilesTab::DrawTree(const TreeItem& father)
	{
		using GUI = BoxEngine::Window::GUI;
		using namespace Window;

		if (father.filtered)
			return;

		for (const TreeItem& child : father.childs)
		{
			if (child.filtered)
				continue;

			bool nodeOpen = GUI::BeginTreeNode(
				this->guid + "tree_item" + child.name, 
				"##", 
				{ child.isDir ? GUITreeFlags::OpenOnArrow : GUITreeFlags::Bullet }
			);

			GUI::ContinueSameLine(10);
			GUI::Image(GUI::GetIconForPath(child.path), { GUI::GetFontSize(), GUI::GetFontSize() });
			GUI::ContinueSameLine();

			GUI::Selectable(this->guid + "file_item" + child.name, child.name);
			if (GUI::IsCurrentItemClickedRight())
			{
				this->popUpItem = child;
				this->openPopUp = true;
			}

			if (!child.isRoot && GUI::BeginSourceDragDrop())
			{
				this->popUpItem = child;
				GUI::SetDragDropData("file_item", (void*)(&this->guid), sizeof(void*));
				GUI::Image(GUI::GetIconForPath(child.path), { GUI::GetFontSize(), GUI::GetFontSize() });
				GUI::ContinueSameLine();
				GUI::Text(child.name);
				GUI::EndSourceDragDrop();
			}

			if (child.isDir && GUI::BeginDestinyDragDrop())
			{
				this->shouldUpdate = true;

				if (this->popUpItem.path != child.path)
				{
					if (GUI::GetDragDropData("file_item") != nullptr)
					{
						std::string newPath = child.path + '/' + Utils::Directory::GetLastPartFromPath(this->popUpItem.path);
						Utils::Directory::Move(this->popUpItem.path, newPath);
					}
				}

				GUI::EndDestinyDragDrop();
			}

			if (nodeOpen)
			{
				if (child.isDir)
					this->DrawTree(child);

				GUI::EndTreeNode();
			}
		}
	}

	void FilesTab::DrawPopUps()
	{
		using GUI = BoxEngine::Window::GUI;
		using namespace Window;

		if (this->openPopUp)
		{
			GUI::OpenPopUp(this->guid + "popup");
			this->inputRename = Utils::Directory::GetLastPartFromPath(this->popUpItem.path);
			this->inputCreateFolder = "";
			this->inputCreateFile = "";
			this->openPopUp = false;
		}

		if (GUI::BeginPopUp(this->guid + "popup"))
		{
			if (GUI::Selectable(this->guid + "open_explorer", "Open in explorer"))
			{
				std::string path = this->popUpItem.isDir 
					? this->popUpItem.path 
					: Utils::Directory::RemovePartsFromPath(this->popUpItem.path, 1);

				Utils::Directory::OpenExplorer(path);
			}

			if (!this->popUpItem.isDir && GUI::Selectable(this->guid + "open_vscode", "Open in VS CODE"))
				Utils::Directory::Execute("code \"" + this->popUpItem.path + "\"");

			if (this->popUpItem.isDir && GUI::BeginMenu("Create folder"))
			{
				GUI::Input(this->guid + "create_folder", this->inputCreateFolder);
				GUI::ContinueSameLine();

				if (GUI::Button("Create"))
				{
					std::string newFolder = this->popUpItem.path + '/' + this->inputCreateFolder;

					if (Utils::Directory::Exists(newFolder))
						GUI::CloseCurrentPopUp();

					Utils::Directory::CreateDirectory(newFolder);
					this->shouldUpdate = true;
					GUI::CloseCurrentPopUp();
				}

				GUI::EndMenu();
			}

			if (this->popUpItem.isDir && GUI::BeginMenu("Create file"))
			{
				GUI::Input(this->guid + "create_file", this->inputCreateFile);
				GUI::ContinueSameLine();

				if (GUI::Button("Create"))
				{
					std::string newFile = this->popUpItem.path + '/' + this->inputCreateFile;

					if (Utils::Directory::Exists(newFile))
					{
						GUI::CloseCurrentPopUp();
					}
					else if (!newFile.ends_with(".lua"))
						Utils::Directory::CreateFile(newFile, "");
					else
						Utils::Directory::CreateFile(newFile, this->GetScriptFile(Utils::Directory::GetLastPartFromPathNoExtension(newFile)));

					this->shouldUpdate = true;
					GUI::CloseCurrentPopUp();
				}

				GUI::EndMenu();
			}

			if (!this->popUpItem.isRoot && GUI::BeginMenu("Rename") && Utils::Directory::Exists(this->popUpItem.path))
			{
				std::string basePath = Utils::Directory::RemovePartsFromPath(this->popUpItem.path, 1);

				GUI::Input(this->guid + "rename", this->inputRename);
				GUI::ContinueSameLine();
				
				if (GUI::Button("Rename"))
				{
					std::string newName = basePath + '/' + this->inputRename;

					if (Utils::Directory::Exists(newName))
						GUI::CloseCurrentPopUp();

					Utils::Directory::Move(this->popUpItem.path, newName);

					this->shouldUpdate = true;
					GUI::CloseCurrentPopUp();
				}

				GUI::EndMenu();
			}

			if (!this->popUpItem.isRoot && GUI::Selectable(this->guid + "copy", "Copy"))
			{
				this->toCopy = this->popUpItem.path;
				this->isCut = false;
			}

			if (!this->popUpItem.isRoot && GUI::Selectable(this->guid + "cut", "Cut"))
			{
				this->toCopy = this->popUpItem.path;
				this->isCut = true;
			}

			if (this->toCopy.size() > 0 && 
				Utils::Directory::Exists(this->toCopy) &&
				Utils::Directory::Exists(this->popUpItem.path) &&
				this->popUpItem.isDir &&
				GUI::Selectable(this->guid + "paste", "Paste"))
			{
				this->shouldUpdate = true;
				std::string newPath = Utils::Directory::GetLastPartFromPath(this->toCopy);
				if(isCut)
					Utils::Directory::Move(this->toCopy, this->popUpItem.path + '/' + newPath);
				else
					Utils::Directory::Copy(this->toCopy, this->popUpItem.path + '/' + newPath);
			}

			if (!this->popUpItem.isRoot && GUI::BeginMenu("Delete"))
			{
				if (GUI::Button("No"))
					GUI::CloseCurrentPopUp();
				
				GUI::ContinueSameLine();
				
				if (GUI::Button("Yes") && Utils::Directory::Exists(this->popUpItem.path))
				{
					Utils::Directory::Delete(this->popUpItem.path, true);

					this->shouldUpdate = true;
					GUI::CloseCurrentPopUp();
				}
				GUI::EndMenu();
			}

			GUI::EndPopUp();
		}
	}

	std::string FilesTab::GetScriptFile(const std::string& name)
	{
		return  name + " = {}\n\nfunction " + name + ".start()\nend\n\nfunction " + name + ".update()\nend\n\nfunction " + name + ".destroy()\nend";
	}
}}

