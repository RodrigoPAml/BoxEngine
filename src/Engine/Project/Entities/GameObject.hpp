#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Engine {
namespace Project {

	class GameObject;
	typedef std::shared_ptr<GameObject> GameObjectPtr;
	typedef std::weak_ptr<GameObject> GameObjectWeakPtr;

	/// <summary>
	/// Represents an entity of the game.
	/// </summary>
	class GameObject
	{
		friend class GoManager;
	private:
		/// <summary>
		/// Unique Identifier.
		/// </summary>
		std::string id;

		/// <summary>
		/// Name (not unique).
		/// </summary>
		std::string name;

		/// <summary>
		/// Father go.
		/// </summary>
		GameObjectPtr father;

		/// <summary>
		/// Childrens of this entity.
		/// </summary>
		std::vector<GameObjectPtr> childrens;

		/// <summary>
		/// Scripts
		/// </summary>
		std::vector<ScriptPtr> scripts;

		/// <summary>
		/// If go its active.
		/// </summary>
		bool active;

		/// <summary>
		/// If this go will be destroyed;
		/// </summary>
		bool toDestroy = false;

		/// <summary>
		/// If this go will be visited anyway;
		/// </summary>
		bool toVisit = false;

		/// <summary>
		/// Total current existent gos
		/// </summary>
		static int Total;
	public:
		GameObject();
		~GameObject();

		std::string GetId() const;

		void SetName(const std::string& name);
		std::string GetName() const;

		void SetActive(const bool active);
		bool GetActive() const;

		void SetFather(const GameObjectPtr& father);
		GameObjectPtr GetFather() const;

		std::vector<GameObjectPtr>& GetChildrens();

		// Used in runtime (non persistent)
		bool AddScript(ScriptPtr script);
		void RemoveScript(ScriptPtr script);
		std::vector<ScriptPtr>& GetScripts();
		void ClearScripts();

		bool IsToDestroy() const;
		void SetToDestroy();

		bool IsToVisit() const;
		void SetToVisit(bool value);

		static int GetCurrentGosCount();
	};
}}}