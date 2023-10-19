#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Input {

	/// <summary>
	/// A class to read the mouse input.
	/// This class is a Singleton.
	/// </summary>
	class Mouse
	{
		friend class Window::Window;
	private:
		/// <summary>
		/// The mouse last saved position.
		/// Used to calculate mouse delta.
		/// </summary>
		glm::vec<2, int> lastPosition;

		/// <summary>
		/// The frame scroll of the mouse.
		/// </summary>
		float scroll;

		/// <summary>
		/// If the mouse is inside the display
		/// </summary>
		bool isInsideWindow;

		/// <summary>
		/// Callbacks for mouse events notification.
		/// </summary>
		std::map<std::string, MouseButtonCallback> mouseButtonCallbacks;
		std::map<std::string, MousePositionCallback> mousePositionCallbacks;
		std::map<std::string, MouseScrollCallback> mouseScrollCallbacks;
		std::map<std::string, MouseEnterWindowCallback> mouseEnterWindowCallbacks;

		/// <summary>
		/// Reference to current GLFW Window in use.
		/// </summary>
		GLFWwindow* windowPtr;
	public:
		/// <summary>
		/// Set callbacks to recieve mouse events.
		/// </summary>
		static void RegisterMouseButtonCallback(const std::string& identifier, MouseButtonCallback callback);
		static void RegisterMousePositionCallback(const std::string& identifier, MousePositionCallback callback);
		static void RegisterMouseScrollCallback(const std::string& identifier, MouseScrollCallback callback);
		static void RegisterMouseEnterWindowCallback(const std::string& identifier, MouseEnterWindowCallback callback);

		/// <summary>
		/// Remove callbacks of mouse events.
		/// </summary>
		static void RemoveMouseButtonCallback(const std::string& identifier);
		static void RemoveMousePositionCallback(const std::string& identifier);
		static void RemoveMouseScrollCallback(const std::string& identifier);
		static void RemoveMouseEnterWindowCallback(const std::string& identifier);

		/// <summary>
		/// Get the current state of some mouse button.
		/// </summary>
		static InputAction GetMouseButtonState(const MouseButton button);

		/// <summary>
		/// Returns the current mouse position.
		/// </summary>
		static glm::vec<2, int> GetMousePosition(bool correctY = true);

		/// <summary>
		/// Returns the current mouse delta.
		/// </summary>
		static glm::vec<2, int> GetMouseVariation();

		/// <summary>
		/// Sets the mouse visualization mode.
		/// </summary>
		void SetMouseMode(const MouseMode mode);

		/// <summary>
		/// Get the mouse scroll.
		/// Based on current frame.
		/// </summary>
		float GetScroll();

		/// <summary>
		/// Get if the mouse is inside the window.
		/// </summary>
		bool IsMouseInsideWindow();
	private:
		Mouse() {};
		Mouse(Mouse const&);

		/// <summary>
		/// Returns current instance.
		/// </summary>
		static Mouse& Instance();

		/// <summary>
		/// State control.
		/// </summary>
		void Init(GLFWwindow* windowPtr);
		void Release();

		/// <summary>
		/// Callbacks to recieve events directly from GLFW.
		/// Internal usage.
		/// </summary>
		static void MasterCursorEnterWindow(GLFWwindow* window, int entered);
		static void MasterCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void MasterMouseButtonCallback(GLFWwindow* window, int button, int action, int mod);
		static void MasterScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};
}}}