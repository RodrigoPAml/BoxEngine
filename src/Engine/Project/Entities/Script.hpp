#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {

	class Script;
	typedef std::shared_ptr<Script> ScriptPtr;
	typedef std::weak_ptr<Script> ScriptWeakPtr;

	/// <summary>
	/// Represents an script.
	/// </summary>
	class Script
	{
		friend class Project;
	private:
		/// <summary>
		/// Unique Identifier is the path.
		/// </summary>
		std::string path;

		/// <summary>
		/// Name should be unique.
		/// </summary>
		std::string name;

		/// <summary>
		/// The script state.
		/// </summary>
		ScriptState state;
		
		/// <summary>
		/// The script runmode
		/// </summary>
		RunMode mode = RunMode::Normal;

		/// <summary>
		/// Data used in script.
		/// </summary>
		std::vector<ScriptData> datas;

		/// <summary>
		/// Scripts data that can't been show on editor or persisted in the project file
		/// </summary>
		std::vector<std::string> cantPersistDatas;
		std::vector<std::string> cantShowDatas;

		/// <summary>
		/// If the script was started
		/// (used to know if destroy function needs to be called)
		/// </summary>
		bool isStarted;

		/// <summary>
		/// If the script data was initialized
		/// (When you destroy a script before it initializing)
		/// </summary>
		bool isLoaded = false;

		/// <summary>
		/// If the script is active
		/// </summary>
		bool active;

		/// <summary>
		/// If the script have failed to be found (used in editor)
		/// </summary>
		bool haveWarningInLoad;

		/// <summary>
		/// If the engine should follow its script data and update it (used in editor only)
		/// </summary>
		bool updateScriptData = false;

		/// <summary>
		/// If this script can persist at runtime
		/// </summary>
		bool persist = true;

		/// <summary>
		/// If the script should removed from the go after destroyed
		/// </summary>
		bool removeWhenDestroyed = false;

		/// <summary>
		/// Total current existent scripts
		/// </summary>
		static int Total;
	public:
		Script(std::string name);
		~Script();

		std::string GetName() const;

		void SetPath(const std::string& path);
		std::string GetPath() const;

		void SetActive(const bool active);
		bool GetActive() const;

		void SetState(ScriptState state);
		ScriptState GetState() const;

		void SetRunMode(RunMode mode);
		RunMode GetRunMode() const;

		void AddScriptData(ScriptData data);
		void RemoveScriptData(const std::string& name);
		void SetScriptData(std::vector<ScriptData>& data);
		std::vector<ScriptData>& GetScriptData();

		void AddDataNotShowed(const std::string& dataName);
		void RemoveDataNotShowed(const std::string& dataName);
		bool HaveDataNotShowed(const std::string& dataName);

		void AddDataNotPersisted(const std::string& dataName);
		void RemoveDataNotPersisted(const std::string& dataName);
		bool HaveDataNotPersisted(const std::string& dataName);

		bool IsStarted() const;
		bool IsLoaded() const;

		bool HaveWarningToLoad();
		void MarkAsFailedToLoad();

		void SetUpdateScriptData(bool value);
		bool GetUpdateScriptData() const;

		bool IsPersisted() const;
		void SetPersisted(bool value);

		bool IsRemovedAfterDestroyed() const;
		void SetRemovedAfterDestroyed(bool value);

		static int GetCurrentScriptsCount();
	};
}}}