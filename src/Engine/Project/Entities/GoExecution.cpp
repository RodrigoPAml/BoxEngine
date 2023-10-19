#include <BoxEngine.hpp>
#include "GoExecution.hpp"

namespace BoxEngine {
namespace Engine {
namespace Project {

	GoExecution::GoExecution(GameObjectPtr go, ScriptPtr script, std::string command)
	{
		this->go = go;
		this->script = script;
		this->command = command;
		this->type = ExecutionType::Normal;
	}

	GoExecution::GoExecution(GameObjectPtr go)
	{
		this->go = go;
		this->type = ExecutionType::Destroy;
	}

	GoExecution::GoExecution(GameObjectPtr go, ScriptPtr script, unsigned int newIndex)
	{
		this->go = go;
		this->script = script;
		this->newIndex = newIndex;
		this->type = ExecutionType::ScriptIndexChange;
	}

	GoExecution::GoExecution(GameObjectPtr go, unsigned int newIndex)
	{
		this->go = go;
		this->script = script;
		this->newIndex = newIndex;
		this->type = ExecutionType::ScriptIndexChange;
	}

	GoExecution::GoExecution(GameObjectPtr go, std::string fatherId)
	{
		this->go = go;
		this->newFather = fatherId;
		this->type = ExecutionType::Movement;
	}

	ExecutionType GoExecution::GetType() const
	{
		return this->type;
	}

	GameObjectPtr GoExecution::GetGameObject() const
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

	int GoExecution::GetNewIndex() const
	{
		return this->newIndex;
	}

	std::string GoExecution::GetNewFatherId() const
	{
		return this->newFather;
	}
}}}