#include <BoxEngine.hpp>
#include "Primitives2D.hpp"

namespace BoxEngine {
namespace Drawing {

	void Primitives2D::DrawRectangle(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec3& color, const bool filled)
	{
		auto instance = Instance();

		if (!instance.Setup(position, size, rotation, color))
			return;

		if (filled)
		{
			instance.rectMesh->Use();
			instance.rectMesh->Draw(GPU::DrawingType::TRIANGLES);
		}
		else
		{
			instance.rectUnfilledMesh->Use();
			instance.rectUnfilledMesh->Draw(GPU::DrawingType::LINE_LOOP);
		}
	}

	void Primitives2D::DrawCircle(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec3& color, const bool filled)
	{
		auto instance = Instance();

		if (!instance.Setup(position, size, rotation, color))
			return;

		if (filled)
		{
			instance.circleMesh->Use();
			instance.circleMesh->Draw(GPU::DrawingType::TRIANGLE_FAN);
		}
		else
		{
			instance.circleUnfilledMesh->Use();
			instance.circleUnfilledMesh->Draw(GPU::DrawingType::LINE_LOOP);
		}
	}

	void Primitives2D::DrawTriangle(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec2& pos3, const glm::vec3& color, const bool filled)
	{
		auto instance = Instance();
		
		if (!instance.Setup({ 1,1 }, { 2,2 }, 0, color))
			return;
		
		float v[6] = { pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y };

		instance.triangleMesh->Use();
		instance.triangleMesh->ModifyData(0, 0, 6 * sizeof(float), &v);
		
		if (filled)
			instance.triangleMesh->Draw(GPU::DrawingType::TRIANGLES);
		else
			instance.triangleMesh->Draw(GPU::DrawingType::LINE_LOOP);
	}

	void Primitives2D::DrawPoint(const glm::vec2& position, const glm::vec3& color)
	{
		auto instance = Instance();

		if (!instance.Setup(position, { 1,1 }, 0, color))
			return;

		instance.pointMesh->Use();
		instance.pointMesh->Draw(GPU::DrawingType::POINTS);
	}

	void Primitives2D::DrawLine(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec3& color)
	{
		auto instance = Instance();

		if (!instance.Setup({ 1,1 }, { 2,2 }, 0, color))
			return;

		float v[4] = {pos1.x, pos1.y, pos2.x, pos2.y};

		instance.lineMesh->Use();
		instance.lineMesh->ModifyData(0, 0, 4 * sizeof(float), v);
		instance.lineMesh->Draw(GPU::DrawingType::LINES);
	}

	Primitives2D& Primitives2D::Instance()
	{
		static Primitives2D* instance = new Primitives2D();

		return *instance;
	}

	void Primitives2D::Init()
	{
		const std::string vertShader = {
			"#version 330 core\n"
			"layout(location = 0) in vec2 vertex;\n"
			"uniform mat4 model;\n"
			"uniform mat4 projection;\n"
			"void main()\n"
			"{\n"
			"  gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
			"}"
		};

		const std::string fragShader = {
			"#version 330 core\n"
			"out vec4 colorOut;\n"
			"uniform vec3 color;\n"
			"void main()\n"
			"{\n"
			"	colorOut = vec4(color, 1.0);\n"
			"}"
		};

		this->shader = GPU::ShaderPtr(new GPU::Shader(vertShader, fragShader, ""));

		this->rectMesh = Utils::Generator::Generate2DRect(GPU::DataUse::STATIC_DRAW);
		this->rectUnfilledMesh = Utils::Generator::Generate2DRect(GPU::DataUse::STATIC_DRAW, false);
		this->pointMesh = Utils::Generator::Generate2DPoint(GPU::DataUse::DYNAMIC_DRAW);
		this->triangleMesh = Utils::Generator::Generate2DTriangle(GPU::DataUse::DYNAMIC_DRAW);
		this->lineMesh = Utils::Generator::Generate2DLine(GPU::DataUse::DYNAMIC_DRAW);
		this->circleMesh = Utils::Generator::Generate2DCircle(40, GPU::DataUse::STATIC_DRAW, true);
		this->circleUnfilledMesh = Utils::Generator::Generate2DCircle(40, GPU::DataUse::STATIC_DRAW, false);	

		Debug::Logging::Log("[Primitives2D]: Initialized", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	void Primitives2D::Release()
	{
		this->circleMesh.~shared_ptr();
		this->lineMesh.~shared_ptr();
		this->pointMesh.~shared_ptr();
		this->rectMesh.~shared_ptr();
		this->triangleMesh.~shared_ptr();
		this->circleUnfilledMesh.~shared_ptr();
		this->rectUnfilledMesh.~shared_ptr();
		this->shader.~shared_ptr();

		this->shader = nullptr;
		this->circleMesh = nullptr;
		this->lineMesh = nullptr;
		this->pointMesh = nullptr;
		this->rectMesh = nullptr;
		this->triangleMesh = nullptr;
		this->circleUnfilledMesh = nullptr;
		this->rectUnfilledMesh = nullptr;

		Debug::Logging::Log("[Primitives2D]: Released", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	bool Primitives2D::Setup(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec3& color)
	{
		const Camera::Camera2DPtr cam = Camera::Camera2D::GetCurrentCamera();

		if (cam == nullptr)
		{
			Debug::Logging::Log("[Primitives2D]: Attempt to draw a 2D primitive without a camera", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
			return false;
		}

		glm::mat4 model(glm::mat4(1.0f));

		model = glm::translate(model, glm::vec3(position, 0));

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0));

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0));

		model = glm::scale(model, glm::vec3(size.x / 2, size.y / 2, 1.0f));

		this->shader->Use();
		this->shader->SetMat4("model", model);
		this->shader->SetMat4("projection", cam->GetOrthoMatrix());
		this->shader->SetVec3("color", color);

		return true;
	}
}}
