#include <BoxEngine.hpp>
#include "TopBar.hpp"

namespace BoxEngine {
namespace Editor {

	void TopBar::Reset()
	{
		this->reset = true;
	}

	void TopBar::Update()
	{
		using namespace BoxEngine::Window;
		using namespace BoxEngine::Project;
		using Project = BoxEngine::Project::Project;
		using Window = BoxEngine::Window::Window;
			
		ProjectPtr currentProject = Project::GetCurrentProject();

		if (currentProject == nullptr)
			return;

		if (GUI::BeginMainMenuBar())
		{
			auto project = Project::GetCurrentProject();

			if (GUI::BeginMenu("File"))
			{
				if (GUI::MenuItem("Save", currentProject->GetState() == ProjectState::Idle))
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

			GUI::EndMainMenuBar();
		}
	}
}}

