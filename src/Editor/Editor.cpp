#include <BoxEngine.hpp>
#include "Editor.hpp"

namespace BoxEngine {
namespace Editor {

	std::weak_ptr<Editor> Editor::current;

	void Editor::Awake()
	{
		this->bottomBar.Awake();
		this->topBar.Awake();
		this->inspector.Awake();
		this->gameTree.Awake();
	}

	void Editor::Start()
	{
		this->bottomBar.Start();
		this->topBar.Start();
		this->inspector.Start();
		this->gameTree.Start();

		Debug::Logging::Log(
			"[Editor]: Initialized",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);
	}

	void Editor::Update()
	{
		using namespace BoxEngine::Window;

		GUI::BeginFrame();

		this->topBar.Update();
		this->bottomBar.Update();

		this->inspector.SetMinY(this->bottomBar.GetMinY());
		this->inspector.Update();

		this->gameTree.SetMinY(this->bottomBar.GetMinY());
		this->gameTree.Update();

		GUI::EndFrame();
	}

	void Editor::Destroy()
	{
		this->bottomBar.Destroy();
		this->topBar.Destroy();
		this->inspector.Destroy();
		this->gameTree.Destroy();

		Debug::Logging::Log(
			"[Editor]: Released",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);
	}

	void Editor::InspectProjectSettings()
	{
		this->inspector.InspectProjectSettings();
	}

	void Editor::ClearLogs()
	{
		this->bottomBar.ClearLogs();
	}

	void Editor::InspectGo(Project::GameObjectWeakPtr go)
	{
		this->inspector.InspectGo(go);
	}

	glm::vec2 Editor::GetTopStartPoint() const
	{
		// Min x, Min y
		return glm::vec2(this->gameTree.GetMaxX(), Window::Window::GetSize().y - this->bottomBar.GetMinY());
	}

	glm::vec2 Editor::GetBottomEndPoint() const
	{
		// Max x, Max y
		double maxY = Window::Window::GetSize().y - TOPBAR_Y;

		if (maxY < 0)
			maxY = 0;

		return glm::vec2(this->inspector.GetMinX(), maxY);
	}

	EditorPtr Editor::GetCurrentEditor()
	{
		if (current.expired())
			return nullptr;
		else
			return current.lock();
	}

	void Editor::SetCurrentEditor(EditorPtr editor)
	{
		current = editor;
	}
}}