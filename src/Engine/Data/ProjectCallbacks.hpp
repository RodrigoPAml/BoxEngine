#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {

	/// <summary>
	/// Represents a pointer to function, to create a GO.
	/// </summary>
	typedef std::function<void(const std::string&, const std::string&, bool, const std::vector<ScriptPtr>&, const std::string&)> CreateGoFunction;
}}}