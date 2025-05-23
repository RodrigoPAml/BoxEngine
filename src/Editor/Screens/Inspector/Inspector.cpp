#include <BoxEngine.hpp>
#include "Inspector.hpp"

namespace BoxEngine {
namespace Editor {
	
	using namespace Modules;
	using namespace Engine;

	void Inspector::Start()
	{
		this->guid = Utils::Directory::NewGuid();
	}

	void Inspector::Update()
	{
		using namespace Modules::Window;
		using Window = Modules::Window::Window;

		auto size = Window::GetSize();
		auto project = Engine::Project::Project::GetCurrentProject();

		if (this->reset)
		{
			GUI::SetNextWindowPosition({ size.x * 0.8, TOPBAR_Y });
			GUI::SetNextWindowSize({ size.x * 0.2, this->minY - TOPBAR_Y });

			this->reset = false;
		}

		if (GUI::BeginWindow(
			"Inspector",
			nullptr,
			{
				GUIWindowFlags::NoMove,
				GUIWindowFlags::NoCollapse,
				GUIWindowFlags::NoBringToFrontOnFocus,
				project->isDirty() ? GUIWindowFlags::UnsavedDocument : GUIWindowFlags::None
			})
			)
		{
			auto guiPosition = GUI::GetWindowPosition();
			auto guiSize = GUI::GetWindowSize();

			if (std::abs(guiPosition.x + guiSize.x - Window::GetSize().x) > 2 ||
				guiPosition.y != TOPBAR_Y ||
				guiSize.y != this->minY - TOPBAR_Y)
			{
				this->reset = true;
			}

			this->minX = guiPosition.x;

			if (this->isInspectingProjectSettings)
				this->ShowProjectSettings();

			if (this->isInspectingGo)
				this->ShowGoEditor();

			this->focused = GUI::IsCurrentWindowFocused() || GUI::IsAnyItemFocused();
			GUI::EndWindow();
		}
		else this->focused; 

		this->debugger.Update();
	}

	bool Inspector::IsFocused()
	{
		return this->focused || this->debugger.IsFocused();
	}

	void Inspector::InspectProjectSettings()
	{
		auto project = Project::Project::GetCurrentProject();

		this->isInspectingGo = false;
		this->isInspectingProjectSettings = true;
		this->projectName = project->GetName();
		this->debugConfig = Debug::Debugging::GetConfiguration();
		this->loggingConfig = Debug::Logging::GetConfiguration();

		this->useSeverityLow = this->debugConfig.openGlSeverities.contains(Debug::OpenGlErrorSeverity::SEVERITY_LOW);
		this->useSeverityHigh = this->debugConfig.openGlSeverities.contains(Debug::OpenGlErrorSeverity::SEVERITY_HIGH);
		this->useSeverityMedium = this->debugConfig.openGlSeverities.contains(Debug::OpenGlErrorSeverity::SEVERITY_MEDIUM);
		this->useSeverityNotification = this->debugConfig.openGlSeverities.contains(Debug::OpenGlErrorSeverity::SEVERITY_NOTIFICATION);
	}

	void Inspector::InspectGo(std::string goId)
	{
		auto ref = Project::Project::GetCurrentProject()->GetGameObject(goId);

		if (ref == nullptr)
			return;

		this->isInspectingGo = true;
		this->isInspectingProjectSettings = false;
		this->goName = ref->GetName();
		this->goActive = ref->GetActive();
		this->goId = goId;
	}

	std::string Inspector::GetInspectedGo()
	{
		if (this->isInspectingGo)
			return this->goId;

		return "";
	}

	void Inspector::SetMinY(float value)
	{
		this->minY = value;
	}

	float Inspector::GetMinX() const
	{
		if (this->minX < 0)
			return 0;

		return this->minX;
	}

	void Inspector::ShowProjectSettings()
	{
		using namespace Modules::Window;
		using Window = Modules::Window::Window;

		auto project = Project::Project::GetCurrentProject();
	
		if (project == nullptr)
			return;

		GUI::SetFontScale(0.5);
		
		if (GUI::BeginInnerWindow(this->guid + "inner", {0, 0}))
		{
			GUI::Text("Project name:");
			GUI::ContinueSameLine();

			auto guiSize = GUI::GetWindowSize();
			GUI::SetNextItemWidth(guiSize.x/2);
			GUI::Input(this->guid + "edit_project_name", this->projectName);

			auto showLogging = GUI::Header("Logging settings");
			GUI::ContinueSameLine(15);
			GUI::Text("Logging settings");

			if (showLogging)
			{
				GUI::Ident(20);

				GUI::Text("Logs shows into editor");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_logCallback", this->loggingConfig.logCallback);

				GUI::Text("Logs shows into console");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_logConsole", this->loggingConfig.logConsole);

				GUI::Text("Logs stored into file");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_logFile", this->loggingConfig.logFile);

				GUI::Unident(20);
			}

			auto showDebug = GUI::Header("Debugging settings");
			GUI::ContinueSameLine(15);
			GUI::Text("Debugging settings");

			if (showDebug)
			{
				GUI::Ident(20);

				GUI::BulletText("You might want to restart to see effect in this settings");

				GUI::Text("Activate callbacks to recieve logs from GLFW");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_enableGlfwDebugging", this->debugConfig.enableGlfwDebugging);

				GUI::Text("Activate callbacks to recieve logs from OpenGL");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_enableOpenGLDebugging", this->debugConfig.enableOpenGLDebugging);

				GUI::Text("Auto generate GLFW logs");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_autoLogGLFWErrors", this->debugConfig.autoLogGLFWErrors);

				GUI::Text("Auto generate OpenGL logs");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_autoLogOpenGLErrors", this->debugConfig.autoLogOpenGLErrors);

				GUI::Text("Log notifications OpenGL");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_logOpenGLNotification", this->useSeverityNotification);

				GUI::Text("Log low severity errors in OpenGL");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_logOpenGLLow", this->useSeverityLow);

				GUI::Text("Log medium severity errors in OpenGL ");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_logOpenGLMedium", this->useSeverityMedium);

				GUI::Text("Log high severity errors OpenGL ");
				GUI::ContinueSameLine();
				GUI::CheckBox(this->guid + "edit_project_logOpenGLErrors", this->useSeverityHigh);

				this->debugConfig.openGlSeverities.clear();

				if (this->useSeverityNotification)
					this->debugConfig.openGlSeverities.insert(Debug::OpenGlErrorSeverity::SEVERITY_NOTIFICATION);
				if (this->useSeverityLow)
					this->debugConfig.openGlSeverities.insert(Debug::OpenGlErrorSeverity::SEVERITY_LOW);
				if (this->useSeverityMedium)
					this->debugConfig.openGlSeverities.insert(Debug::OpenGlErrorSeverity::SEVERITY_MEDIUM);
				if (this->useSeverityHigh)
					this->debugConfig.openGlSeverities.insert(Debug::OpenGlErrorSeverity::SEVERITY_HIGH);

				GUI::Unident(20);
			}

			if (GUI::Button("Save changes"))
			{
				Debug::Debugging::SetConfiguration(this->debugConfig);
				Debug::Logging::SetConfiguration(this->loggingConfig);

				project->SetName(this->projectName);
				project->Save();
			}

			GUI::EndInnerWindow();
		}

		GUI::SetFontScale(1);
	}

	void Inspector::ShowGoEditor()
	{
		auto project = Project::Project::GetCurrentProject();

		using namespace Project;
		using Project = Engine::Project::Project;
		using namespace Modules::Window;
		using Window = Modules::Window::Window;

		GameObjectPtr go = project->GetGameObject(goId);

		if (go == nullptr)
		{
			this->goId = "";
			return;
		}
		
		// Header info, only gos information
		if (GUI::BeginInnerWindow(this->guid + "window_header", {0, 135}))
		{
			this->ShowGoEditorHeader(go);
			GUI::EndInnerWindow();
		}

		// Window that show scripts and its data
		if (GUI::BeginInnerWindow(this->guid + "window_scripts", { 0, 0 }))
		{
			this->ShowGoEditorScripts(go);
			GUI::EndInnerWindow();
		}
	}

	void Inspector::ShowGoEditorHeader(Project::GameObjectPtr go)
	{
		auto project = Project::Project::GetCurrentProject();

		using namespace Project;
		using Project = Engine::Project::Project;
		using namespace Modules::Window;
		using Window = Modules::Window::Window;

		if (go == nullptr)
			return;

		// Show id
		GUI::SetFontScale(0.65);
		GUI::Text("ID: " + go->GetId());
		GUI::Separator();

		// Show name
		GUI::Text("Name: ");
		GUI::ContinueSameLine();

		if (project->GetState() == ProjectState::Idle && GUI::Input(this->guid + "go_name", this->goName))
		{
			go->SetName(this->goName);
			project->SetDirty();
		}
		else if (project->GetState() == ProjectState::Running)
			GUI::Text(this->goName);

		GUI::Separator();
		GUI::SetFontScale(0.9);

		// Go activation
		if (project->GetState() == ProjectState::Idle && GUI::CheckBox(this->guid + "go_active", this->goActive))
		{
			go->SetActive(this->goActive);
			project->SetDirty();
		}
		else if (project->GetState() == ProjectState::Running && GUI::CheckBox(this->guid + "go_active", this->goActive))
			go->SetActive(this->goActive);

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Activated or not the Game Object");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		// Add script button
		if (GUI::ImageButton(this->guid + "add_script", GUI::GetIcon("add_file.png")))
			GUI::OpenPopUp(this->guid + "scripts_pop_up");

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Add script");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		// Copy id button
		if (GUI::ImageButton(this->guid + "copy_id", GUI::GetIcon("copy.png")))
			Utils::Directory::CopyClipboard(go->GetId());

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Copy Id");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		// Move up go
		if (GUI::ImageButton(this->guid + "move_up", GUI::GetIcon("up.png")))
			project->ChangeGoPosition(go->GetId(), -1);

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Move up");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		// Move Down go
		if (GUI::ImageButton(this->guid + "move_down", GUI::GetIcon("down.png")))
			project->ChangeGoPosition(go->GetId(), 1);

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Move down");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();
		
		// Debugger for scripts of go
		if (GUI::ImageButton(this->guid + "debugging" + goId, GUI::GetIcon("debugging.png")) && project->GetState() != ProjectState::Idle)
		{
			this->debugger.SetGo(goId);
			this->debugger.SetOpen(true);
		}

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Open debugger");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		std::string imgName = std::to_string((int)go->GetRunMode()+1) + ".png";
		auto mode = (int)go->GetRunMode();

		// Move Down go
		if (GUI::ImageButton(this->guid + "mode", GUI::GetIcon(imgName)) && project->GetState() == ProjectState::Idle)
		{
			mode = mode + 1;
			go->SetRunMode((RunMode)(mode > 2 ? 0 : mode));
			project->SetDirty();
		}

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Current mode: " + RunModeToString(go->GetRunMode()));
			GUI::EndHintWindow();
		}

		GUI::SetFontScale(0.6);
		if(project->GetState() == ProjectState::Idle)
			GUI::Text("State: Normal");
		else
			GUI::Text("State: " + GoStateToStringForEditor(go->GetActive(), go->GetRunMode(), project->GetMode()));

		GUI::SetFontScale(1);

		// Pop up to add scripts
		if (GUI::BeginPopUp(this->guid + "scripts_pop_up"))
		{
			GUI::Text("Search: ");
			GUI::ContinueSameLine();
			GUI::Input(this->guid + "script_filter", this->scriptFilter);

			auto scripts = Project::GetCurrentProject()->GetScriptNamesForEditor();

			GUI::Text("Select: ");
			GUI::ContinueSameLine();
			GUI::ComboBox(this->guid + "go_scripts", scripts, selectedScript, this->scriptFilter);

			if (GUI::Button("Add") && selectedScript >= 0)
			{
				GUI::CloseCurrentPopUp();

				if (project->GetState() == ProjectState::Idle)
				{
					go->AddScript(ScriptPtr(new Script(scripts[selectedScript])));
					project->SetDirty();
				}
				else
					project->AddScript(go->GetId(), scripts[selectedScript]);
			}

			GUI::EndPopUp();
		}
	}

	void Inspector::ShowGoEditorScripts(Project::GameObjectPtr go)
	{
		auto project = Project::Project::GetCurrentProject();

		using namespace Project;
		using Project = Engine::Project::Project;
		using namespace Modules::Window;
		using Window = Modules::Window::Window;

		std::vector<ScriptPtr> toRemoves;
		int id = 0;

		if (go == nullptr)
			return;

		project->UpdateScriptData(go);
		for (const auto& script : go->GetScripts())
		{
			std::string scriptName = script->GetName();

			bool isOpen = GUI::Header(this->guid + "header" + scriptName);
			GUI::ContinueSameLine();
			GUI::Ident(8);
			GUI::Image(GUI::GetIcon("code.png"), { GUI::GetFontSize(), GUI::GetFontSize() + 5 });
			GUI::ContinueSameLine();
			GUI::Text(scriptName);

			auto size = GUI::GetWindowSize().x - (GUI::CalculateTextSize(scriptName).x);
			GUI::ContinueSameLine(size - 130);
			
			// Script activation
			bool active = script->GetActive();
			if (project->GetState() == ProjectState::Idle && GUI::CheckBox(this->guid + "script_active" + scriptName, active))
			{
				script->SetActive(active);
				project->SetDirty();
			}
			else if (project->GetState() == ProjectState::Running && GUI::CheckBox(this->guid + "script_active" + scriptName, active))
				script->SetActive(active);

			if (GUI::IsCurrentItemHovered())
			{
				GUI::BeginHintWindow();
				GUI::Text("Activated or not the script");
				GUI::EndHintWindow();
			}

			GUI::ContinueSameLine();

			if (GUI::ImageButton(this->guid + "remove_script" + scriptName, GUI::GetIcon("remove_file.png")))
			{
				if (project->GetState() == ProjectState::Idle)
				{
					project->SetDirty();
					toRemoves.push_back(script);
				}
				else
				{
					if(script->GetState() == ScriptState::Destroyed)
						toRemoves.push_back(script);
					else
						project->DestroyScript(go->GetId(), scriptName, false);
				}
			}

			if (GUI::IsCurrentItemHovered())
			{
				GUI::BeginHintWindow();
				GUI::Text("Remove script");
				GUI::EndHintWindow();
			}

			if (!isOpen)
			{
				GUI::Unident(8);
				continue;
			}

			if (script->HaveWarningToLoad())
			{
				GUI::SetFontScale(0.5);
				GUI::ColoredText("This script have failed to be found! Fix/Remove it and Reload.", { 1, 0.8, 0, 1 });
				GUI::Unident(8);
				GUI::SetFontScale(1);

				continue;
			}

			GUI::SetFontScale(0.6);
			if (project->GetState() == ProjectState::Idle)
				GUI::Text("State: Idle");
			else 
				GUI::Text("State: " + ScriptStateToStringForEditor(script->GetState(), go->GetActive() && script->GetActive(), script->GetRunMode(), project->GetMode()));

			GUI::ContinueSameLine();

			std::string imgName = std::to_string((int)script->GetRunMode() + 1) + ".png";
			auto mode = (int)script->GetRunMode();

			// Move Down go
			if (GUI::ImageButton(this->guid + "mode" + scriptName, GUI::GetIcon(imgName)) && project->GetState() == ProjectState::Idle)
			{
				mode = mode + 1;
				script->SetRunMode((RunMode)(mode > 3 ? 0 : mode));
				project->SetDirty();
			}

			if (GUI::IsCurrentItemHovered())
			{
				GUI::BeginHintWindow();
				GUI::Text("Current mode: " + RunModeToString(script->GetRunMode()));
				GUI::EndHintWindow();
			}

			GUI::Separator();
			this->ShowGoEditorScriptsData(go, script);
		}

		for (const auto& item : toRemoves)
			go->RemoveScript(item);
	}

	void Inspector::ShowGoEditorScriptsData(Project::GameObjectPtr go, Project::ScriptPtr script)
	{
		auto project = Project::Project::GetCurrentProject();

		using namespace Project;
		using Project = Engine::Project::Project;
		using namespace Modules::Window;
		using Window = Modules::Window::Window;

		std::string scriptName = script->GetName();
		GUI::SetFontScale(0.9);

		if (GUI::ImageButton(this->guid + "add_script_data" + scriptName, GUI::GetIcon("add_data.png")) && project->GetState() == ProjectState::Idle)
		{
			this->scriptDataName = "";
			this->scriptDataType = 0;
			GUI::OpenPopUp(this->guid + "scripts_data_pop_up" + scriptName);
		}

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Add script variable");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();
	
		if (GUI::ImageButton(this->guid + "move_script_up" + scriptName, GUI::GetIcon("up.png")))
			project->ChangeScriptPosition(go->GetId(), script->GetName(), -1);

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Move Up");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		if (GUI::ImageButton(this->guid + "move_script_down" + scriptName, GUI::GetIcon("down.png")))
			project->ChangeScriptPosition(go->GetId(), script->GetName(), 1);

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Move Down");
			GUI::EndHintWindow();
		}

		int id = 0;
		// Script data of script
		if (GUI::BeginTable(this->guid + "table" + scriptName, 3))
		{
			std::string dataToRemove = "";
			bool moveUp = false;
			int indexToMove = -1;

			// Script data
			GUI::SetFontScale(0.65);
			GUI::Ident(16);
			
			for (ScriptData& data : script->GetScriptData())
			{
				if (data.GetName()[0] == '_' && !Editor::GetCurrentEditor()->GetShowPrivateVariables())
					continue;

				if (!data.IsShowEditor())
					continue;

				GUI::NextRow();
				GUI::NextColumn();
				
				std::string innerId = std::to_string(id);
				
				// script data name
				GUI::Text(data.GetName());

				GUI::NextColumn();
				GUI::SetNextItemWidth(-FLT_MIN);
				int currType = (int)data.GetType();
				if (data.GetType() == ScriptDataType::string && GUI::Input(this->guid + scriptName + "value" + innerId, "", data.GetValue()))
				{
					data.SetModified(true);
					project->SetDirty();
				}
				else if (data.GetType() == ScriptDataType::number)
				{
					auto value = data.GetValue();
					char* ref;

					double converted = strtod(value.c_str(), &ref);

					if (*ref)
					{
						data.SetValue("0");
						converted = 0;
					}

					if (GUI::Input(this->guid + scriptName + "value" + innerId, converted))
					{
						project->SetDirty();
						data.SetValue(std::to_string(converted));
						data.SetModified(true);
					}
				}
				else if (data.GetType() == ScriptDataType::boolean)
				{
					int currTypeBool;
					if (data.GetValue() == "0")
						currTypeBool = 0;
					else if (data.GetValue() == "1")
						currTypeBool = 1;
					else
					{
						currTypeBool = 1;
						data.SetValue("1");
						data.SetModified(true);
					}

					if (GUI::ComboBox(this->guid + scriptName + "type_bool" + innerId, { "false", "true" }, currTypeBool))
					{
						project->SetDirty();
						data.SetValue(std::to_string(currTypeBool));
						data.SetModified(true);
					}
				}
				else if (data.GetType() == ScriptDataType::button)
				{
					int currTypeBool;
					if (data.GetValue() == "0")
						currTypeBool = 0;
					else if (data.GetValue() == "1")
						currTypeBool = 1;
					else
					{
						currTypeBool = 0;
						data.SetValue("0");
						data.SetModified(true);
					}

					GUI::Push(this->guid + scriptName + "type_bool" + innerId);
					bool clicked = GUI::Button("Click me");
					GUI::Pop();

					if (clicked && project->GetState() == ProjectState::Running)
					{
						data.SetValue("1");
						data.SetModified(true);
					} 
					else
					{
						data.SetValue("0");
						data.SetModified(true);
					}
				}

				GUI::NextColumn();
		
				if (project->GetState() == ProjectState::Idle)
				{
					if (GUI::ImageButton(this->guid + "remove_script_data" + innerId, GUI::GetIcon("remove_data.png")))
					{
						project->SetDirty();
						dataToRemove = data.GetName();
					}

					if (GUI::IsCurrentItemHovered())
					{
						GUI::BeginHintWindow();
						GUI::Text("Remove script variable");
						GUI::EndHintWindow();
					}

					GUI::ContinueSameLine();
				}

				if (GUI::ImageButton(this->guid + "up_script_data" + innerId, GUI::GetIcon("up.png")))
				{
					moveUp = false;
					indexToMove = id;
				}

				if (GUI::IsCurrentItemHovered())
				{
					GUI::BeginHintWindow();
					GUI::Text("Move up script variable");
					GUI::EndHintWindow();
				}

				GUI::ContinueSameLine();

				if (GUI::ImageButton(this->guid + "down_script_data" + innerId, GUI::GetIcon("down.png")))
				{
					moveUp = true;
					indexToMove = id;
				}

				if (GUI::IsCurrentItemHovered())
				{
					GUI::BeginHintWindow();
					GUI::Text("Move down script variable");
					GUI::EndHintWindow();
				}

				id++;
			}

			if(dataToRemove != "")
				script->RemoveScriptData(dataToRemove);

			if (indexToMove != -1)
			{
				auto& data = script->GetScriptData();
				auto diff = moveUp ? indexToMove + 1 : indexToMove - 1;

				if (indexToMove >= 0 && indexToMove < data.size() && diff >= 0 && diff < data.size())
				{
					auto current = data[diff];
					data[diff] = data[indexToMove];
					data[indexToMove] = current;
				}
			}

			GUI::Unident(16);
			GUI::EndTable();
		}

		GUI::Unident(8);
		GUI::SetFontScale(1);

		// Pop up to add script data into script
		if (GUI::BeginPopUp(this->guid + "scripts_data_pop_up" + scriptName))
		{
			GUI::Text("Name: ");
			GUI::ContinueSameLine();
			GUI::Input(this->guid + "script_data_name", this->scriptDataName);
			GUI::Text("Type: ");
			GUI::ContinueSameLine();
			GUI::ComboBox(this->guid + "script_data_type", { "boolean", "number", "string", "button"}, this->scriptDataType);

			if (GUI::Button("Add"))
			{
				script->AddScriptData(ScriptData(scriptDataName, "0", (ScriptDataType)this->scriptDataType));

				project->SetDirty();
				GUI::CloseCurrentPopUp();
			}

			GUI::EndPopUp();
		}
	}
}}

