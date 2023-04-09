#include <BoxEngine.hpp>
#include "Mouse.hpp"

namespace BoxEngine {
namespace Input {

	void Mouse::RegisterMouseButtonCallback(const std::string& identifier, MouseButtonCallback callback)
	{
		if(callback == nullptr)
			Instance().mouseButtonCallbacks[identifier] = callback;
	}

	void Mouse::RegisterMousePositionCallback(const std::string& identifier, MousePositionCallback callback)
	{
		if(callback == nullptr)
			Instance().mousePositionCallbacks[identifier] = callback;
	}

	void Mouse::RegisterMouseScrollCallback(const std::string& identifier, MouseScrollCallback callback)
	{
		if(callback == nullptr)
			Instance().mouseScrollCallbacks[identifier] = callback;
	}

	void Mouse::RegisterMouseEnterWindowCallback(const std::string& identifier, MouseEnterWindowCallback callback)
	{
		if(callback == nullptr)
			Instance().mouseEnterWindowCallbacks[identifier] = callback;
	}

	void Mouse::RemoveMouseButtonCallback(const std::string& identifier)
	{
		auto& instance = Instance();

		if(instance.mouseButtonCallbacks.contains(identifier))
			instance.mouseButtonCallbacks.erase(identifier);
	}

	void Mouse::RemoveMousePositionCallback(const std::string& identifier)
	{
		auto& instance = Instance();

		if(instance.mousePositionCallbacks.contains(identifier))
			instance.mousePositionCallbacks.erase(identifier);
	}

	void Mouse::RemoveMouseScrollCallback(const std::string& identifier)
	{
		auto& instance = Instance();

		if(instance.mouseScrollCallbacks.contains(identifier))
			instance.mouseScrollCallbacks.erase(identifier);
	}

	void Mouse::RemoveMouseEnterWindowCallback(const std::string& identifier)
	{
		auto& instance = Instance();

		if(instance.mouseEnterWindowCallbacks.contains(identifier))
			instance.mouseEnterWindowCallbacks.erase(identifier);
	}

	InputAction Mouse::GetMouseButtonState(const MouseButton button)
	{
		return (InputAction)glfwGetMouseButton(Instance().windowPtr, (int)button);
	}

	glm::vec<2, int> Mouse::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(Instance().windowPtr, &xpos, &ypos);

		return {xpos, ypos};
	}

	glm::vec<2, int> Mouse::GetMouseVariation()
	{
		return Instance().lastPosition -  GetMousePosition();
	}

	void Mouse::SetMouseMode(const MouseMode mode)
	{
		glfwSetInputMode(Instance().windowPtr, GLFW_CURSOR, (int)mode);
	}

	float Mouse::GetScroll()
	{
		auto& mouse = Instance();

		auto& tempScroll = mouse.scroll;

		mouse.scroll = 0;

		return tempScroll;
	}

	bool Mouse::IsMouseInsideWindow()
	{
		return Instance().isInsideWindow;
	}

	Mouse& Mouse::Instance()
	{
		static Mouse* instance = new Mouse();

		return *instance;
	}

	void Mouse::Init(GLFWwindow* windowPtr)
	{
		this->windowPtr = windowPtr;

		this->mouseButtonCallbacks.clear();
		this->mousePositionCallbacks.clear();
		this->mouseScrollCallbacks.clear();
		this->mouseEnterWindowCallbacks.clear();

		glfwSetScrollCallback(windowPtr, MasterScrollCallback);
		glfwSetCursorEnterCallback(windowPtr, MasterCursorEnterWindow);
		glfwSetMouseButtonCallback(windowPtr, MasterMouseButtonCallback);
		glfwSetCursorPosCallback(windowPtr, MasterCursorPositionCallback);

		this->lastPosition = { 0.0f, 0.0f };
		this->scroll  = 0;
		this->isInsideWindow = false;

		Debug::Logging::Log("[Mouse]: Initialized", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	void Mouse::Release()
	{
		this->mouseButtonCallbacks.clear();
		this->mousePositionCallbacks.clear();
		this->mouseScrollCallbacks.clear();
		this->mouseEnterWindowCallbacks.clear();

		glfwSetScrollCallback(this->windowPtr, nullptr);
		glfwSetCursorEnterCallback(this->windowPtr, nullptr);
		glfwSetCursorPosCallback(this->windowPtr, nullptr);
		glfwSetMouseButtonCallback(this->windowPtr, nullptr);

		this->lastPosition = { 0.0f, 0.0f };
		this->scroll = 0;
		this->isInsideWindow = false;
		this->windowPtr = nullptr;

		Debug::Logging::Log("[Mouse]: Released", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	void Mouse::MasterCursorEnterWindow(GLFWwindow* window, int entered)
	{
		auto& mouse = Instance();

		mouse.isInsideWindow = (bool)entered;

		for(auto callback : mouse.mouseEnterWindowCallbacks)
			callback.second((bool)entered);
	}

	void Mouse::MasterCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		auto& mouse = Instance();

		for(auto callback : mouse.mousePositionCallbacks)
			callback.second({ xpos, ypos });
	}

	void Mouse::MasterMouseButtonCallback(GLFWwindow* window, int button, int action, int mod)
	{
		auto& mouse = Instance();

		for(auto callback : mouse.mouseButtonCallbacks)
			callback.second((MouseButton)button, (InputAction)action, (InputModifier)mod);
	}

	void Mouse::MasterScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		auto& mouse = Instance();

		mouse.scroll += yoffset;

		for(auto callback : mouse.mouseScrollCallbacks)
			callback.second(yoffset);
	}
}}
