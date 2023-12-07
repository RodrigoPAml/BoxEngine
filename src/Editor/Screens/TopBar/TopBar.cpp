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

		this->focused = false;
		this->visualizer.Update();

		if (GUI::BeginMainMenuBar())
		{
			if (GUI::BeginMenu("File"))
			{
				this->focused = true;

				if (GUI::MenuItem("Save", currentProject->GetState() == ProjectState::Idle || currentProject->GetMode() == ProjectMode::EditorMode, "CTRL + S"))
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

				if (currentProject->GetState() == ProjectState::Idle && GUI::MenuItem("Discard changes", true, "CTRL + Z"))
				{
					if (currentProject != nullptr)
						currentProject->Reload();
				}

				if (currentProject->GetState() == ProjectState::Idle && GUI::MenuItem("Reload", true, "CTRL + X"))
				{
					if (currentProject->isDirty())
						Debug::Logging::Log("[Project]: Before reload, please save the changes", Debug::LogSeverity::Error, Debug::LogOrigin::Engine);
					else 
						currentProject->Reload();
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
				this->focused = true;

				if (GUI::MenuItem("Edit Settings"))
					Editor::GetCurrentEditor()->InspectProjectSettings();

				if (GUI::MenuItem("Refresh scripts list") && currentProject != nullptr)
					currentProject->LoadScriptNameListForEditor();

				if (GUI::MenuItem("Open VS Code Project"))
					Utils::Directory::Execute("code \"" + currentProject->GetBasePath() + "\"");

				if (GUI::MenuItem("Open Texture Visualizer"))
					this->visualizer.SetOpen(true);

				GUI::EndMenu();
			}

			if (GUI::BeginMenu("Mode"))
			{
				this->focused = true;

				auto mode = currentProject->GetMode();

				if (GUI::MenuItem("Set Play Mode", mode == ProjectMode::EditorMode && currentProject->GetState() == ProjectState::Idle))
					currentProject->SetMode(ProjectMode::PlayMode);

				if (GUI::MenuItem("Set Editor Mode", mode == ProjectMode::PlayMode && currentProject->GetState() == ProjectState::Idle))
					currentProject->SetMode(ProjectMode::EditorMode);

				GUI::EndMenu();
			}

			if (GUI::BeginMenu("About"))
			{
				this->focused = true;

				if (GUI::MenuItem("Documentation"))
					Utils::Directory::Execute("explorer https://github.com/RodrigoPAml/BoxEngine/blob/main/docs/api.md");

				if (GUI::MenuItem("GitHub"))
					Utils::Directory::Execute("explorer https://github.com/RodrigoPAml/BoxEngine");

				GUI::EndMenu();
			}

			GUI::EndMainMenuBar();

			this->Shortcuts();
		}
	}

	void TopBar::DrawTextureVisualizerTex()
	{
		this->visualizer.DrawTexture();
	}

	void TopBar::Shortcuts()
	{
		using namespace Project;
		using Project = Engine::Project::Project;

		auto project = Project::GetCurrentProject();

		// Save shortcut (CTRL + S)
		if (Input::Keyboard::GetKeyState(Input::KeyboardKey::KEY_S) >= Input::InputAction::PRESS &&
			Input::Keyboard::GetModState(Input::KeyModifier::CONTROL) >= Input::InputAction::PRESS &&
			(project->GetState() == ProjectState::Idle || project->GetMode() == ProjectMode::EditorMode)
		)
		{
			project->Save();
		}

		// Play/Stop shortcut (CTRL + SPACE)
		if (Input::Keyboard::GetKeyState(Input::KeyboardKey::KEY_SPACE) >= Input::InputAction::PRESS &&
			Input::Keyboard::GetModState(Input::KeyModifier::CONTROL) >= Input::InputAction::PRESS
		)
		{
			if (project->GetState() == ProjectState::Idle)
				project->Start();
			else if (project->GetState() == ProjectState::Running)
				project->Stop();
		}

		// Discard (CTRL + Z)
		if (Input::Keyboard::GetKeyState(Input::KeyboardKey::KEY_Z) >= Input::InputAction::PRESS &&
			Input::Keyboard::GetModState(Input::KeyModifier::CONTROL) >= Input::InputAction::PRESS
		)
		{
			if (project->GetState() == ProjectState::Idle)
			{
				if (project != nullptr)
					project->Reload();
			}
		}

		// Reload (CTRL + X)
		if (Input::Keyboard::GetKeyState(Input::KeyboardKey::KEY_X) >= Input::InputAction::PRESS &&
			Input::Keyboard::GetModState(Input::KeyModifier::CONTROL) >= Input::InputAction::PRESS
		)
		{
			if (project->GetState() == ProjectState::Idle)
			{
				if (project->isDirty())
					Debug::Logging::Log("[Project]: Before reload, please save the changes", Debug::LogSeverity::Error, Debug::LogOrigin::Engine);
				else
					project->Reload();
			}
		}
	}

	bool TopBar::IsFocused()
	{
		return this->visualizer.IsFocused() || this->focused;
	}
}}

