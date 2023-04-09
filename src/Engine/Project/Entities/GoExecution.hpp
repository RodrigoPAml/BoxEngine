#pragma once
#include "BoxEngine.hpp"

namespace BoxEngine {
namespace Project {

	/// <summary>
	/// Represents part of the execution of a go.
	/// </summary>
	class GoExecution
	{
	private:
		/// <summary>
		/// Go of instruction
		/// </summary>
		GameObjectPtr go;

		/// <summary>
		/// Script of the instruction
		/// </summary>
		ScriptPtr script;

		/// <summary>
		/// The instruction
		/// </summary>
		std::string command;

		/// <summary>
		/// If the go is to be destroyed with it scripts
		/// </summary>
		bool isDestroy = false;
	public:
		GoExecution(GameObjectPtr go, ScriptPtr script, std::string command);

		/// <summary>
		/// Get game object of instruction.
		/// </summary>
		GameObjectPtr GetGo() const;

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
		/// If the go is destroyed.
		/// </summary>
		/// <returns></returns>
		bool IsDestroyed() const;

		/// <summary>
		/// Set if the go is destroyed.
		/// </summary>
		void SetIsDestroy(bool value);
	};
}}