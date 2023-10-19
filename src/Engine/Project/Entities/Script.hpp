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
		/// Data used in script.
		/// </summary>
		std::vector<ScriptData> datas;

		/// <summary>
		/// If the script was started
		/// (used to know if destroy function needs to be called)
		/// </summary>
		bool isStarted;

		/// <summary>
		/// If the script have failed to be found (used in editor)
		/// </summary>
		bool haveWarningInLoad;

		/// <summary>
		/// If the engine should follow its script data and update it (used in editor only)
		/// </summary>
		bool updateScriptData = false;

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

		void SetState(ScriptState state);
		ScriptState GetState() const;

		void AddScriptData(ScriptData data);
		void RemoveScriptData(const std::string& name);
		void SetScriptData(std::vector<ScriptData>& data);
		std::vector<ScriptData>& GetScriptData();

		bool IsStarted() const;

		bool HaveWarningToLoad();
		void MarkAsFailedToLoad();

		void SetUpdateScriptData(bool value);
		bool GetUpdateScriptData() const;

		static int GetCurrentScriptsCount();
	};
}}}