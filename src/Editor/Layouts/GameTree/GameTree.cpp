#include <BoxEngine.hpp>
#include "GameTree.hpp"

namespace BoxEngine {
namespace Editor {

	void GameTree::Awake()
	{
		this->guid = Utils::Directory::NewGuid();
	}

	void GameTree::Update()
	{
		using namespace BoxEngine::Window;
		using namespace BoxEngine::Project;
		using Window = BoxEngine::Window::Window;
		using Project = BoxEngine::Project::Project;

		auto size = Window::GetSize();
		auto project = Project::GetCurrentProject();

		if (this->reset)
		{
			GUI::SetNextWindowPosition({ 0, TOPBAR_Y });
			GUI::SetNextWindowSize({ size.x * 0.2, this->minY - TOPBAR_Y });

			this->reset = false;
		}

		if (GUI::BeginWindow("Game Tree", nullptr, {
			GUIWindowFlags::NoMove, 
			GUIWindowFlags::NoCollapse, 
			project->isDirty() ? GUIWindowFlags::UnsavedDocument : GUIWindowFlags::None })
		)
		{
			auto guiPosition = GUI::GetWindowPosition();
			auto guiSize = GUI::GetWindowSize();

			if (guiPosition.x < 0 ||
				guiPosition.x >= 1 ||
				guiPosition.y != TOPBAR_Y ||
				guiSize.y != this->minY - TOPBAR_Y)
			{
				this->reset = true;
			}

			this->maxX = guiSize.x;

			if (GUI::ImageButton(this->guid + "start", GUI::GetIcon("start.png")) && project->GetState() == ProjectState::Idle)
			{
				if (project->isDirty())
					Debug::Logging::Log("[Project]: Please save or discard changes before run", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
				else
				{
					Editor::GetCurrentEditor()->ClearLogs();
					project->Start();
				}
			}

			if (GUI::IsCurrentItemHovered())
			{
				GUI::BeginHintWindow();
				GUI::Text("Run");
				GUI::EndHintWindow();
			}

			GUI::ContinueSameLine();
		
			if (GUI::ImageButton(this->guid + "stop", GUI::GetIcon("stop.png")) && project->GetState() == ProjectState::Running)
				project->Stop();

			if (GUI::IsCurrentItemHovered())
			{
				GUI::BeginHintWindow();
				GUI::Text("Stop");
				GUI::EndHintWindow();
			}

			GUI::ContinueSameLine();

			if (GUI::ImageButton(this->guid + "add_go_global", GUI::GetIcon("add.png")))
			{
				if(project->GetState() == ProjectState::Idle)
					Project::GetCurrentProject()->AddGameObjectInEditor("New Game Object");
				else 
					project->AddGameObject("New Game Object", true);
			}

			if (GUI::IsCurrentItemHovered())
			{
				GUI::BeginHintWindow();
				GUI::Text("Add game object in root");
				GUI::EndHintWindow();
			}

			GUI::Separator();
			GUI::Text("Filter: ");
			GUI::ContinueSameLine();
			GUI::Input(this->guid + "filter", this->filter);

			GUI::Separator();

			this->DrawGameTree();

			GUI::EndWindow();
		}

		this->DrawMenus();
	}

	float GameTree::GetMaxX() const
	{
		if (this->maxX < 0)
			return 0;

		return this->maxX;
	}

	void GameTree::SetMinY(float value)
	{
		this->minY = value;
	}

	void GameTree::DrawGameTree()
	{
		using Project = BoxEngine::Project::Project;
		using namespace BoxEngine::Project;

		auto gos = Project::GetCurrentProject()->GetGosFromRoot();

		RecursiveDrawGameTree(gos);
	}

	void GameTree::RecursiveDrawGameTree(std::vector<Project::GameObjectPtr>& gos, bool inactive)
	{
		using Project = BoxEngine::Project::Project;
		using namespace BoxEngine::Project;
		using namespace BoxEngine::Window;

		auto project = Project::GetCurrentProject();

		for (GameObjectPtr& go : gos)
		{
			if (this->filter != "" && isFiltered(go, this->filter))
				continue;

			bool nodeOpen = GUI::BeginTreeNode(
				this->guid + go->GetId(),
				"##",
				{ go->GetChildrens().size() > 0 ? GUITreeFlags::OpenOnArrow : GUITreeFlags::Bullet }
			);

			auto father = go->GetFather();

			if (father != nullptr && father->GetActive() == false)
				inactive = true;

			GUI::ContinueSameLine(10);
			GUI::Image(go->GetActive() && !inactive ? GUI::GetIcon("box.png") : GUI::GetIcon("closed_box.png"), {GUI::GetFontSize(), GUI::GetFontSize()});
			GUI::ContinueSameLine();

			if (GUI::Selectable(go->GetId(), go->GetName()))
				Editor::GetCurrentEditor()->InspectGo(go);

			if (GUI::IsCurrentItemClickedRight())
			{
				this->isMenuGoOpen = true;
				this->createGoInput = "";
				this->clickedGoId = go->GetId();
			}

			if (nodeOpen)
			{
				RecursiveDrawGameTree(go->GetChildrens(), inactive);

				GUI::EndTreeNode();
			}
		}
	}

	bool GameTree::isFiltered(Project::GameObjectPtr go, std::string value)
	{
		if (go->GetName().find(value) != std::string::npos || go->GetId().find(value) != std::string::npos)
			return false;

		for (auto& item : go->GetChildrens())
			if (!isFiltered(item, value))
				return false;

		return true;
	}

	void GameTree::DrawMenus()
	{
		using namespace BoxEngine::Project;
		using namespace BoxEngine::Window;
		using Window = BoxEngine::Window::Window;
		using Project = BoxEngine::Project::Project;

		auto project = Project::GetCurrentProject();

		if (this->isMenuGoOpen)
		{
			GUI::OpenPopUp(this->guid + "go_menu");
			this->isMenuGoOpen = false;
		}

		if (GUI::BeginPopUp(this->guid + "go_menu"))
		{
			if (GUI::BeginMenu("Create children"))
			{
				GUI::Input(this->guid + "create_go_input", this->createGoInput);
				GUI::ContinueSameLine();
				if (GUI::Button("Create"))
				{
					if(project->GetState() == ProjectState::Idle)
						project->AddGameObjectInEditor(this->createGoInput, this->clickedGoId);
					else 
						project->AddGameObject(this->createGoInput, true, this->clickedGoId);

					GUI::CloseCurrentPopUp();
				}

				GUI::EndMenu();
			}

			if (GUI::Selectable(this->guid + "delete_go", "Delete"))
			{
				if (project->GetState() == ProjectState::Idle)
					project->RemoveGameObjectInEditor(this->clickedGoId);
				else
					project->DestroyGameObject(this->clickedGoId);
			}

			GUI::EndPopUp();
		}
	}
}}

