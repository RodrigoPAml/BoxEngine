#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Window {
	
	/// <summary>
	/// Callbacks for window events.
	/// </summary>
	typedef std::function<void(glm::vec<2, int>)> ResizeWindowCallback;
	typedef std::function<void(glm::vec<2, int>)> RepositionWindowCallback;
	typedef std::function<void(bool)> MaximizeWindowCallback;
	typedef std::function<void(bool)> MinimizeWindowCallback;
	typedef std::function<void(bool)> FocusWindowCallback;
	typedef std::function<void(void)> CloseWindowCallback;
}}