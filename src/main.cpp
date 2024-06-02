#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <BoxEngine.hpp>

static BoxEngine::Editor::ProjectManager* OpenProjectManager(bool external)
{
	using namespace BoxEngine::Editor;

	ProjectManager* manager = new ProjectManager();

	manager->Awake();
	manager->Start();

	if (!external)
		manager->Update();

	manager->Destroy();

	return manager;
}

int main(int argc, char* argv[])
{
	using namespace BoxEngine::Modules::Window;
	using namespace BoxEngine::Modules::GPU;
	using namespace BoxEngine::Modules::Debug;
	using namespace BoxEngine::Engine::Project;
	using namespace BoxEngine::Modules::Utils;
	using namespace BoxEngine::Editor;

	using Project = BoxEngine::Engine::Project::Project;
	using Window = BoxEngine::Modules::Window::Window;

	// Se projeto ta sendo carregado por argumento
	bool external = argc > 1;
	
	// Se deve ativar o editor quando abrindo por argumento, basta passar qualquer segundo argumento
	bool withEditor = argc > 2;

	ProjectPtr project = nullptr;
	auto manager = OpenProjectManager(external);

	if (external)
	{
		auto projectName = argv[1];

		project = ProjectPtr(new Project());
		project->LoadFrom(projectName);
	}
	else
		project = manager->GetProject();

	delete manager;
	
	if (project == nullptr)
		return 0;
	
	Project::SetCurrentProject(project);

	EditorPtr editor = nullptr;
	if (!external || withEditor)
	{
		editor = EditorPtr(new Editor());
		editor->SetCurrentEditor(editor);
		editor->Awake();
	}

	project->Load();

	Window::Init();
	Window::Maximize();
	Window::SetIcons({ ImagePtr(new Image(Directory::GetResourcePath() + "/icons/settings.png"))});

	if (editor)
		editor->Start();
	else
		project->Start();

	while(Window::ShouldRun())
	{	
		Framebuffer::ActiveDefault();
		Framebuffer::SetClearModes({ ClearMode::COLOR, ClearMode::DEPTH });
		Framebuffer::Clear({0.0f, 0.0f, 0.0f, 0.0f});
		
		project->Execute();

		if (editor)
		{
			Framebuffer::ActiveDefault();
			editor->Update();
			project->SetScreenLimits(editor->GetTopStartPoint(), editor->GetBottomEndPoint());
		}
		else 
			project->SetScreenLimits({0, 0}, Window::GetSize());

		Window::SwapAndPollEvents();
	}

	if(editor)
		editor->Destroy();
	
	Window::Destroy();

	return 0;
}