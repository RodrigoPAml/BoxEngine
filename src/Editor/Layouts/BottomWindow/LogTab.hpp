#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	/// <summary>
	/// Represents log tab in bottom window.
	/// </summary>
	class LogTab : public Layout
	{
	private:
		bool showWarnings = true;
		bool showErrors = true;
		bool showMessages = true;

		bool showEngineInternals = false;
		bool showEngine = true;
		bool showGlfw = true;
		bool showOpenGl = true;
		bool showUserGenerated = true;
		bool lockDown = true;
		bool allowClear = true;

		bool isFilterMenuOpen = false;
		std::string filterMessage = "";
		std::string guid = "";

		glm::vec4 notificationColor = { 0.0f, 0.0f, 0.0f, 0.0f };
		glm::vec4 errorColor = { 1.0f, 0.0f, 0.0f, 0.5f };
		glm::vec4 warningColor = { 1.0f, 0.8f, 0.0f, 0.5f };

		std::vector<LogTabItem> logMessages;
		std::vector<Window::GUIListBoxItem> guiMessages;
		std::mutex mutexCallback;

		GPU::TexturePtr errorTexture = nullptr;
		GPU::TexturePtr notifyTexture = nullptr;
		GPU::TexturePtr warningTexture = nullptr;
		GPU::TexturePtr filterTexture = nullptr;
	public:
		LogTab() = default;
		~LogTab() = default;

		void Awake();
		void Start();
		void Update();
		void Destroy();
		void ClearLogs();

		void PopulateLog();
		void LogCallback(
			const Utils::DateTime& datetime,
			const std::string& message,
			const Debug::LogSeverity severity,
			const Debug::LogOrigin origin,
			const std::unordered_map<std::string, std::string>& additionalData,
			const std::string& function,
			const std::string& file
		);
	private:
		void DrawTop();
		void DrawFilterPopUp();
	};
}}