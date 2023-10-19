#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	using namespace Engine;

	class GameTree : public Layout
	{
	private:
		std::string guid = "";
		bool reset = true;

		bool isMenuGoOpen = false;

		std::string clickedGoId = "";
		std::string createGoInput = "";

		// To move gos
		std::string sourceGoId = "";
		std::string destinyGoId = "";

		float minY = 0;
		float maxX = 0;

		std::string filter = "";
	public:
		GameTree() = default;
		~GameTree() = default;

		void Awake();
		void Update();

		float GetMaxX() const;
		void SetMinY(float value);
	private:
		void DrawGameTree();
		void RecursiveDrawGameTree(std::vector<Engine::Project::GameObjectPtr>& gos, bool inactive = false);

		bool isFiltered(Engine::Project::GameObjectPtr go, std::string value);

		void DrawMenus();
	};
}}
