#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	using namespace Engine;

	class ProjectManager : public Layout
	{
	private:
		Project::ProjectPtr project = nullptr;

		std::string currentPath = "";
		std::string currentFilter = "";
		std::string currentProjectName = "";
		std::string guid = Utils::Directory::NewGuid();

		bool isCreateMode = false;
		bool shouldResize = false;
		bool isDialogOpen = false;

		glm::vec3 color = { 1, 0, 0 };
		std::string warningTitle = "Warning";
		std::string warningContent = "Warning";
		bool shouldOpenWarningModal = false;
		bool shouldOpenProject = false;

		std::string startingPath = "C:/Users";
	public:
		ProjectManager() = default;
		~ProjectManager() = default;

		void Start();
		void Awake();
		void Update();
		void Destroy();

		Project::ProjectPtr GetProject() const;
	private:
		void DrawCreateProjectDialog();
		void DrawLoadProjectDialog(const std::string& filename);

		std::vector<std::string> LoadRecents();
		void WriteRecents(const std::string& path);
	};
}}