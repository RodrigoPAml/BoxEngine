#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Drawing {

	/// <summary>
	/// Engine 3d renderer
	/// </summary>
	class Renderer
	{
		friend class Window::Window;
	private:
		GPU::ShaderPtr shader;
		GPU::ShaderPtr shaderMtl;
	public:
		static void Draw(const Importer::ObjectPtr obj);
	private:
		Renderer() {};

		/// <summary>
		/// Returns current instance.wa
		/// </summary>
		static Renderer& Instance();

		void Init();
		void Release();
	};
}}}