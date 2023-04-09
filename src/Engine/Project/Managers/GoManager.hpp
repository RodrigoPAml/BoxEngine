#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Project {

	class GoManager;
	typedef std::shared_ptr<GoManager> GoManagerPtr;
	typedef std::weak_ptr<GoManager> GoManagerWeakPtr;

	/// <summary>
	/// Go Manager.
	/// </summary>
	class GoManager
	{
	private:
		/// <summary>
		/// Game Objects of project (root)
		/// </summary>
		std::vector<GameObjectPtr> gos;

		/// <summary>
		/// Fast access to gos by id (any)
		/// </summary>
		std::unordered_map<std::string, GameObjectPtr> gosMap;
	public:
		// Load and Unload go's from scene
		void Load(nlohmann::json& data);
		void Unload();

		// Get the go's from the root of the scene
		std::vector<GameObjectPtr>& GetRootGameObjects();

		// Crud in runtime (get, add and remove)
		GameObjectPtr GetGameObject(const std::string& id);
		GameObjectPtr AddGameObject(const std::string& name, bool active, const std::string& fatherId = "");
		bool RemoveGameObject(const std::string& id);
		void RemoveGameObject(GameObjectPtr go);

		// Remove go references in every thing
		void RemoveGameObjectReferences(GameObjectPtr go);
		void RemoveGameObjectReferences(const std::string& id);
	private:
		// Add go when reading from file.
		void AddGameObjectFromFile(
			const std::string& id, 
			const std::string& name, 
			bool active, 
			const std::vector<ScriptPtr>& scripts,
			const std::string fatherId = ""
		);

		// Remove all game objects of gos
		void RecursiveRemoveGos(std::vector<GameObjectPtr>& gos);
	
		// Return a new unique id for a new go.
		std::string NewGoId();
	};
}}