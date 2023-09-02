#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Drawing {

	/// <summary>
	/// Draw 3D Primitives.
	/// </summary>
	class Primitives3D
	{
		friend class BoxEngine::Window::Window;
	private:
		GPU::VertexPtr meshCube;
		GPU::VertexPtr meshUnfilledCube;
		GPU::VertexPtr meshSphere;
		GPU::VertexPtr meshUnfilledSphere;
		GPU::VertexPtr meshPoint;
		GPU::VertexPtr meshLine;
		GPU::VertexPtr meshRect;
		GPU::VertexPtr meshUnfilledRect;
		GPU::VertexPtr meshCircle;
		GPU::VertexPtr meshUnfilledCircle;
		GPU::VertexPtr meshTriangle;

		GPU::ShaderPtr shader;
	public:
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color, bool filled = true);

		static void DrawSphere(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color, bool filled = true);

		static void DrawPoint(const glm::vec3& position, const glm::vec4& color);

		static void DrawLine(const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec4& color);

		static void DrawRect(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color, bool filled = true);

		static void DrawTriangle(const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec3& pos3, const glm::vec4& color, bool filled = true);

		static void DrawCircle(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color, bool filled = true);
	private:
		Primitives3D() {};

		/// <summary>
		/// Returns current instance.
		/// </summary>
		static Primitives3D& Instance();

		void Init();
		void Release();

		bool Setup(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color);
	};
}}
