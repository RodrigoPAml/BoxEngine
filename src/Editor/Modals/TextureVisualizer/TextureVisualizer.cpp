#include <BoxEngine.hpp>
#include "TextureVisualizer.hpp"

namespace BoxEngine {
namespace Editor {
	
	using namespace Modules;
	using namespace Engine;

	void TextureVisualizer::Start()
	{
		this->guid = Utils::Directory::NewGuid();
	}

	void TextureVisualizer::SetOpen(bool val)
	{
		this->open = val;
	}

	void TextureVisualizer::Update()
	{
		using GUI = Window::GUI;
		 
		if (this->open && !this->configured)
		{
			GUI::SetNextWindowPosition(Window::Window::GetSize() / 2.0f);
			GUI::SetNextWindowSize({ 400, 400 });

			this->configured = true;
		}

		if (open && GUI::BeginWindow("Texture Visualizer", &open, { Window::GUIWindowFlags::NoCollapse }))
		{
			auto project = Project::Project::GetCurrentProject();

			if (project != nullptr)
			{
				std::vector<std::string> items;

				for (auto item : Project::Project::GetCurrentProject()->GetTextures())
					items.push_back(std::to_string(item.first));

				this->canDraw = !GUI::DropBoxSelectable(this->guid + "options", items, this->toDraw);

				auto size = GUI::GetContentRegionAvailable();
				auto pos = GUI::GetWindowPosition() + size / 2.0f;
				auto totalSize = Window::Window::GetSize();
				pos.y = (totalSize.y - pos.y);

				if (this->toDraw != -1)
				{
					this->pos = pos;
					this->size = size;
				}
			}

			this->focused = GUI::IsCurrentWindowFocused() || !this->canDraw;
			GUI::EndWindow();
		}
		else this->focused = false;
	}

	void TextureVisualizer::DrawTexture()
	{
		if (this->toDraw != -1 && this->canDraw)
		{
			int index = 0;
			for (auto item : Project::Project::GetCurrentProject()->GetTextures())
			{
				if (index == this->toDraw)
				{
					pos.y -= 80;
					pos.x += 5;
					
					bool depthTestingEnabled = GPU::Command::IsDepthTestingEnabled();

					if (depthTestingEnabled)
						GPU::Command::DisableDepthTesting();

					Modules::Drawing::TextureRenderer::Draw(item.second, pos, size, { 0, 0, 0}, 0);

					if (depthTestingEnabled)
						GPU::Command::EnableDepthTesting();

					break;
				}

				index++;
			}
		}
	}

	bool TextureVisualizer::IsFocused()
	{
		return this->focused && this->open;
	}
}}