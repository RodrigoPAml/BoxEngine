#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	using namespace Engine;

	class ScriptDebugger : public Layout
	{
	private:
		std::string guid = Utils::Directory::NewGuid();

		bool focused = false;
		bool open = false;
		bool configured = false;

		std::string goId;
	public:
		ScriptDebugger() = default;
		~ScriptDebugger() = default;

		void SetOpen(bool val);
		void Update();
		bool IsFocused() const;
		void SetGo(std::string goId);
	private:
		void PrintTable(lua_State* L, int index, const std::string& key);
		void PrintPrimitive(lua_State* L, int index);
	};
}}
