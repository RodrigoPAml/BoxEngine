#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Window {

	/// <summary>
	/// Manager GUI for the engine.
	/// </summary>
	class GUI
	{
		friend class Window;
	private:
		ImGuiContext* context;

		int fontSize = 26;
		float fontScale = 1.0f;

		// Some of images/icons used in the engine.
		std::map<std::string, GPU::TexturePtr> images;
		std::map<std::string, std::string> imagesByExtension;
	public:
		// Frame limiters
		static void BeginFrame();
		static void EndFrame();

		// Ids
		static void Push(const std::string& label);
		static void Pop();

		// Texts
		static void Text(const std::string& label);
		static void DisabledText(const std::string& label);
		static void BulletText(const std::string& label);
		static void ColoredText(const std::string& label, const glm::vec4& color);
		static void WrappedText(const std::string& label);

		// Buttons and Selectables
		static bool CheckBox(const std::string& label, bool& checked);
		static bool Button(const std::string& label, const glm::vec2& size = { 0, 0 });
		static bool RadioButton(const std::string& label, bool& selected);
		static bool Selectable(const std::string& label, const std::string& text, bool& selected);
		static bool Selectable(const std::string& label, const std::string& text);

		// Images
		static void Image(GPU::TexturePtr texture, const glm::vec2& size);
		static bool ImageButton(const std::string& label, GPU::TexturePtr texture);

		// Inputs
		static bool Input(const std::string& label, std::string& text);
		static bool Input(const std::string& label, const std::string& hint, std::string& text);
		static bool Input(const std::string& label, double& val);
		static bool Input(const std::string& label, float& val);
		static bool Input(const std::string& label, int& val);
		static bool Input(const std::string& label, glm::vec2& val);
		static bool Input(const std::string& label, glm::vec3& val);
		static bool Input(const std::string& label, glm::vec4& val);

		static bool MultilineText(const std::string& label, std::string& text);

		// Drags
		static bool Drag(const std::string& label, int& val);
		static bool Drag(const std::string& label, float& val);
		static bool Drag(const std::string& label, glm::vec2& val);
		static bool Drag(const std::string& label, glm::vec3& val);
		static bool Drag(const std::string& label, glm::vec4& val);

		// Sliders
		static bool Slider(const std::string& label, const glm::vec<2, int>& limits, int& val);
		static bool Slider(const std::string& label, const glm::vec2& limits, float& val);
		static bool Slider(const std::string& label, const glm::vec2& limits, glm::vec2& val);
		static bool Slider(const std::string& label, const glm::vec2& limits, glm::vec3& val);
		static bool Slider(const std::string& label, const glm::vec2& limits, glm::vec4& val);

		// Color
		static bool ColorSelectable(const std::string& label, glm::vec3& color);
		static bool ColorSelectable(const std::string& label, glm::vec4& color);

		// List box
		static void ListBox(const std::string& label, std::vector<GUIListBoxItem>& items, const std::string& filter = "", bool lockDown = false);
		static bool BeginListBox(const std::string& label);
		static void EndListBox();

		// Combo box
		static bool ComboBox(const std::string& label, const std::vector<std::string>& itens, int& currItem, const std::string& filter = "");

		// Tabs
		static bool BeginTabBar(const std::string& label);
		static void EndTabBar();

		static bool BeginTabItem(const std::string& label);
		static void EndTabItem();

		// Trees
		static bool BeginTreeNode(const std::string& label , const std::string& text, const std::set<GUITreeFlags>& flags = { GUITreeFlags::None });
		static void EndTreeNode();

		// Font Scale
		static void SetFontScale(float scale);
		static float GetFontScale();
		static glm::vec2 CalculateTextSize(const std::string& text);

		// Window Components
		static bool IsCurrentWindowAppearing();
		static bool IsCurrentWindowCollapsed();
		static bool IsCurrentWindowFocused();
		static bool IsCurrentWindowHovered();

		static void SetNextWindowPosition(const glm::vec2& pos);
		static void SetNextWindowSize(const glm::vec2& size);
		static void SetWindowPosition(const glm::vec2& pos);
		static void SetWindowSize(const glm::vec2& size);

		static glm::vec2 GetWindowPosition();
		static glm::vec2 GetWindowSize();

		static bool BeginWindow(const std::string& label, bool* open = nullptr, const std::set<GUIWindowFlags>& flags = { GUIWindowFlags::None });
		static void EndWindow();
		static bool BeginInnerWindow(const std::string& label, const glm::vec2& size, const std::set<GUIWindowFlags>& flags = { GUIWindowFlags::None });
		static void EndInnerWindow();

		static void DownScroll();

		// Hint window
		static void BeginHintWindow();
		static void EndHintWindow();

		// Pop Ups
		static bool BeginPopUp(const std::string& label);
		static void EndPopUp();
		static void OpenPopUp(const std::string& label);
		static void CloseCurrentPopUp();
		static bool IsPopUpOpened(const std::string& label);

		// Header and identation
		static bool Header(const std::string& label);
		static void Ident(float size);
		static void Unident(float size);

		// Layouts
		static void ContinueSameLine(const float spacing = -1);
		static void Separator();
		static void Space();

		// GUI State
		static bool IsCurrentItemClickedLeft();
		static bool IsCurrentItemClickedRight();
		static bool IsCurrentItemActive();
		static bool IsCurrentItemFocused();
		static bool IsCurrentItemHovered();

		static bool IsLeftMouseClicked();
		static bool IsRightMouseClicked();

		static void SetNextItemWidth(float width);

		// Menus
		static bool BeginMainMenuBar();
		static void EndMainMenuBar();

		static bool BeginMenuBar();
		static void EndMenuBar();

		static bool BeginMenu(const std::string& label, const bool enabled = true);
		static void EndMenu();

		static bool MenuItem(const std::string& label, const bool enabled = true, const std::string& shortcut = "");

		// Drag and Drop
		static bool BeginSourceDragDrop();
		static void EndSourceDragDrop();

		static bool BeginDestinyDragDrop();
		static void EndDestinyDragDrop();

		static void SetDragDropData(const std::string& label, std::string data);
		static std::string GetDragDropData(const std::string& label);

		// Tables
		static bool BeginTable(const std::string& label, unsigned int columns);
		static void EndTable();
		static void NextRow();
		static void NextColumn();

		// Plots
		static bool BeginPlot(const std::string& label);
		static void EndPlot();

		static void PlotLine(
			const std::string& label,
			std::vector<float>& data,
			glm::vec2 limitsY,
			const std::string& yTitle
		);

		// File Dialog container
		static std::string FileDialog(
			std::string& currentPath,
			std::string& filter,
			const bool showOnlyDir,
			const std::vector<std::string>& extensions
		);

		// Warninig pop up
		static bool MakeWarningPopUp(const std::string& title, const std::string& message, const glm::vec3& color);
		
		// Icons managment
		static GPU::TexturePtr GetIcon(const std::string& iconName);
		static GPU::TexturePtr GetIconForPath(const std::string& path);
		static int GetFontSize();
	private:
		GUI() {};
		GUI(GUI const&) {};

		/// <summary>
		/// Returns current instance.
		/// </summary>
		/// <returns></returns>
		static GUI& Instance();

		/// <summary>
		/// Load resources for the engine.
		/// </summary>
		static void LoadResources();

		/// <summary>
		/// Init and Release GUI.
		/// </summary>
		static void Init(GLFWwindow* windowPtr);
		static void Release();

		static void RemoveCheckeds(std::vector<GUIListBoxItem>& items);
	};
}}}