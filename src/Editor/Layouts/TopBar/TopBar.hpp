#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	class TopBar : public Layout
	{
	private:
		bool reset = true;
		bool focused = false;

		TextureVisualizer visualizer;
	public:
		void Reset();
		void Update();
		void DrawTextureVisualizerTex();

		bool IsFocused();
	};	
}}