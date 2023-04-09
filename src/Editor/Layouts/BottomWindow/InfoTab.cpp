#include <BoxEngine.hpp>
#include "InfoTab.hpp"

namespace BoxEngine {
namespace Editor {

	void InfoTab::Awake()
	{
	}

	void InfoTab::Start()
	{
	}

	void InfoTab::Update()
	{
		using GUI = BoxEngine::Window::GUI;
		
		auto project = Project::Project::GetCurrentProject();

		auto fpsValue = project->GetCurrentFPS();
		auto frametimeValue = project->GetCurrentFrameTime();

		GUI::Separator();
		GUI::SetFontScale(0.7);
		
		GUI::Text("Go instance count: " + std::to_string(Project::GameObject::GetCurrentGosCount()));
		GUI::Text("Script instance count: " + std::to_string(Project::Script::GetCurrentScriptsCount()));
		
		GUI::Text("Texture instance count: " + std::to_string(GPU::Texture::GetInstanceCount()));
		GUI::Text("Vertex instance count: " + std::to_string(GPU::Vertex::GetInstanceCount()));
		GUI::Text("Shader instance count: " + std::to_string(GPU::Shader::GetInstanceCount()));
		GUI::Text("Framebuffer instance count: " + std::to_string(GPU::Framebuffer::GetInstanceCount()));

		GUI::Text("Stack size: " + std::to_string(project->GetStackSize()));
		
		GUI::Separator();

		this->fps.push_back(fpsValue);
		this->frametimes.push_back(frametimeValue);

		if (this->fps.size() > 200)
			this->fps.erase(this->fps.begin());

		if (this->frametimes.size() > 1000)
			this->frametimes.erase(this->frametimes.begin());

		GUI::Text("FPS: " + std::to_string(fpsValue));
		if (GUI::BeginPlot("fps"))
		{
			GUI::PlotLine("fps", this->fps, { 0, 200}, "ms");
			GUI::EndPlot();
		}

		GUI::Text("Frame Time (ms): " + std::to_string(frametimeValue));
		if (GUI::BeginPlot("frametime"))
		{
			GUI::PlotLine("frametime", this->frametimes, { 0, 50 }, "per second");
			GUI::EndPlot();
		}

		GUI::SetFontScale(1);
		GUI::Separator();
	}

	void InfoTab::Destroy()
	{
	}
}}

