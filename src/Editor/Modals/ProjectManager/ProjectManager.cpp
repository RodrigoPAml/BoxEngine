#include <BoxEngine.hpp>
#include "ProjectManager.hpp"

namespace BoxEngine {
namespace Editor {

	using namespace Modules;

	void ProjectManager::Awake()
	{
		this->startingPath = std::filesystem::current_path().string();

		auto logConfig = Debug::LoggingConfiguration();

		logConfig.logConsole = false;
		logConfig.logFile = false;
		logConfig.logCallback = false;

		Debug::Logging::SetConfiguration(logConfig);

		auto debugConfig = Debug::DebugConfiguration();

		debugConfig.enableGlfwDebugging = false;
		debugConfig.enableOpenGLDebugging = false;
		debugConfig.autoLogOpenGLErrors = false;
		debugConfig.autoLogGLFWErrors = false;

		Debug::Debugging::SetConfiguration(debugConfig);
	}

	void ProjectManager::Start()
	{
		using namespace Utils;

		GPU::Command::EnableVSync();

		this->guid = Utils::Directory::NewGuid();

		Window::Window::Init();
		Window::Window::SetIcons({ ImagePtr(new Image(Directory::GetResourcePath() + "/icons/settings.png")) });
		Window::Window::Maximize();

		Debug::Logging::Log(
			"[Project Manager]: Initialized",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);
	}

	void ProjectManager::Update()
	{
		using Window = Window::Window;
		using Project = Project::Project;

		using namespace Window;
		using namespace Project;
		using namespace GPU;
			
		Framebuffer::SetClearModes({ ClearMode::COLOR, ClearMode::DEPTH });

		while (Window::ShouldRun())
		{
			Framebuffer::Clear({ 0.25f, 0.25f, 0.25f, 0.0f });

			GUI::BeginFrame();

			// 1. Draw Menu bar
			if (GUI::BeginMainMenuBar())
			{
				if (GUI::BeginMenu("Project", !GUI::IsPopUpOpened(this->warningTitle)))
				{
					if (GUI::MenuItem("Create"))
					{
						this->currentPath = this->startingPath;
						this->currentFilter = this->currentProjectName =  "";
						this->isDialogOpen = this->isCreateMode = this->shouldResize =  true;
					}

					if (GUI::MenuItem("Load"))
					{
						this->currentPath = this->startingPath;
						this->isDialogOpen = this->shouldResize = true;
						this->currentFilter = "";
						this->isCreateMode = false;
					}

					if (GUI::BeginMenu("Load recents"))
					{
						for (auto path : LoadRecents())
						{
							this->currentPath = path;

							if (GUI::MenuItem(path))
							{
								try
								{
									this->project = ProjectPtr(new Project());
									this->project->LoadFrom(this->currentPath);

									this->warningContent = "Project loaded with success!";
									this->shouldOpenWarningModal = true;
									this->color = { 0, 1, 0 };
									WriteRecents(this->currentPath);
								}
								catch (const std::runtime_error& ex)
								{
									Debug::Logging::Log(
										ex.what(),
										Debug::LogSeverity::Error,
										Debug::LogOrigin::Engine
									);

									this->project = nullptr;
									this->warningContent = ex.what();
									this->shouldOpenWarningModal = true;
									this->color = { 1, 0, 0 };
								}
							}
						}

						GUI::EndMenu();
					}
				
					if (GUI::MenuItem("Exit"))
						Window::Close();

					GUI::EndMenu();
				}
				
				GUI::EndMainMenuBar();
			}
			
			// 2. File dialog
			if (this->isDialogOpen)
			{
				if (this->shouldResize)
				{
					GUI::SetNextWindowSize({ 600, 600 });
					this->shouldResize = false;
				}

				auto config = {GUIWindowFlags::AlwaysAutoResize,GUIWindowFlags::NoCollapse, GUIWindowFlags::AlwaysVerticalScrollbar};

				if (GUI::BeginWindow(this->isCreateMode ? "Create Project" : "Load Project", &this->isDialogOpen, config))
				{
					std::string selected = GUI::FileDialog(this->currentPath, this->currentFilter, this->isCreateMode, std::vector<std::string>({ ".boxproj" }));
					
					GUI::Separator();
						
					if (this->isCreateMode)
						this->DrawCreateProjectDialog();
					else
						this->DrawLoadProjectDialog(selected);

					GUI::EndWindow();
				}
			}

			// 3. Warning pop up
			if (this->shouldOpenWarningModal)
			{
				GUI::OpenPopUp(this->warningTitle);
				this->shouldOpenWarningModal = false;
			}

			if (GUI::MakeWarningPopUp(this->warningTitle, this->warningContent, this->color))
			{	
				if (this->project != nullptr)
				{
					this->shouldOpenProject = true;
					Window::Close();
				}
			}

			GUI::EndFrame();
			Window::SwapAndPollEvents();
		}
	}

	void ProjectManager::Destroy()
	{
		if (!this->shouldOpenProject)
			this->project = nullptr;

		using Window = Window::Window;
			
		Debug::Logging::Log(
			"[Project Manager]: Released",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		Window::Destroy();
	}

	Project::ProjectPtr ProjectManager::GetProject() const
	{
		return this->project;
	}

	void ProjectManager::DrawCreateProjectDialog()
	{
		using Window = Window::Window;
		using Project = Project::Project;

		using namespace Window;
		using namespace Project;

		GUI::Text("Project name:");
		GUI::ContinueSameLine();
		GUI::Input(this->guid, this->currentProjectName);
		GUI::ContinueSameLine();

		if (GUI::Button("Create"))
		{
			if (this->currentProjectName == "")
			{
				this->warningContent = "Please provide the project name";
				this->shouldOpenWarningModal = true;
				this->color = { 1, 0, 0 };
			}
			else if (Utils::Directory::Exists(this->currentPath + '/' + this->currentProjectName))
			{
				this->warningContent = "The folder for this project already exists";
				this->shouldOpenWarningModal = true;
				this->color = { 1, 0, 0 };
			}
			else
			{
				try
				{
					this->project = ProjectPtr(new Project());

					this->project->SetName(this->currentProjectName);
					this->project->SetPath(this->currentPath + "/" + this->currentProjectName);
					this->project->Create();

					this->warningContent = "Project created with success!";
					this->shouldOpenWarningModal = true;
					this->color = { 0, 1, 0 };
					this->isDialogOpen = false;

					WriteRecents(this->currentPath + "/" + this->currentProjectName);
				}
				catch (const std::runtime_error& ex)
				{
					Debug::Logging::Log(
						ex.what(),
						Debug::LogSeverity::Error,
						Debug::LogOrigin::Engine
					);

					this->project = nullptr;
					this->warningContent = ex.what();
					this->shouldOpenWarningModal = true;
					this->isDialogOpen = false;
					this->color = { 1, 0, 0 };
				}
			}
		}
	}

	void ProjectManager::DrawLoadProjectDialog(const std::string& filename)
	{
		using Window = Window::Window;
		using Project = Project::Project;

		using namespace Window;
		using namespace Project;

		GUI::SetFontScale(0.8);
		GUI::BulletText("Select the ");
		GUI::ContinueSameLine();
		GUI::ColoredText(".boxproj", { 0.3, 0.9, 0.3, 1 });
		GUI::ContinueSameLine();
		GUI::Text(" file to load project");
		GUI::SetFontScale(1);

		if (filename != "" && Utils::Directory::IsFile(filename))
		{
			this->shouldOpenWarningModal = true;
			this->isDialogOpen = false;

			try
			{
				this->project = ProjectPtr(new Project());
				this->project->LoadFrom(this->currentPath);

				this->warningContent = "Project loaded with success!";
				this->shouldOpenWarningModal = true;
				this->color = { 0, 1, 0 };
				this->isDialogOpen = false;

				WriteRecents(this->currentPath);
			}
			catch (const std::runtime_error& ex)
			{
				Debug::Logging::Log(
					ex.what(),
					Debug::LogSeverity::Error,
					Debug::LogOrigin::Engine
				);

				this->project = nullptr;
				this->warningContent = ex.what();
				this->shouldOpenWarningModal = true;
				this->isDialogOpen = false;
				this->color = { 1, 0, 0 };
			}
		}
	}
	
	std::vector<std::string> ProjectManager::LoadRecents()
	{
		std::ifstream inFile("recents.txt");
		std::vector<std::string> lines;
		std::string line;
		int lineCount = 0;

		if (inFile.is_open())
		{
			while (getline(inFile, line) && lineCount < 9)
			{
				lines.push_back(line);
				++lineCount;
			}

			inFile.close();
		}

		return lines;
	}

	void ProjectManager::WriteRecents(const std::string& path)
	{
		std::vector<std::string> lines = LoadRecents();
		std::ofstream outFile("recents.txt");

		if (outFile.is_open())
		{
			outFile << path << '\n';

			for (const auto& line : lines)
			{
				if(path != line)
					outFile << line << '\n';
			}

			outFile.close();
		}
	}
}}