#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Drawing {

	/// <summary>
	/// Draw 2D Primitives.
	/// </summary>
	class Primitives2D
	{
		friend class BoxEngine::Window::Window;
	private:
		GPU::VertexPtr rectMesh;
		GPU::VertexPtr rectUnfilledMesh;
		GPU::VertexPtr circleMesh;
		GPU::VertexPtr circleUnfilledMesh;
		GPU::VertexPtr pointMesh; 
		GPU::VertexPtr lineMesh;
		GPU::VertexPtr triangleMesh;

		GPU::ShaderPtr shader;
	public:
		static void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const bool filled = true);
		static void DrawCircle(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const bool filled = true);
		static void DrawTriangle(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec2& pos3, const glm::vec4& color, const bool filled = true);
		static void DrawPoint(const glm::vec2& position, const glm::vec4& color);
		static void DrawLine(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec4& color);
	private:
		Primitives2D() {};

		/// <summary>
		/// Returns current instance.
		/// </summary>
		static Primitives2D& Instance();

		void Init();
		void Release();

		bool Setup(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color);
	};
}}
