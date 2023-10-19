#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Window {
	
	/// <summary>
	/// Flags for customize GUI Window.
	/// </summary>
	enum class GUIWindowFlags
	{
		None = ImGuiWindowFlags_None,
		TitleBar = ImGuiWindowFlags_NoTitleBar,
		NoResize = ImGuiWindowFlags_NoResize,
		NoMove = ImGuiWindowFlags_NoMove,
		NoScrollbar = ImGuiWindowFlags_NoScrollbar,
		NoScrollWithMouse = ImGuiWindowFlags_NoScrollWithMouse,
		NoCollapse = ImGuiWindowFlags_NoCollapse,
		AlwaysAutoResize = ImGuiWindowFlags_AlwaysAutoResize,
		NoBackground = ImGuiWindowFlags_NoBackground,
		NoSavedSettings = ImGuiWindowFlags_NoSavedSettings,
		NoMouseInputs = ImGuiWindowFlags_NoMouseInputs,
		MenuBar = ImGuiWindowFlags_MenuBar,
		HorizontalScrollbar = ImGuiWindowFlags_HorizontalScrollbar,
		NoFocusOnAppearing = ImGuiWindowFlags_NoFocusOnAppearing,
		NoBringToFrontOnFocus = ImGuiWindowFlags_NoBringToFrontOnFocus,
		AlwaysVerticalScrollbar = ImGuiWindowFlags_AlwaysVerticalScrollbar,
		AlwaysHorizontalScrollbar = ImGuiWindowFlags_AlwaysHorizontalScrollbar,
		AlwaysUseWindowPadding = ImGuiWindowFlags_AlwaysUseWindowPadding,
		NoNavInputs = ImGuiWindowFlags_NoNavInputs,
		NoNavFocus = ImGuiWindowFlags_NoNavFocus,
		UnsavedDocument = ImGuiWindowFlags_UnsavedDocument,
		NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
		NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
		NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
	};

	enum GUITreeFlags
	{
		None = ImGuiTreeNodeFlags_None,
		Selected = ImGuiTreeNodeFlags_Selected,
		Framed = ImGuiTreeNodeFlags_Framed, 
		AllowItemOverlap = ImGuiTreeNodeFlags_AllowItemOverlap,
		NoTreePushOnOpen = ImGuiTreeNodeFlags_NoTreePushOnOpen,
		DefaultOpen = ImGuiTreeNodeFlags_DefaultOpen,
		OpenOnDoubleClick = ImGuiTreeNodeFlags_OpenOnDoubleClick,
		OpenOnArrow = ImGuiTreeNodeFlags_OpenOnArrow,
		Leaf = ImGuiTreeNodeFlags_Leaf,
		Bullet = ImGuiTreeNodeFlags_Bullet,
		FramePadding = ImGuiTreeNodeFlags_FramePadding,
		SpanAvailWidth = ImGuiTreeNodeFlags_SpanAvailWidth,
		SpanFullWidth = ImGuiTreeNodeFlags_SpanFullWidth,
		NavLeftJumpsBackHere  = ImGuiTreeNodeFlags_NavLeftJumpsBackHere,
		CollapsingHeader = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog
	};
}}}