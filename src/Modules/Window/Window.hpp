#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Window {

	/// <summary>
	/// Class to manager the window.
	/// This class is a singleton.
	/// </summary>
	class Window
	{
	private:
		/// <summary>
		/// GLFW window reference.
		/// </summary>
		GLFWwindow* windowPtr;

		/// <summary>
		/// Window current configuration.
		/// </summary>
		WindowConfiguration config;

		/// <summary>
		/// Window states.
		/// </summary>
		bool isInitialized;
		bool isMinimized;
		bool isFullscreen;
		bool isHide;
		bool isFocused;
			
		/// <summary>
		/// Window event callbacks.
		/// </summary>
		ResizeWindowCallback resizeWindowCallback;
		RepositionWindowCallback repositionWindowCallback;
		MaximizeWindowCallback maximizeWindowCallback;
		MinimizeWindowCallback minimizeWindowCallback;
		CloseWindowCallback closeWindowCallback;
		FocusWindowCallback focusWindowCallback;
	public:
		/// <summary>
		/// Initialize window with GLFW, OpenGL and GLAD.
		/// </summary>
		static void Init(const WindowConfiguration& windowConfig = WindowConfiguration());

		/// <summary>
		/// Destroy window with GLFW, OpenGL and GLAD.
		/// </summary>
		static void Destroy();

		/// <summary>
		/// Returns if the main loop of the window should continue.
		/// </summary>
		/// <returns></returns>
		static bool ShouldRun();

		static void Resize(const glm::vec2& newSize);
		static glm::vec2 GetSize();

		static void SetPosition(const glm::vec2& pos);
		static glm::vec2 GetPosition();

		static std::string GetName();
		static void SetName(const std::string& title);

		static void SetFullscreen();
		static void RemoveFullscreen(const glm::vec2& newSize, const glm::vec2& newPos);

		static void Hide();
		static void Show();

		static void Maximize();
		static void Minimize();
		static void Restore();
		static void Close();

		static void RequestAttention();
		static void SwapAndPollEvents();

		/// <summary>
		/// Set window events callbacks.
		/// </summary>
		static void SetResizeWindowCallback(const ResizeWindowCallback callback);
		static void SetRepositionWindowCallback(const RepositionWindowCallback callback);
		static void SetMaximizeWindowCallback(const MaximizeWindowCallback callback);
		static void SetMinimizeWindowCallback(const MinimizeWindowCallback callback);
		static void SetCloseWindowCallback(const CloseWindowCallback callback);
		static void SetFocusWindowCallback(const FocusWindowCallback callback);

		/// <summary>
		/// Get Window States.
		/// </summary>
		static bool IsMinimized();
		static bool IsHide();
		static bool IsFullscreen();
		static bool IsFocused();

		/// <summary>
		/// Sets the window icons, the most suitable is used.
		/// </summary>
		static void SetIcons(const std::vector<Utils::ImagePtr>& icons);

		static glm::vec2 GetScreenLimits();
	private:
		Window() {};
		Window(Window const&);

		/// <summary>
		/// Returns current instance.
		/// </summary>
		/// <returns></returns>
		static Window& Instance();

		/// <summary>
		/// To recieve events directly from GLFW.
		/// Internal usage.
		/// </summary>
		static void WindowResizeCallback(GLFWwindow* window, int width, int height);
		static void WindowCloseCallback(GLFWwindow* window);
		static void WindowPositionCallback(GLFWwindow* window, int xpos, int ypos);
		static void WindowMaximizeCallback(GLFWwindow* window, int maximized);
		static void WindowMinimizeCallback(GLFWwindow* window, int maximized);
		static void WindowFocusCallback(GLFWwindow* window, int focused);
	};
}}}
