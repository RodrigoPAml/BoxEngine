#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {
	
	using namespace Modules;

	class Project;
	typedef std::shared_ptr<Project> ProjectPtr;

	/// <summary>
	/// Represents a loaded project;
	/// </summary>
	class Project
	{
	private:
		/// <summary>
		/// Project name
		/// </summary>
		std::string name;

		/// <summary>
		/// Project path 
		/// </summary>
		std::string path;

		/// <summary>
		/// If project is modified.
		/// </summary>
		bool isModified = false;

		/// <summary>
		/// Go Manager.
		/// </summary>
		GoManagerPtr goManager = nullptr;

		/// <summary>
		/// Script Manager.
		/// </summary>
		ScriptManagerPtr scriptManager = nullptr;

		/// <summary>
		/// Project state
		/// </summary>
		ProjectState state = ProjectState::Idle;

		/// <summary>
		/// Project Mode
		/// </summary>
		ProjectMode mode = ProjectMode::PlayMode;

		/// <summary>
		/// Global reference to this project.
		/// </summary>
		static std::weak_ptr<Project> current;

		/// <summary>
		/// Holds the project data
		/// </summary>
		ProjectData data;
	public:
		// Create, Save and Load
		void Create();
		void Save();
		void LoadFrom(const std::string& path);
		void Load();

		// Modifications Control
		void SetDirty();
		bool isDirty() const;

		// Project Name
		void SetName(const std::string& name);
		std::string GetName() const;

		// Paths Localization
		void SetPath(const std::string& path);
		std::string GetBasePath() const;
		std::string GetAssetsPath() const;
		std::string GetLogsPath() const;
		std::string GetProjectSettingsPath() const;

		// Get/Set the draw box limits (editor calculate this)
		void SetScreenLimits(glm::vec2 topLeft, glm::vec2 bottomRight);
		glm::vec4 GetScreenLimits() const;

		// Execution control
		ProjectState GetState() const;
		ProjectMode GetMode() const;
		void SetMode(ProjectMode mode);

		void Start();
		void Stop();
		void Reload();
		void Execute();
		void StopThenStart();

		// Global References
		static ProjectPtr GetCurrentProject();
		static void SetCurrentProject(ProjectPtr project);

		// Funtions for Editor
		std::vector<std::string>& GetScriptNamesForEditor() const;
		void LoadScriptNameListForEditor() const;

		// Crud for gos 
		GameObjectPtr AddGameObject(const std::string& name, bool active, const std::string& fatherId = "");
		bool DestroyGameObject(const std::string& id);
		GameObjectPtr GetGameObject(const std::string& id);
		std::string DuplicateGo(const std::string& goId, const std::string& fatherId = "");
		void ChangeGoFather(const std::string& goId, const std::string& fatherId = "");
		void ChangeGoPosition(const std::string& goId, int displacement);
		std::vector<std::string> GetGosOfScripts(const std::string& scriptName);

		// Crud for scripts
		bool AddScript(const std::string& goId, const std::string& scriptName);
		bool DestroyScript(const std::string& goId, const std::string& scriptName, bool remove);
		void ChangeScriptPosition(const std::string& goId, const std::string& scriptName, int displacement);
		void ChangeScriptPositionByIndex(const std::string& goId, const std::string& scriptName, int index);
		bool PreLoadScripts(const std::string& goId);

		// Get gos root
		std::vector<GameObjectPtr> GetGosFromRoot() const;
		// Get all gos
		std::vector<GameObjectPtr> GetAllGos() const;

		// Project information
		int GetCurrentFPS();
		double GetCurrentFrameTime();
		void CalculateMetrics();
		int GetStackSize();
		std::unordered_map<long, GPU::TexturePtr> GetTextures();
	private:
		// Plan execution of scripts and gos
		void PlanExecution(const std::vector<GameObjectPtr>& gos, std::vector<GoExecution>& executions);
		
		// Plan destruction of scripts and gos
		void PlanExecutionToDestroy(const std::vector<GameObjectPtr> gos, std::vector<GoExecution>& executions);

		// Execute plans
		bool Execute(const std::vector<GoExecution>& executions);
	};
}}}