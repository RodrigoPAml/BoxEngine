#include <BoxEngine.hpp>
#include "GameTree.hpp"

namespace BoxEngine {
namespace Editor {

	using namespace Modules;

	void GameTree::Awake()
	{
		this->guid = Utils::Directory::NewGuid();
	}

	void GameTree::Update()
	{
		using namespace Modules::Window;
		using namespace Engine::Project;
		using Window = Modules::Window::Window;
		using Project = Engine::Project::Project;

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
				project->AddGameObject("New Game Object", true);

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

			if (GUI::BeginInnerWindow(this->guid + "inner", {0, 0}))
			{
				this->DrawGameTree();
				GUI::EndInnerWindow();
			}

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
		using Project = Engine::Project::Project;
		using namespace Engine::Project;

		auto gos = Project::GetCurrentProject()->GetGosFromRoot();
		auto project = Project::GetCurrentProject();

		RecursiveDrawGameTree(gos);

		if (this->sourceGoId.size() > 0)
		{
			project->ChangeGoFather(this->sourceGoId, this->destinyGoId);
			this->sourceGoId = "";
			this->destinyGoId = "";
		}
	}

	void GameTree::RecursiveDrawGameTree(std::vector<Engine::Project::GameObjectPtr>& gos, bool inactive)
	{
		using Project = Engine::Project::Project;
		using namespace Engine::Project;
		using namespace Modules::Window;

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
				Editor::GetCurrentEditor()->InspectGo(go->GetId());

			if (GUI::IsCurrentItemClickedRight())
			{
				this->isMenuGoOpen = true;
				this->createGoInput = "";
				this->clickedGoId = go->GetId();
			}

			if (GUI::BeginSourceDragDrop())
			{
				GUI::Text(go->GetName());
				GUI::SetDragDropData("move_go", go->GetId());
				GUI::EndSourceDragDrop();
			}
			
			if (GUI::BeginDestinyDragDrop())
			{
				std::string goId = GUI::GetDragDropData("move_go");
				
				if (goId.size() > 0)
				{
					this->sourceGoId = goId;
					this->destinyGoId = go->GetId();
				}

				GUI::EndDestinyDragDrop();
			}

			if (nodeOpen)
			{
				RecursiveDrawGameTree(go->GetChildrens(), inactive);

				GUI::EndTreeNode();
			}
		}
	}

	bool GameTree::isFiltered(Engine::Project::GameObjectPtr go, std::string value)
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
		using Project = Engine::Project::Project;
		using namespace Engine::Project;

		using namespace Modules::Window;
		using Window = Modules::Window::Window;

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
					project->AddGameObject(this->createGoInput, true, this->clickedGoId);
					GUI::CloseCurrentPopUp();
				}

				GUI::EndMenu();
			}

			if (GUI::Selectable(this->guid + "delete_go", "Delete"))
				project->DestroyGameObject(this->clickedGoId);

			if (GUI::Selectable(this->guid + "duplicate_go", "Duplicate"))
				project->DuplicateGo(this->clickedGoId);

			if (GUI::Selectable(this->guid + "move_top", "Move to Root"))
				this->sourceGoId = this->clickedGoId;

			GUI::EndPopUp();
		}
	}
}}

