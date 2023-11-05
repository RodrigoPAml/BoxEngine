#include <BoxEngine.hpp>
#include "TopBar.hpp"

namespace BoxEngine {
namespace Editor {

	using namespace Modules;
	using namespace Engine;

	void TopBar::Reset()
	{
		this->reset = true;
	}

	void TopBar::Update()
	{
		using namespace Window;
		using namespace Project;
		using Project = Engine::Project::Project;
		using Window = Modules::Window::Window;
			
		ProjectPtr currentProject = Project::GetCurrentProject();

		if (currentProject == nullptr)
			return;

		if (GUI::BeginMainMenuBar())
		{
			auto project = Project::GetCurrentProject();

			if (GUI::BeginMenu("File"))
			{
				if (GUI::MenuItem("Save", currentProject->GetState() == ProjectState::Idle || currentProject->GetMode() == ProjectMode::EditorMode))
				{
					try
					{
						currentProject->Save();
					}
					catch (const std::runtime_error& error)
					{
						Debug::Logging::Log(error.what(), Debug::LogSeverity::Error, Debug::LogOrigin::Engine);
					}
				}

				if (project->GetState() == ProjectState::Idle && GUI::MenuItem("Discard changes"))
				{
					if (project != nullptr)
						project->Reload();
				}

				if (project->GetState() == ProjectState::Idle && GUI::MenuItem("Reload"))
				{
					if (currentProject->isDirty())
						Debug::Logging::Log("[Project]: Before reload, please save the changes", Debug::LogSeverity::Error, Debug::LogOrigin::Engine);
					else 
						project->Reload();
				}

				if (currentProject->isDirty())
				{
					if (GUI::BeginMenu("Exit", currentProject->GetState() == ProjectState::Idle))
					{
						GUI::ColoredText("There are unsaved changes. Do you want to save it?", { 1.0f, 0.0f, 0.0f, 1.0f });

						if (GUI::Button("Yes"))
						{
							currentProject->Save();
							Window::Close();
						}

						GUI::ContinueSameLine();

						if (GUI::Button("No"))
							Window::Close();

						GUI::EndMenu();
					}
				}
				else if (GUI::MenuItem("Exit", currentProject->GetState() == ProjectState::Idle))
					Window::Close();

				GUI::EndMenu();
			}

			if (GUI::BeginMenu("Options"))
			{
				if (GUI::MenuItem("Edit Settings"))
					Editor::GetCurrentEditor()->InspectProjectSettings();

				if (GUI::MenuItem("Refresh scripts list"))
				{
					if (project != nullptr)
						project->LoadScriptNameListForEditor();
				}

				if (GUI::MenuItem("Open VS Code Project"))
					Utils::Directory::Execute("code \"" + project->GetBasePath() + "\"");

				GUI::EndMenu();
			}

			if (GUI::BeginMenu("Mode"))
			{
				auto mode = currentProject->GetMode();

				if (GUI::MenuItem("Set Play Mode", mode == ProjectMode::EditorMode && currentProject->GetState() == ProjectState::Idle))
					currentProject->SetMode(ProjectMode::PlayMode);

				if (GUI::MenuItem("Set Editor Mode", mode == ProjectMode::PlayMode && currentProject->GetState() == ProjectState::Idle))
					currentProject->SetMode(ProjectMode::EditorMode);

				GUI::EndMenu();
			}

			if (GUI::BeginMenu("About"))
			{
				if (GUI::MenuItem("GitHub"))
					Utils::Directory::Execute("explorer https://github.com/RodrigoPAml/BoxEngine/blob/main/docs/api.md");

				if (GUI::MenuItem("Documentation"))
					Utils::Directory::Execute("explorer https://github.com/RodrigoPAml/BoxEngine");

				GUI::EndMenu();
			}

			GUI::EndMainMenuBar();
		}
	}
}}

