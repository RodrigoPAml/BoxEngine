#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	class Inspector : public Layout
	{
	private:
		bool reset = true;
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
		Project::GameObjectWeakPtr go;
		std::string goName = "";
		std::string scriptDataName = "";
		int scriptDataType = 0;
		bool goActive = "";
		int selectedScript = -1;
		int selected = -1;
	public:
		Inspector() = default;
		~Inspector() = default;

		void Start();
		void Update();
		void InspectProjectSettings();
		void InspectGo(Project::GameObjectWeakPtr go);

		void SetMinY(float value);
		float GetMinX() const;
	private:
		// Settings inspection
		void ShowProjectSettings();

		// Go inspection
		void ShowGoEditor();
		void ShowGoEditorHeader(Project::GameObjectPtr go);
		void ShowGoEditorScripts(Project::GameObjectPtr go);
		void ShowGoEditorScriptsData(Project::ScriptPtr script);
	};
}}
