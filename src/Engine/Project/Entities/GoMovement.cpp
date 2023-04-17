#include <BoxEngine.hpp>
#include "GoMovement.hpp"

namespace BoxEngine {
namespace Project {

	GoMovement::GoMovement(GameObjectPtr go, GameObjectPtr father)
	{
		this->go = go;
		this->father = father;
	}

	GoMovement::GoMovement(GameObjectPtr go, unsigned int newIndex)
	{
		this->go = go;
		this->newIndex = newIndex;
	}

	GameObjectPtr GoMovement::GetGo() const
	{
		return this->go;
	}

	GameObjectPtr GoMovement::GetNewFather() const
	{
		return this->father;
	}
	
	int GoMovement::GetNewIndex() const
	{
		return this->newIndex;
	}
}}