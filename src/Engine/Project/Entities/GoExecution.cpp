#include <BoxEngine.hpp>
#include "GoExecution.hpp"

namespace BoxEngine {
namespace Project {

	GoExecution::GoExecution(GameObjectPtr go, ScriptPtr script, std::string command)
	{
		this->go = go;
		this->script = script;
		this->command = command;
	}

	GameObjectPtr GoExecution::GetGo() const
	{
		return this->go;
	}
	
	ScriptPtr GoExecution::GetScript() const
	{
		return this->script;
	}
	
	std::string GoExecution::GetCommand() const
	{
		return this->command;
	}
	
	bool GoExecution::IsDestroyed() const
	{
		return this->isDestroy;
	}
	
	void GoExecution::SetIsDestroy(bool value)
	{
		this->isDestroy = value;
	}
}}