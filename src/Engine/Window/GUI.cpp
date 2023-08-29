#include <BoxEngine.hpp>
#include "GUI.hpp"

// ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace BoxEngine {
namespace Window {

	void GUI::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GUI::EndFrame()
	{
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUI::Push(const std::string& label)
	{
		ImGui::PushID(label.c_str());
	}

	void GUI::Pop()
	{
		ImGui::PopID();
	}

	void GUI::Text(const std::string& text)
	{
		ImGui::AlignTextToFramePadding();
		ImGui::Text(text.c_str());
	}

	void GUI::DisabledText(const std::string& text)
	{
		ImGui::AlignTextToFramePadding();
		ImGui::TextDisabled(text.c_str());
	}

	void GUI::BulletText(const std::string& text)
	{
		ImGui::AlignTextToFramePadding();
		ImGui::BulletText(text.c_str());
	}

	void GUI::ColoredText(const std::string& text, const glm::vec4& color)
	{
		ImGui::AlignTextToFramePadding();
		ImGui::TextColored(ImVec4(color.x, color.y, color.z, color.w), text.c_str());
	}

	void GUI::WrappedText(const std::string& text)
	{
		ImGui::AlignTextToFramePadding();
		ImGui::TextWrapped(text.c_str());
	}

	bool GUI::CheckBox(const std::string& label, bool& checked)
	{
		auto id = "##" + label;

		return ImGui::Checkbox(id.c_str(), &checked);
	}

	bool GUI::Button(const std::string& label, const glm::vec2& size)
	{
		return ImGui::Button(label.c_str(), {size.x, size.y});
	}

	bool GUI::RadioButton(const std::string& label, bool& selected)
	{
		ImGui::RadioButton(label.c_str(), selected);

		return selected;
	}

	bool GUI::Selectable(const std::string& label, const std::string& text, bool& selected)
	{
		GUI::Push(label);

		bool val = ImGui::Selectable(text.c_str(), &selected);

		GUI::Pop();

		return val;
	}

	bool GUI::Selectable(const std::string& label, const std::string& text)
	{
		GUI::Push(label);

		bool val = ImGui::Selectable(text.c_str(), false);

		GUI::Pop();

		return val;
	}

	void GUI::Image(GPU::TexturePtr texture, const glm::vec2& size)
	{
		ImTextureID my_tex_id = ImTextureID(texture->GetId());
						
		ImGui::Image(my_tex_id, ImVec2(size.x, size.y), ImVec2(0, 0), ImVec2(1, 1));
	}

	bool GUI::ImageButton(const std::string& label, GPU::TexturePtr texture)
	{
		ImTextureID my_tex_id = ImTextureID(texture->GetId());

		GUI::Push(label);
		auto value = ImGui::ImageButton(my_tex_id, ImVec2(GUI::GetFontSize(), GUI::GetFontSize()), ImVec2(0, 0), ImVec2(1, 1));
		GUI::Pop();

		return value;
	}

	bool GUI::Input(const std::string& label, std::string& text)
	{
		auto id = "##" + label;

		char* cstr = new char[4096];
		strcpy(cstr, text.c_str());

		bool changed = ImGui::InputText(id.c_str(), cstr, 4096);

		text = cstr;
		delete[] cstr;

		return changed;
	}

	bool GUI::Input(const std::string& label, const std::string& hint, std::string& text)
	{
		auto id = "##" + label;

		char* cstr = new char[4096];
		strcpy(cstr, text.c_str());

		bool changed = ImGui::InputTextWithHint(id.c_str(), hint.c_str(), cstr, 4096);

		text = cstr;
		delete[] cstr;

		return changed;
	}

	bool GUI::Input(const std::string& label, double& val)
	{
		auto id = "##" + label;

		if (val - (int)val == 0)
			return ImGui::InputDouble(id.c_str(), &val, 0, 0, "%.0f");

		return ImGui::InputDouble(id.c_str(), &val, 0, 0, "%.6f");
	}

	bool GUI::Input(const std::string& label, float& val)
	{
		auto id = "##" + label;

		return ImGui::InputFloat(id.c_str(), &val, 0, 0, "%.3f");
	}

	bool GUI::Input(const std::string& label, int& val)
	{
		auto id = "##" + label;

		return ImGui::InputInt(id.c_str(), &val, 1, 100);
	}

	bool GUI::Input(const std::string& label, glm::vec2& val)
	{
		auto id = "##" + label;

		float v[2];

		v[0] = val.x;
		v[1] = val.y;

		bool changed = ImGui::InputFloat2(id.c_str(), v, "%.3f");

		val.x = v[0];
		val.y = v[1];

		return changed;
	}

	bool GUI::Input(const std::string& label, glm::vec3& val)
	{
		auto id = "##" + label;

		float v[3];

		v[0] = val.x;
		v[1] = val.y;
		v[2] = val.z;

		bool changed = ImGui::InputFloat3(id.c_str(), v, "%.3f");

		val.x = v[0];
		val.y = v[1];
		val.z = v[2];

		return changed;
	}

	bool GUI::Input(const std::string& label, glm::vec4& val)
	{
		auto id = "##" + label;

		float v[4];

		v[0] = val.x;
		v[1] = val.y;
		v[2] = val.z;
		v[3] = val.w;

		bool changed = ImGui::InputFloat2(id.c_str(), v, "%.3f");

		val.x = v[0];
		val.y = v[1];
		val.z = v[2];
		val.w = v[3];
	
		return changed;
	}

	bool GUI::MultilineText(const std::string& label, std::string& text)
	{
		auto id = "##" + label;

		char* cstr = new char[8096];
		strcpy(cstr, text.c_str());
		bool changed = ImGui::InputTextMultiline(id.c_str(), cstr, 8096, {0,0});

		text = cstr;
		delete[] cstr;

		return changed;
	}

	bool GUI::Drag(const std::string& label, int& val)
	{
		auto id = "##" + label;

		return ImGui::DragInt(id.c_str(), &val);
	}

	bool GUI::Drag(const std::string& label, float& val)
	{
		auto id = "##" + label;

		return ImGui::DragFloat(id.c_str(), &val);
	}

	bool GUI::Drag(const std::string& label, glm::vec2& val)
	{
		auto id = "##" + label;

		float v[2];

		v[0] = val.x;
		v[1] = val.y;

		bool changed = ImGui::DragFloat2(id.c_str(), v);

		val.x = v[0];
		val.y = v[1];

		return changed;
	}

	bool GUI::Drag(const std::string& label, glm::vec3& val)
	{
		auto id = "##" + label;

		float v[3];

		v[0] = val.x;
		v[1] = val.y;
		v[2] = val.z;

		bool changed = ImGui::DragFloat3(id.c_str(), v);

		val.x = v[0];
		val.y = v[1];
		val.z = v[2];

		return changed;
	}

	bool GUI::Drag(const std::string& label, glm::vec4& val)
	{
		auto id = "##" + label;

		float v[4];

		v[0] = val.x;
		v[1] = val.y;
		v[2] = val.z;
		v[3] = val.w;

		bool changed = ImGui::DragFloat4(id.c_str(), v);

		val.x = v[0];
		val.y = v[1];
		val.z = v[2];
		val.w = v[3];

		return changed;
	}

	bool GUI::Slider(const std::string& label, const glm::vec<2, int>& limits, int& val)
	{
		auto id = "##" + label;

		return ImGui::SliderInt(id.c_str(), &val, limits.x, limits.y, "%d");
	}

	bool GUI::Slider(const std::string& label, const glm::vec2& limits, float& val)
	{
		auto id = "##" + label;

		return ImGui::SliderFloat(id.c_str(), &val, limits.x, limits.y, "%.3f");
	}

	bool GUI::Slider(const std::string& label, const glm::vec2& limits, glm::vec2& val)
	{
		auto id = "##" + label;

		float v[2];

		v[0] = val.x;
		v[1] = val.y;

		bool changed = ImGui::SliderFloat2(id.c_str(), v, limits.x, limits.y, "%.3f");

		val.x = v[0];
		val.y = v[1];

		return changed;
	}

	bool GUI::Slider(const std::string& label, const glm::vec2& limits, glm::vec3& val)
	{
		auto id = "##" + label;

		float v[3];

		v[0] = val.x;
		v[1] = val.y;
		v[2] = val.z;

		bool changed = ImGui::SliderFloat3(id.c_str(), v, limits.x, limits.y, "%.3f");

		val.x = v[0];
		val.y = v[1];
		val.z = v[2];

		return changed;
	}

	bool GUI::Slider(const std::string& label, const glm::vec2& limits, glm::vec4& val)
	{
		auto id = "##" + label;

		float v[4];

		v[0] = val.x;
		v[1] = val.y;
		v[2] = val.z;
		v[3] = val.w;

		bool changed = ImGui::SliderFloat4(id.c_str(), v, limits.x, limits.y, "%.3f");

		val.x = v[0];
		val.y = v[1];
		val.z = v[2];
		val.w = v[3];

		return changed;
	}

	bool GUI::ColorSelectable(const std::string& label, glm::vec3& color)
	{
		auto id = "##" + label;

		float v[3];

		v[0] = color.x;
		v[1] = color.y;
		v[2] = color.z;

		bool changed = ImGui::ColorEdit3(id.c_str(), v);

		color.x = v[0];
		color.y = v[1];
		color.z = v[2];

		return changed;
	}

	bool GUI::ColorSelectable(const std::string& label, glm::vec4& color)
	{
		auto id = "##" + label;

		float v[4];

		v[0] = color.x;
		v[1] = color.y;
		v[2] = color.z;
		v[3] = color.w;

		bool changed = ImGui::ColorEdit4(id.c_str(), v);

		color.x = v[0];
		color.y = v[1];
		color.z = v[2];
		color.w = v[3];

		return changed;
	}

	void GUI::ListBox(
		const std::string& label,
		std::vector<GUIListBoxItem>& items,
		const std::string& filter,
		const bool lockDown
	)
	{
		auto id = "##" + label;

		if (ImGui::BeginListBox(id.c_str(), { -FLT_MIN, -FLT_MIN }))
		{
			int innerId = 0;
			for (GUIListBoxItem& row : items)
			{
				innerId++;

				row.rightClicked = false;

				// Apply filter
				if (row.value.find(filter) == -1 && filter != "")
					continue;

				if (ImGui::Selectable(row.value.c_str(), row.selected))
				{
					RemoveCheckeds(items);
					row.selected = true;
				}

				if (ImGui::IsItemClicked(ImGuiMouseButton_::ImGuiMouseButton_Right))
					row.rightClicked = true;

				if (row.rightClicked)
					GUI::OpenPopUp(row.value + std::to_string(innerId));

				if (GUI::BeginPopUp(row.value + std::to_string(innerId)))
				{
					if (GUI::Button("Copy content"))
					{
						Utils::Directory::CopyClipboard(row.value);
						GUI::CloseCurrentPopUp();
					}

					for (auto& item : row.additionalData)
					{
						if (GUI::Button("Copy value of " + item.first))
						{
							Utils::Directory::CopyClipboard(item.second);
							GUI::CloseCurrentPopUp();
						}
					}
					GUI::EndPopUp();
				}

				if (ImGui::IsItemClicked())
					row.selected = !row.selected;

				ImVec2 p_min = ImGui::GetItemRectMin();
				ImVec2 p_max = ImGui::GetItemRectMax();

				auto drawList = ImGui::GetWindowDrawList();

				if (drawList != nullptr)
					drawList->AddRectFilled(p_min, p_max, IM_COL32(row.color.r * 255, row.color.g * 255, row.color.b * 255, row.color.a * 255));
			}

			if (lockDown)
				GUI::DownScroll();

			ImGui::EndListBox();
		}
	}

	bool GUI::BeginListBox(const std::string& label)
	{
		return ImGui::BeginListBox(("##" + label).c_str());
	}

	void GUI::EndListBox()
	{
		ImGui::EndListBox();
	}

	bool GUI::ComboBox(const std::string& label, const std::vector<std::string>& itens, int& currItem, const std::string& filter)
	{
		auto id = "##" + label;

		if (itens.size() == 0)
			return false;

		int original = currItem;

		if(currItem < 0 || currItem > itens.size() - 1)
			currItem = 0;

		bool ret = false;
		if(ImGui::BeginCombo(id.c_str(), itens[currItem].c_str()))
		{
			for(int n = 0; n < itens.size(); n++)
			{
				if (filter.size() == 0 || itens[n].find(filter) != std::string::npos)
				{
					auto label = itens[n].c_str();

					bool is_selected = (currItem == n);

					if (ImGui::Selectable(label, is_selected))
						currItem = n;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		return original != currItem;
	}

	bool GUI::BeginTabBar(const std::string& label)
	{
		return ImGui::BeginTabBar(label.c_str());
	}

	void GUI::EndTabBar()
	{
		ImGui::EndTabBar();
	}

	bool GUI::BeginTabItem(const std::string& label)
	{
		return ImGui::BeginTabItem(label.c_str());
	}

	void GUI::EndTabItem()
	{
		ImGui::EndTabItem();
	}

	bool GUI::BeginTreeNode(const std::string& label, const std::string& text, const std::set<GUITreeFlags>& flags)
	{
		int flagsCode = 0;

		for (GUITreeFlags flag : flags)
			flagsCode |= (int)flag;

		GUI::Push(label);

		bool value = ImGui::TreeNodeEx(text.c_str(), flagsCode);

		GUI::Pop();

		return value;
	}

	void GUI::EndTreeNode()
	{
		ImGui::TreePop();
	}

	void GUI::SetFontScale(float scale)
	{
		ImGui::SetWindowFontScale(scale);
		Instance().fontScale = scale;
	}

	float GUI::GetFontScale()
	{
		return Instance().fontScale;
	}

	glm::vec2 GUI::CalculateTextSize(const std::string& text)
	{
		auto size = ImGui::CalcTextSize(text.c_str());
    
		return glm::vec2(size.x, size.y);
	}

	bool GUI::IsCurrentWindowAppearing()
	{
		return ImGui::IsWindowAppearing();
	}

	bool GUI::IsCurrentWindowCollapsed()
	{
		return ImGui::IsWindowCollapsed();
	}

	bool GUI::IsCurrentWindowFocused()
	{
		return ImGui::IsWindowFocused();
	}

	bool GUI::IsCurrentWindowHovered()
	{
		return ImGui::IsWindowHovered();
	}

	void GUI::SetNextWindowPosition(const glm::vec2& pos)
	{
		ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	}

	void GUI::SetNextWindowSize(const glm::vec2& size)
	{
		ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	}

	void GUI::SetWindowPosition(const glm::vec2& pos)
	{
		ImGui::SetWindowPos({ pos.x, pos.y });
	}

	void GUI::SetWindowSize(const glm::vec2& size)
	{
		ImGui::SetWindowSize({ size.x, size.y });
	}

	glm::vec2 GUI::GetWindowPosition()
	{
		return {ImGui::GetWindowPos().x, ImGui::GetWindowPos().y};
	}

	glm::vec2 GUI::GetWindowSize()
	{
		return {ImGui::GetWindowSize().x, ImGui::GetWindowSize().y};
	}

	bool GUI::BeginWindow(const std::string& label, bool* open, const std::set<GUIWindowFlags>& flags)
	{
		int flagsCode = 0;

		for(GUIWindowFlags flag : flags)
			flagsCode |=  (int)flag;

		return ImGui::Begin(label.c_str(), open, flagsCode);
	}

	void GUI::EndWindow()
	{
		ImGui::End();
	}

	bool GUI::BeginInnerWindow(const std::string& label, const glm::vec2& size, const std::set<GUIWindowFlags>& flags)
	{
		int flagsCode = 0;

		for (GUIWindowFlags flag : flags)
			flagsCode |= (int)flag;

		return ImGui::BeginChild(label.c_str(), ImVec2(size.x, size.y), true, flagsCode);
	}

	void GUI::EndInnerWindow()
	{
		ImGui::EndChild();
	}

	void GUI::DownScroll()
	{
		ImGui::SetScrollHereY();
	}

	void GUI::BeginHintWindow()
	{
		ImGui::BeginTooltip();
	}

	void GUI::EndHintWindow()
	{
		ImGui::EndTooltip();
	}

	bool GUI::BeginPopUp(const std::string& label)
	{
		return ImGui::BeginPopup(label.c_str());
	}

	void GUI::EndPopUp()
	{
		ImGui::EndPopup();
	}

	void GUI::OpenPopUp(const std::string& label)
	{
		ImGui::OpenPopup(label.c_str());
	}

	void GUI::CloseCurrentPopUp()
	{
		ImGui::CloseCurrentPopup();
	}

	bool GUI::IsPopUpOpened(const std::string& label)
	{
		return ImGui::IsPopupOpen(label.c_str());
	}

	bool GUI::Header(const std::string& label)
	{
		return ImGui::CollapsingHeader(("##" + label).c_str(), ImGuiTreeNodeFlags_AllowItemOverlap);
	}

	void GUI::Ident(float size)
	{
		ImGui::Indent(size);
	}

	void GUI::Unident(float size)
	{
		ImGui::Unindent(size);
	}

	void GUI::ContinueSameLine(float spacing)
	{
		ImGui::SameLine(0, spacing);
	}

	void GUI::Separator()
	{
		ImGui::Separator();
	}

	void GUI::Space()
	{
		ImGui::Spacing();
	}

	bool GUI::IsCurrentItemClickedLeft()
	{
		return ImGui::IsItemClicked();
	}

	bool GUI::IsCurrentItemClickedRight()
	{
		return ImGui::IsItemClicked(ImGuiMouseButton_Right);
	}

	bool GUI::IsCurrentItemActive()
	{
		return ImGui::IsItemActive();
	}

	bool GUI::IsCurrentItemFocused()
	{
		return ImGui::IsItemFocused();
	}

	bool GUI::IsCurrentItemHovered()
	{
		return ImGui::IsItemHovered();
	}

	bool GUI::IsLeftMouseClicked()
	{
		return ImGui::IsMouseClicked(ImGuiMouseButton_Left);
	}

	bool GUI::IsRightMouseClicked()
	{
		return ImGui::IsMouseClicked(ImGuiMouseButton_Right);
	}

	void GUI::SetNextItemWidth(float width)
	{
		ImGui::SetNextItemWidth(width);
	}

	bool GUI::BeginMainMenuBar()
	{
		return ImGui::BeginMainMenuBar();
	}

	void GUI::EndMainMenuBar()
	{
		return ImGui::EndMainMenuBar();
	}

	bool GUI::BeginMenuBar()
	{
		return ImGui::BeginMenuBar();
	}

	void GUI::EndMenuBar()
	{
		ImGui::EndMenuBar();
	}

	bool GUI::BeginMenu(const std::string& label, const bool enabled)
	{
		return ImGui::BeginMenu(label.c_str(), enabled);
	}

	void GUI::EndMenu()
	{
		ImGui::EndMenu();
	}

	bool GUI::MenuItem(const std::string& name, const bool enabled, const std::string& shortcut)
	{
		return ImGui::MenuItem(name.c_str(), shortcut.c_str(), nullptr, enabled);
	}

	bool GUI::BeginSourceDragDrop()
	{
		return ImGui::BeginDragDropSource();
	}

	void GUI::EndSourceDragDrop()
	{
		ImGui::EndDragDropSource();
	}

	bool GUI::BeginDestinyDragDrop()
	{
		return ImGui::BeginDragDropTarget();
	}

	void GUI::EndDestinyDragDrop()
	{
		ImGui::EndDragDropTarget();
	}

	void GUI::SetDragDropData(const std::string& label, std::string data)
	{
		ImGui::SetDragDropPayload(label.c_str(), data.c_str(), data.size());
	}

	std::string GUI::GetDragDropData(const std::string& label)
	{
		auto payload = ImGui::AcceptDragDropPayload(label.c_str());

		if (payload == nullptr)
			return "";

		if (payload->Data == nullptr)
			return "";

		const char* data = (const char*)payload->Data;

		return data;
	}

	bool GUI::BeginTable(const std::string& label, unsigned int columns)
	{
		return ImGui::BeginTable(label.c_str(), columns, 
			ImGuiTableFlags_Resizable |
			ImGuiTableFlags_Borders |
			ImGuiTableFlags_RowBg |
			ImGuiTableFlags_SizingStretchSame
		);
	}

	void GUI::EndTable()
	{
		ImGui::EndTable();
	}

	void GUI::NextRow()
	{
		ImGui::TableNextRow();
	}

	void GUI::NextColumn()
	{
		ImGui::TableNextColumn();
	}

	bool GUI::BeginPlot(const std::string& label)
	{
		return ImPlot::BeginPlot(("##" + label).c_str());
	}

	void GUI::EndPlot()
	{
		ImPlot::EndPlot();
	}

	void GUI::PlotLine(
		const std::string& label, 
		std::vector<float>& data,
		glm::vec2 limitsY,
		const std::string& yTitle
	)
	{
		ImPlot::SetNextAxisToFit(ImAxis_X1);
		ImPlot::SetNextAxisToFit(ImAxis_X2);
		ImPlot::SetNextAxisToFit(ImAxis_X3);

		ImPlot::SetupAxisLimits(ImAxis_Y1, limitsY.x, limitsY.y, ImPlotCond_Once);
		ImPlot::SetupAxisLimits(ImAxis_Y2, limitsY.x, limitsY.y, ImPlotCond_Once);
		ImPlot::SetupAxisLimits(ImAxis_Y3, limitsY.x, limitsY.y, ImPlotCond_Once);

		ImPlot::SetupAxis(ImAxis_Y1, yTitle.c_str());
		ImPlot::SetupAxis(ImAxis_X1, "Samples");

		ImPlot::PlotLine<float>(label.c_str(), data.data(), data.size());
	}

	std::string GUI::FileDialog(
		std::string& currentPath,
		std::string& filter,
		const bool showOnlyDir, 
		const std::vector<std::string>& extensions
	)
	{
		auto id = "##" + currentPath;
		std::string clickedPath = "";
		GUI::SetFontScale(0.9);
		GUI::Text("Current path:");
		GUI::ContinueSameLine(1);
		GUI::ColoredText(currentPath, {0.5, 0.5, 0.0, 1});
		GUI::SetFontScale(1);

		if (!Utils::Directory::IsDirectory(currentPath))
			return "";

		GUI::ContinueSameLine(8);
		if (GUI::ImageButton(currentPath, GUI::GetIcon("back.png")))
		{
			std::string previous = Utils::Directory::RemovePartsFromPath(currentPath, 1);

			if (Utils::Directory::IsDirectory(previous) && previous.size() > 2)
				currentPath = previous;
		}

		if (GUI::IsCurrentItemHovered())
		{
			GUI::BeginHintWindow();
			GUI::Text("Go to previous folder");
			GUI::EndHintWindow();
		}

		GUI::Separator();

		GUI::Text("Search: ");
		GUI::ContinueSameLine(1);
		GUI::Input(id + "input", filter);
		GUI::Separator();

		if (ImGui::BeginListBox(id.c_str(), { -FLT_MIN, 0 }))
		{
			for (const std::string& path : Utils::Directory::ListDirectories(currentPath, false))
			{
				bool isDir = Utils::Directory::IsDirectory(path);
				std::string name = Utils::Directory::GetLastPartFromPath(path);

				if (showOnlyDir && !isDir)
					continue;

				if (filter != "" && path.find(filter) == -1)
					continue;

				if (!isDir && extensions.size() > 0)
				{
					bool isValid = false;
					for (const std::string& extension : extensions)
					{
						if (path.ends_with(extension))
						{
							isValid = true;
							break;
						}
					}

					if (!isValid)
						continue;
				}

				GUI::Image(GUI::GetIconForPath(path), {GetFontSize(), GetFontSize()});
				GUI::ContinueSameLine();
				ImGui::Selectable(name.c_str(), false);

				if (ImGui::IsItemClicked())
				{
					if (isDir)
					{
						currentPath = path;
						filter = "";
					}

					clickedPath = path;
				}
			}

			ImGui::EndListBox();
		}

		return clickedPath;
	}

	bool GUI::MakeWarningPopUp(const std::string& title, const std::string& message, const glm::vec3& color)
	{
		bool click = false;

		if (ImGui::BeginPopupModal(title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize| ImGuiWindowFlags_NoMove))
		{
			ImGui::SetItemDefaultFocus();

			auto size = Window::GetSize() / 2.0f - GUI::GetWindowSize() / 2.0f;
			GUI::SetWindowPosition(size);
			GUI::ColoredText(message, { color, 1 });

			ImGui::Spacing();
			float font_size = GUI::GetFontSize() * 10 / 2;
			ImGui::SameLine(
				ImGui::GetWindowSize().x / 2 -
				font_size + (font_size / 2)
			);

			if (GUI::Button("    OK    "))
			{
				click = true;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		return click;
	}

	GPU::TexturePtr GUI::GetIcon(const std::string& iconName)
	{
		if (Instance().images.contains(iconName))
			return Instance().images[iconName];

		Debug::Logging::LogException("[GUI]: Can't find icon: " + iconName, Debug::LogOrigin::Engine);
	}

	GPU::TexturePtr GUI::GetIconForPath(const std::string& path)
	{
		if (Utils::Directory::IsDirectory(path))
			return GetIcon("folder.png");

		std::string extension = Utils::Directory::GetExtensionFromPath(path);

		if (Instance().imagesByExtension.contains(extension))
		{
			std::string imageName = Instance().imagesByExtension[extension];

			return GetIcon(imageName);
		}

		return GetIcon("file.png");
	}

	int GUI::GetFontSize()
	{
		return Instance().fontSize * Instance().fontScale;
	}

	GUI& GUI::Instance()
	{
		static GUI* instance = new GUI();

		return *instance;
	}

	void GUI::LoadResources()
	{
		auto& instance = Instance();

		const std::string resPath = Utils::Directory::GetResourcePath();
		const std::string fontPath = (resPath + "/fonts/font.ttf");

		ImFontConfig fontConfig;
		fontConfig.FontDataOwnedByAtlas = false;

		if(!Utils::Directory::Exists(fontPath))
			Debug::Logging::LogException("[GUI]: Can't find default font in : " + fontPath, Debug::LogOrigin::Engine);

		auto& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF(fontPath.c_str(), instance.fontSize, &fontConfig);

		auto textureConfig = GPU::TextureDataConfiguration();

		textureConfig.pixelFormat = GPU::TexturePixelFormat::UNSIGNED_BYTE;
		textureConfig.internalFormat = GPU::TextureInternalFormat::RGBA;

		// Load Icons
		for (const std::string& file : Utils::Directory::ListDirectories(resPath + "/icons", false))
		{
			if (Utils::Directory::IsFile(file) && Utils::Directory::GetExtensionFromPath(file) == "png")
			{
				auto icon = Utils::ImagePtr(new Utils::Image(file));
				auto texture = GPU::TexturePtr(new GPU::Texture(textureConfig, icon));

				instance.images[Utils::Directory::GetLastPartFromPath(file)] = texture;
			}
		}

		// Load extensions for ref icons
		for (const std::string& file : Utils::Directory::ListDirectories(resPath + "/extensions", false))
		{
			if (Utils::Directory::IsFile(file) && Utils::Directory::GetExtensionFromPath(file) == "txt")
			{
				std::string extension = Utils::Directory::GetLastPartFromPathNoExtension(file);
				std::string content = Utils::Directory::ReadFile(file);

				std::stringstream stream(content);
				std::string line = "";

				while (std::getline(stream, line))
				{
					instance.imagesByExtension[line] = extension + ".png";
				}
			}
		}
	}

	void GUI::Init(GLFWwindow* windowPtr)
	{
		IMGUI_CHECKVERSION();

		Instance().context = ImGui::CreateContext();
		ImPlot::CreateContext();
		ImGui::SetCurrentContext(Instance().context);

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
		colors[ImGuiCol_Border] = ImVec4(0.28f, 0.27f, 0.28f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.08f, 1.00f, 0.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.70f, 0.70f, 0.70f, 0.29f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(8.00f, 6.00f);
		style.FramePadding = ImVec2(8.00f, 4.00f);
		style.CellPadding = ImVec2(3.00f, 3.00f);
		style.ItemSpacing = ImVec2(3.00f, 4.00f);
		style.ItemInnerSpacing = ImVec2(6.00f, 5.00f);
		style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
		style.IndentSpacing = 22;
		style.ScrollbarSize = 10;
		style.GrabMinSize = 10;
		style.WindowBorderSize = 1;
		style.ChildBorderSize = 1;
		style.PopupBorderSize = 1;
		style.FrameBorderSize = 1;
		style.TabBorderSize = 1;
		style.WindowRounding = 0;
		style.ChildRounding = 11;
		style.FrameRounding = 2;
		style.PopupRounding = 11;
		style.ScrollbarRounding = 11;
		style.GrabRounding = 11;
		style.LogSliderDeadzone = 4;
		style.TabRounding = 11;
		style.WindowTitleAlign.x = 0.5f;

		ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

		ImGui_ImplGlfw_InitForOpenGL(windowPtr, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		LoadResources();

		Debug::Logging::Log("[GUI]: Initialized", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	void GUI::Release()
	{
		Instance().context = nullptr;
		Instance().images.clear();
		Instance().imagesByExtension.clear();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		ImPlot::DestroyContext();
		ImGui::DestroyContext(Instance().context);
		ImGui::SetCurrentContext(nullptr);

		Debug::Logging::Log("[GUI]: Released", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	void GUI::RemoveCheckeds(std::vector<GUIListBoxItem>& items)
	{
		for (GUIListBoxItem& item : items)
			item.selected = false;
	}
}}