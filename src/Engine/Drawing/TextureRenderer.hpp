#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Drawing {	

	/// <summary>
	/// Used to draw a texture.
	/// </summary>
	class TextureRenderer
	{
		friend class BoxEngine::Window::Window;
	private:
		GPU::ShaderPtr shader;

		GPU::VertexPtr mesh;
	public:
		static void Draw(const GPU::TexturePtr texture, const glm::vec2& position, const glm::vec2& size, const float rotation);
	private:
		TextureRenderer() {};

		/// <summary>
		/// Returns current instance.
		/// </summary>
		static TextureRenderer& Instance();

		void Init();
		void Release();
	};
}}