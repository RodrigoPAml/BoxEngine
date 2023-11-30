#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	class Editor;
	typedef std::shared_ptr<Editor> EditorPtr;

	class Editor : public Layout
	{
	private:
		TopBar topBar;
		Inspector inspector;
		GameTree gameTree;
		BottomWindow bottomBar;

		// Camera do draw into the editor screen
		Camera::Camera2DPtr camera;

		bool focused = false;

		static std::weak_ptr<Editor> current;
	public:
		Editor() = default;
		~Editor() = default;

		void Awake();
		void Start();
		void Update();
		void Destroy();
		bool IsFocused();

		void InspectProjectSettings();
		void ClearLogs();
		void InspectGo(std::string goId);
		std::string GetInspectedGo();
		
		glm::vec2 GetTopStartPoint(bool correctY = true) const;
		glm::vec2 GetBottomEndPoint(bool correctY = true) const;

		static EditorPtr GetCurrentEditor();
		static void SetCurrentEditor(EditorPtr editor);
	};
}}