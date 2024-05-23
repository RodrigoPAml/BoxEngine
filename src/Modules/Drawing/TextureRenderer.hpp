#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Drawing {

	/// <summary>
	/// Used to draw a texture.
	/// </summary>
	class TextureRenderer
	{
		friend class Window::Window;
	private:
		GPU::ShaderPtr shader;
		GPU::ShaderPtr shaderMultisampled;

		GPU::VertexPtr mesh;
	public:
		static void Draw(const GPU::TexturePtr texture, const glm::vec2& position, const glm::vec2& size, const glm::vec3& color, const float rotation, const float colorWeight = 0);
	private:
		TextureRenderer() {};

		/// <summary>
		/// Returns current instance.
		/// </summary>
		static TextureRenderer& Instance();

		void Init();
		void Release();
	};
}}}