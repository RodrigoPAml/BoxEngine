#pragma once
#include "BoxEngine.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {

	/// <summary>
	/// Represents part of the execution of a go.
	/// </summary>
	class GoExecution
	{
	private:
		/// <summary>
		/// Execution type
		/// </summary>
		ExecutionType type;

		/// <summary>
		/// Go of the instruction
		/// </summary>
		GameObjectPtr go = nullptr;

		/// <summary>
		/// Script of the instruction
		/// </summary>
		ScriptPtr script = nullptr;

		/// <summary>
		/// The instruction
		/// </summary>
		std::string command = "";

		/// <summary>
		/// The new index if instruction is for change go or script position
		/// </summary>
		int newIndex = -1;

		/// <summary>
		/// The new index father of the go
		/// </summary>
		std::string newFather = "";
	public:
		// For normal commands on script
		GoExecution(GameObjectPtr go, ScriptPtr script, std::string command);
		
		// For destroy go
		GoExecution(GameObjectPtr go);

		// Change script index
		GoExecution(GameObjectPtr go, ScriptPtr script, unsigned int newIndex);

		// Change go index
		GoExecution(GameObjectPtr go, unsigned int newIndex);

		// Change go father
		GoExecution(GameObjectPtr go, std::string fatherId);

		/// <summary>
		/// Get Execution type
		/// </summary>
		/// <returns></returns>
		ExecutionType GetType() const;

		/// <summary>
		/// Get go of instruction.
		/// </summary>
		GameObjectPtr GetGameObject() const;

		/// <summary>
		/// Get script of instruction.
		/// </summary>
		ScriptPtr GetScript() const;

		/// <summary>
		/// Get instruction.
		/// </summary>
		/// <returns></returns>
		std::string GetCommand() const;

		/// <summary>
		/// Get the new index for go or script
		/// </summary>
		/// <returns></returns>
		int GetNewIndex() const;
		
		/// <summary>
		/// Get the new father 
		/// </summary>
		/// <returns></returns>
		std::string GetNewFatherId() const;
	};
}}}