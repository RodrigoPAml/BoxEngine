#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	using namespace Engine;

	class TextureVisualizer : public Layout
	{
	private:
		std::string guid;

		bool focused = false;
		bool open = false;
		bool configured = false;
		bool canDraw = true;

		int toDraw = -1;
		glm::vec2 pos, size;
	public:
		TextureVisualizer() = default;
		~TextureVisualizer() = default;

		void Start();
		void SetOpen(bool val);
		void Update();

		void DrawTexture();
		bool IsFocused();
	};
}}
