#pragma once
#include "BoxEngine.hpp"

namespace BoxEngine {
namespace Project {

	/// <summary>
	/// Request to change go position in the tree or the its father
	/// These types of request are processed in the end of the frame only
	/// </summary>
	class GoMovement
	{
	private:
		/// <summary>
		/// Go target
		/// </summary>
		GameObjectPtr go;

		/// <summary>
		/// New father to be set
		/// </summary>
		GameObjectPtr father;

		/// <summary>
		/// If this value is positive then the request is only to change position.
		/// </summary>
		int newIndex = -1;
	public:
		GoMovement(GameObjectPtr go, GameObjectPtr father);
		GoMovement(GameObjectPtr go, unsigned int newIndex);

		GameObjectPtr GetGo() const;
		GameObjectPtr GetNewFather() const;
		int GetNewIndex() const;
	};
}}