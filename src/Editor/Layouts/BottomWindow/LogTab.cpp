#include <BoxEngine.hpp>
#include "LogTab.hpp"

namespace BoxEngine {
namespace Editor {

	void LogTab::Awake()
	{
		using namespace std::placeholders;

		this->guid = Utils::Directory::NewGuid();

		Debug::Logging::RegisterLogCallback(
			this->guid,
			std::bind(&LogTab::LogCallback, this, _1, _2, _3, _4, _5, _6, _7)
		);
	}

	void LogTab::Start()
	{
		using GUI = BoxEngine::Window::GUI;

		this->errorTexture = GUI::GetIcon("error.png");
		this->warningTexture = GUI::GetIcon("warning.png");
		this->notifyTexture = GUI::GetIcon("message.png");
		this->filterTexture = GUI::GetIcon("filter.png");
	}

	void LogTab::DrawTop()
	{
		using namespace BoxEngine::Window;

		if (GUI::ImageButton(this->guid + "error_texture", this->errorTexture))
		{
			this->showErrors = !this->showErrors;
			this->PopulateLog();
		}

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text(this->showErrors ? "Hide errors" : "Show errors");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		if (GUI::ImageButton(this->guid + "warning_texture", this->warningTexture))
		{
			this->showWarnings = !this->showWarnings;
			this->PopulateLog();
		}

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text(this->showWarnings ? "Hide warnings" : "Show warnings");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		if (GUI::ImageButton(this->guid + "notify_texture", this->notifyTexture))
		{
			this->showMessages = !this->showMessages;
			this->PopulateLog();
		}

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text(this->showMessages ? "Hide notifications" : "Show notifications");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		if (GUI::ImageButton(this->guid + "filter_texture", this->filterTexture))
			this->isFilterMenuOpen = true;

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Manage filters");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine(10);

		if (GUI::Input(this->guid, this->filterMessage))
			this->PopulateLog();

		GUI::ContinueSameLine();

		if (GUI::ImageButton(this->guid + "down_log", GUI::GetIcon("down.png")))
			this->lockDown = !this->lockDown;

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text(this->lockDown ? "Unlock scroll" : "Lock scroll");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();


		if (GUI::ImageButton(this->guid + "lock_clear", GUI::GetIcon("clear_lock.png")))
			this->allowClear = !this->allowClear;

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text(this->allowClear ? "Disable log auto clear" : "Enable log auto clear");
			GUI::EndHintWindow();
		}

		GUI::ContinueSameLine();

		if (GUI::ImageButton(this->guid + "clear", GUI::GetIcon("clear.png")))
		{
			this->mutexCallback.lock();

			this->guiMessages.clear();
			this->logMessages.clear();

			this->mutexCallback.unlock();
		}

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Clear logs");
			GUI::EndHintWindow();
		}
	}

	void LogTab::DrawFilterPopUp()
	{
		using namespace BoxEngine::Window;

		if (this->isFilterMenuOpen)
		{
			this->isFilterMenuOpen = false;
			GUI::OpenPopUp(this->guid + "filter_option");
		}

		if (GUI::BeginPopUp(this->guid + "filter_option"))
		{
			bool changed = false;

			if (GUI::CheckBox(this->guid + "showEngine", this->showEngine))
				changed = true;
			GUI::ContinueSameLine();
			GUI::Text("Show engine logs");

			if (GUI::CheckBox(this->guid + "showEngineInternals", this->showEngineInternals))
				changed = true;
			GUI::ContinueSameLine();
			GUI::Text("Show internal engine logs");

			if (GUI::CheckBox(this->guid + "showGlfw", this->showGlfw))
				changed = true;
			GUI::ContinueSameLine();
			GUI::Text("Show GLFW logs");

			if (GUI::CheckBox(this->guid + "showOpenGl", this->showOpenGl))
				changed = true;
			GUI::ContinueSameLine();
			GUI::Text("Show OpenGl logs");

			if (GUI::CheckBox(this->guid + "showUserGenerated", this->showUserGenerated))
				changed = true;
			GUI::ContinueSameLine();
			GUI::Text("Show user generated logs");

			if (changed)
				this->PopulateLog();

			GUI::EndPopUp();
		}
	}

	void LogTab::Update()
	{
		using namespace BoxEngine::Window;
			
		this->DrawTop();

		this->mutexCallback.lock();
		GUI::ListBox(this->guid + "LogsList", this->guiMessages, "", this->lockDown);
		this->mutexCallback.unlock();

		this->DrawFilterPopUp();
	}

	void LogTab::Destroy()
	{
		Debug::Logging::RemoveLogCallback(this->guid);
	}

	void LogTab::ClearLogs()
	{
		if (!allowClear)
			return;

		this->mutexCallback.lock();
		this->logMessages.clear();
		this->guiMessages.clear();
		this->mutexCallback.unlock();
	}

	void LogTab::PopulateLog()
	{
		using namespace BoxEngine::Debug;
		using namespace BoxEngine::Window;

		this->mutexCallback.lock();

		if (this->logMessages.size() > 100000)
		{
			this->logMessages.clear();
			this->guiMessages.clear();
		}
		else
			this->guiMessages.clear();

		for (auto& item : this->logMessages)
		{
			if (this->filterMessage != "" && item.message.find(this->filterMessage) == -1)
				continue;

			if (!this->showErrors && item.severity == LogSeverity::Error)
				continue;
			if (!this->showWarnings && item.severity == LogSeverity::Warning)
				continue;
			if (!this->showMessages && item.severity == LogSeverity::Notify)
				continue;
			if (!this->showEngine && item.origin == LogOrigin::Engine)
				continue;
			if (!this->showEngineInternals && item.origin == LogOrigin::EngineInternal)
				continue;
			if (!this->showOpenGl && item.origin == LogOrigin::OpenGL)
				continue;
			if (!this->showGlfw && item.origin == LogOrigin::GLFW)
				continue;
			if (!this->showUserGenerated && item.origin == LogOrigin::UserGenerated)
				continue;

			glm::vec4 color = this->notificationColor;

			if (item.severity == LogSeverity::Error)
				color = this->errorColor;

			if (item.severity == LogSeverity::Warning)
				color = this->warningColor;

			this->guiMessages.push_back(GUIListBoxItem(item.message, color));
		}

		this->mutexCallback.unlock();
	}

	void LogTab::LogCallback(
		const Utils::DateTime& datetime,
		const std::string& message, 
		const Debug::LogSeverity severity, 
		const Debug::LogOrigin origin, 
		const std::unordered_map<std::string, std::string>& additionalData,
		const std::string& function, 
		const std::string& file
	)
	{
		using namespace BoxEngine::Window;
		using namespace BoxEngine::Debug;

		this->mutexCallback.lock();

		if (this->logMessages.size() > 100000)
		{
			this->logMessages.clear();
			this->guiMessages.clear();
		}

		glm::vec4 color = this->notificationColor;

		if(severity == LogSeverity::Error)
			color = this->errorColor;

		if (severity == LogSeverity::Warning)
			color = this->warningColor;
			
		GUIListBoxItem row = GUIListBoxItem(message, color, additionalData);
		LogTabItem item = LogTabItem(message, severity ,origin);
		
		this->logMessages.push_back(item);

		if (!this->showErrors && severity != LogSeverity::Error)
		{
			this->mutexCallback.unlock();
			return;
		}
		if (!this->showWarnings && severity != LogSeverity::Warning)
		{
			this->mutexCallback.unlock();
			return;
		}
		if (!this->showMessages && severity != LogSeverity::Notify)
		{
			this->mutexCallback.unlock();
			return;
		}
		if (this->filterMessage != "" && message.find(this->filterMessage) == -1)
		{
			this->mutexCallback.unlock();
			return;
		}
		if (!this->showEngine && origin == LogOrigin::Engine)
		{
			this->mutexCallback.unlock();
			return;
		}
		if (!this->showEngineInternals && origin == LogOrigin::EngineInternal)
		{
			this->mutexCallback.unlock();
			return;
		}
		if (!this->showOpenGl && origin == LogOrigin::OpenGL)
		{
			this->mutexCallback.unlock();
			return;
		}
		if (!this->showGlfw && origin == LogOrigin::GLFW)
		{
			this->mutexCallback.unlock();
			return;
		}
		if (!this->showUserGenerated && origin == LogOrigin::UserGenerated)
		{
			this->mutexCallback.unlock();
			return;
		}
		
		this->guiMessages.push_back(row);
		this->mutexCallback.unlock();
	}
}}

