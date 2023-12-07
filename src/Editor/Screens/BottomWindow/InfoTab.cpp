#include <BoxEngine.hpp>
#include "InfoTab.hpp"

namespace BoxEngine {
namespace Editor {

	void InfoTab::Awake()
	{
		this->guid = Modules::Utils::Directory::NewGuid();
	}

	void InfoTab::Start()
	{
	}

	void InfoTab::Update()
	{
		using GUI = Modules::Window::GUI;

		if (GUI::BeginInnerWindow(this->guid + "inner", { 0, 0 }))
		{
			auto project = Engine::Project::Project::GetCurrentProject();

			auto fpsValue = project->GetCurrentFPS();
			auto frametimeValue = project->GetCurrentFrameTime();

			GUI::SetFontScale(0.7);
		
			auto showTotalizers = GUI::Header("Totalizers");
			GUI::ContinueSameLine(15);
			GUI::Text("Totalizers");

			if (showTotalizers)
			{
				GUI::Ident(10);
				GUI::Text("Go instance count: " + std::to_string(Engine::Project::GameObject::GetCurrentGosCount()));
				GUI::Text("Script instance count: " + std::to_string(Engine::Project::Script::GetCurrentScriptsCount()));
				GUI::Text("Texture instance count: " + std::to_string(Modules::GPU::Texture::GetInstanceCount()));
				GUI::Text("Vertex instance count: " + std::to_string(Modules::GPU::Vertex::GetInstanceCount()));
				GUI::Text("Shader instance count: " + std::to_string(Modules::GPU::Shader::GetInstanceCount()));
				GUI::Text("Audio instance count: " + std::to_string(Modules::Audio::Audio::GetInstaceCount()));
				GUI::Text("Font instance count: " + std::to_string(Modules::Font::Font::GetInstaceCount()));
				GUI::Text("Framebuffer instance count: " + std::to_string(Modules::GPU::Framebuffer::GetInstanceCount()));
				GUI::Text("Stack size: " + std::to_string(project->GetStackSize()));
				GUI::Unident(10);
			}
		
			GUI::Separator();

			this->fps.push_back(fpsValue);
			this->frametimes.push_back(frametimeValue);

			if (this->fps.size() > 200)
				this->fps.erase(this->fps.begin());

			if (this->frametimes.size() > 1000)
				this->frametimes.erase(this->frametimes.begin());

			auto showFPS = GUI::Header("FPS");
			GUI::ContinueSameLine(15);
			GUI::Text("FPS");

			if (showFPS)
			{
				GUI::Text("FPS: " + std::to_string(fpsValue));
				if (GUI::BeginPlot("fps"))
				{
					GUI::PlotLine("fps", this->fps, { 0, 200 }, "ms");
					GUI::EndPlot();
				}
			}

			auto autoShowFrametime = GUI::Header("frametime");
			GUI::ContinueSameLine(15);
			GUI::Text("Frametime");

			if (autoShowFrametime)
			{
				GUI::Text("Frame Time (ms): " + std::to_string(frametimeValue));

				if (GUI::BeginPlot("frametime"))
				{
					GUI::PlotLine("frametime", this->frametimes, { 0, 50 }, "per second");
					GUI::EndPlot();
				}
			}

			GUI::SetFontScale(1);
			GUI::Separator();
			GUI::EndInnerWindow();
		}
	}
}}

