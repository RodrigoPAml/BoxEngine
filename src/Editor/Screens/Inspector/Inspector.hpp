#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	using namespace Engine;

	class Inspector : public Layout
	{
	private:
		bool reset = true;
		bool focused = false;
		bool isInspectingProjectSettings = false;
		bool isInspectingGo = false;

		float minY = 0;
		float minX = 0;
		std::string guid = "";

		// Edit project settings variables
		std::string projectName = "";
		Debug::DebugConfiguration debugConfig;
		Debug::LoggingConfiguration loggingConfig;
		bool useSeverityLow = false;
		bool useSeverityMedium = false;
		bool useSeverityHigh = false;
		bool useSeverityNotification = false;

		// Edit go
		bool openAddScriptModal = false;

		std::string scriptFilter = "";
		std::string goId;
		std::string goName = "";
		std::string scriptDataName = "";
		int scriptDataType = 0;
		bool goActive = "";
		int selectedScript = -1;
		int selected = -1;

		ScriptDebugger debugger;
	public:
		Inspector() = default;
		~Inspector() = default;

		void Start();
		void Update();
		bool IsFocused();
		void InspectProjectSettings();

		void InspectGo(std::string goId);
		std::string GetInspectedGo();

		void SetMinY(float value);
		float GetMinX() const;
	private:
		// Settings inspection
		void ShowProjectSettings();

		// Go inspection
		void ShowGoEditor();
		void ShowGoEditorHeader(Project::GameObjectPtr go);
		void ShowGoEditorScripts(Project::GameObjectPtr go);
		void ShowGoEditorScriptsData(Project::GameObjectPtr go, Project::ScriptPtr script);
	};
}}
