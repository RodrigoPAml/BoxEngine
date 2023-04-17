#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <BoxEngine.hpp>

static BoxEngine::Editor::ProjectManager* OpenProjectManager()
{
	using namespace BoxEngine::Editor;

	ProjectManager* manager = new ProjectManager();

	manager->Awake();
	manager->Start();
	manager->Update();
	manager->Destroy();

	return manager;
}

int main(int argc, char* argv[])
{
	using namespace BoxEngine::Window;
	using namespace BoxEngine::GPU;
	using namespace BoxEngine::Debug;
	using namespace BoxEngine::Project;
	using namespace BoxEngine::Utils;
	using namespace BoxEngine::Editor;

	auto manager = OpenProjectManager();

	ProjectPtr project = manager->GetProject();
	delete manager;
	
	if (project == nullptr)
		return 0;
	
	Project::SetCurrentProject(project);

	EditorPtr editor = EditorPtr(new Editor());
	editor->SetCurrentEditor(editor);
	editor->Awake();

	project->Load();

	Window::Init();
	Window::Maximize();
	Window::SetIcons({ ImagePtr(new Image(Directory::GetResourcePath() + "/icons/settings.png"))});

	editor->Start();

	while(Window::ShouldRun())
	{	
		Framebuffer::ActiveDefault();
		Framebuffer::SetClearModes({ ClearMode::COLOR, ClearMode::DEPTH });
		Framebuffer::Clear({0.0f, 0.0f, 0.0f, 0.0f});
		
		editor->Update();

		project->SetScreenLimits(editor->GetTopStartPoint(), editor->GetBottomEndPoint());
		project->Execute();

		Window::SwapAndPollEvents();
	}

	editor->Destroy();
	Window::Destroy();

	return 0;
}