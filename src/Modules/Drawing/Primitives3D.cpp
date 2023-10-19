#include <BoxEngine.hpp>
#include "Primitives3D.hpp"

namespace BoxEngine {
namespace Modules {
namespace Drawing {

	void Primitives3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color, const bool filled)
	{
		auto instance = Instance();

		if (!instance.Setup(position, size, eulerAngles, color))
			return;

		if(filled)
		{
			instance.meshCube->Use();
			instance.meshCube->Draw(GPU::DrawingType::TRIANGLE_STRIP);
		}
		else
		{
			instance.meshUnfilledCube->Use();
			instance.meshUnfilledCube->Draw(GPU::DrawingType::LINES);
		}
	}

	void Primitives3D::DrawSphere(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color, const bool filled)
	{
		auto instance = Instance();

		if (!instance.Setup(position, size, eulerAngles, color))
			return;

		if(filled)
		{
			instance.meshSphere->Use();
			instance.meshSphere->Draw(GPU::DrawingType::TRIANGLE_STRIP);
		}
		else
		{
			instance.meshUnfilledSphere->Use();
			instance.meshUnfilledSphere->Draw(GPU::DrawingType::LINES);
		}
	}

	void Primitives3D::DrawPoint(const glm::vec3& position, const glm::vec4& color)
	{
		auto instance = Instance();

		if (!instance.Setup(position, { 1,1,1 }, { 0,0,0 }, color))
			return;

		instance.meshPoint->Use();
		instance.meshPoint->Draw(GPU::DrawingType::POINTS);
	}

	void Primitives3D::DrawLine(const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec4& color)
	{
		auto instance = Instance();

		if (!instance.Setup({ 0,0,0 }, { 1,1,1 }, { 0,0,0 }, color))
			return;

		float v[6] = {pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z};

		instance.meshLine->Use();
		instance.meshLine->Draw(GPU::DrawingType::LINES);
		instance.meshLine->ModifyData(0, 0, 6 * sizeof(float), v);
	}

	void Primitives3D::DrawRect(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color, const bool filled)
	{
		auto instance = Instance();

		if (!instance.Setup(position, size, eulerAngles, color))
			return;

		if(filled)
		{
			instance.meshRect->Use();
			instance.meshRect->Draw(GPU::DrawingType::TRIANGLES);
		}
		else
		{
			instance.meshUnfilledRect->Use();
			instance.meshUnfilledRect->Draw(GPU::DrawingType::LINE_LOOP);
		}
	}

	void Primitives3D::DrawTriangle(const glm::vec3&pos1, const glm::vec3&pos2, const glm::vec3&pos3, const glm::vec4&color, const bool filled)
	{
		auto instance = Instance();

		if (!instance.Setup({ 0,0,0 }, { 1,1,1 }, { 0,0,0 }, color))
			return;

		float v[9] = {pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z , pos3.x, pos3.y, pos3.z};

		instance.meshTriangle->Use();
		instance.meshTriangle->ModifyData(0, 0, 9 * sizeof(float), v);

		if(filled)
			instance.meshTriangle->Draw(GPU::DrawingType::TRIANGLES);
		else
			instance.meshTriangle->Draw(GPU::DrawingType::LINE_LOOP);
	}

	void Primitives3D::DrawCircle(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color, const bool filled)
	{
		auto instance = Instance();

		if (!instance.Setup(pos, size, eulerAngles, color))
			return;

		if(filled)
		{
			instance.meshCircle->Use();
			instance.meshCircle->Draw(GPU::DrawingType::TRIANGLE_FAN);
		}
		else
		{
			instance.meshUnfilledCircle->Use();
			instance.meshUnfilledCircle->Draw(GPU::DrawingType::LINE_LOOP);
		}
	}

	Primitives3D& Primitives3D::Instance()
	{
		static Primitives3D* instance = new Primitives3D();

		return *instance;
	}

	void Primitives3D::Init()
	{
		const std::string vertShader = {
			"#version 330 core\n"
			"layout(location = 0) in vec3 vertex;\n"
			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = projection * view * model * vec4(vertex, 1.0f);\n"
			"}"
		};

		const std::string fragShader = {
			"#version 330 core\n"
			"out vec4 colorOut;\n"
			"uniform vec4 color;\n"
			"void main()\n"
			"{\n"
			"	colorOut = vec4(color);\n"
			"}"
		};

		shader = GPU::ShaderPtr(new GPU::Shader(vertShader, fragShader, ""));

		meshPoint = Utils::Generator::Generate3DPoint();
		meshLine = Utils::Generator::Generate3DLine();
		meshCube = Utils::Generator::Generate3DCube();
		meshUnfilledCube = Utils::Generator::Generate3DCube(GPU::DataUse::STATIC_DRAW, false);
		meshRect = Utils::Generator::Generate3DRect();
		meshUnfilledRect = Utils::Generator::Generate3DRect(GPU::DataUse::STATIC_DRAW, false);
		meshSphere = Utils::Generator::Generate3DSphere(GPU::DataUse::STATIC_DRAW, 40);
		meshUnfilledSphere = Utils::Generator::Generate3DSphere(GPU::DataUse::STATIC_DRAW, 41, false);
		meshTriangle = Utils::Generator::Generate3DTriangle();
		meshCircle = Utils::Generator::Generate3DCircle(40);
		meshUnfilledCircle = Utils::Generator::Generate3DCircle(40, GPU::DataUse::STATIC_DRAW, false);	

		Debug::Logging::Log("[Primitives3D]: Initialized", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	void Primitives3D::Release()
	{
		meshCube.~shared_ptr();
		meshLine.~shared_ptr();
		meshPoint.~shared_ptr();
		meshRect.~shared_ptr();
		meshSphere.~shared_ptr();
		meshTriangle.~shared_ptr();
		meshCircle.~shared_ptr();
		meshUnfilledCube.~shared_ptr();
		meshUnfilledSphere.~shared_ptr();
		meshUnfilledRect.~shared_ptr();
		meshUnfilledCircle.~shared_ptr();
		shader.~shared_ptr();

		meshCube = nullptr;
		meshLine = nullptr;
		meshPoint = nullptr;
		meshRect = nullptr;
		meshSphere = nullptr;
		meshTriangle = nullptr;
		meshCircle = nullptr;
		meshUnfilledCube = nullptr;
		meshUnfilledSphere = nullptr;
		meshUnfilledRect = nullptr;
		meshUnfilledCircle = nullptr;
		shader = nullptr;

		Debug::Logging::Log("[Primitives3D]: Released", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	bool Primitives3D::Setup(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec4& color)
	{
		const Camera::Camera3DPtr cam = Camera::Camera3D::GetCurrentCamera();

		if (cam == nullptr)
		{
			Debug::Logging::Log("[Primitives3D]: Attempt to draw a 3D primitive  without a camera", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
			return false;
		}

		glm::mat4 model(glm::mat4(1.0f));

		model = glm::translate(model, position);

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));

		model = glm::rotate(model, glm::radians(eulerAngles.x), { 1.0f, 0.0f, 0.0f });
		model = glm::rotate(model, glm::radians(eulerAngles.y), { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, glm::radians(eulerAngles.z), { 0.0f, 0.0f, 1.0f });

		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));

		model = glm::scale(model, size);

		shader->Use();
		shader->SetMat4("model", model);
		shader->SetMat4("projection", cam->GetProjectionMatrix());
		shader->SetMat4("view", cam->GetViewMatrix());
		shader->SetVec3("color", color);

		return true;
	}
}}}