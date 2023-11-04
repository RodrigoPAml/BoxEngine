#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {

	/// <summary>
	/// Represents the data inputed to script
	/// </summary>
	class ScriptData
	{
	private:
		// The name of the data
		std::string name;

		// The value of the data 
		std::string value;

		// The value type
		ScriptDataType type;

		// If data is modified in editor   
		bool isModified;

		// If this data must be showed in editor to edit
		bool showInEditor;

		// If this data should persist when saved
		bool persist;
	public:
		ScriptData(std::string name, std::string value, ScriptDataType type);

		void SetName(const std::string& name);
		std::string& GetName();

		void SetValue(const std::string& value);
		std::string& GetValue();

		void SetType(const ScriptDataType type);
		ScriptDataType& GetType();

		void SetModified(const bool value);
		bool IsModified();

		void SetPersist(const bool value);
		bool IsPersist();

		void SetShowEditor(const bool value);
		bool IsShowEditor();
	};
}}}