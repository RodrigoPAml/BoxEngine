#include <BoxEngine.hpp>
#include "TextureRenderer.hpp"

namespace BoxEngine {
namespace Modules {
namespace Drawing {

	void TextureRenderer::Draw(const GPU::TexturePtr texture, const glm::vec2& position, const glm::vec2& size, const glm::vec3& color, const float rotation, const float colorWeight)
	{
		const Camera::Camera2DPtr cam = Camera::Camera2D::GetCurrentCamera();

		if (cam == nullptr)
		{
			Debug::Logging::Log("[TextureRenderer]: Attempt to draw a texture without a camera", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
			return;
		}

		if (texture == nullptr)
		{
			Debug::Logging::Log("[TextureRenderer]: Attempt to draw an null texture", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
			return;
		}

		auto instance = Instance();

		if (instance.shader == nullptr || instance.shaderMultisampled == nullptr)
		{
			Debug::Logging::Log("[TextureRenderer]: Attempt to draw an texture without a shader", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
			return;
		}

		if (instance.mesh == nullptr)
		{
			Debug::Logging::Log("[TextureRenderer]: Attempt to draw an texture without a mesh", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
			return;
		}

		glm::mat4 model(glm::mat4(1.0f));

		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.0f));

		texture->Use(0);

		if (texture->IsMultiSampled())
		{
			instance.shaderMultisampled->Use();

			instance.shaderMultisampled->SetMat4("model", model);
			instance.shaderMultisampled->SetMat4("projection", cam->GetOrthoMatrix());
			instance.shaderMultisampled->SetInt("image", 0);
			instance.shaderMultisampled->SetVec3("texColor", color);
			instance.shaderMultisampled->SetFloat("colorWeight", colorWeight);
			instance.shaderMultisampled->SetXY("texSize", texture->GetSize().x, texture->GetSize().y);
			instance.shaderMultisampled->SetInt("samples", texture->GetNumberOfSamples());
		}
		else
		{
			instance.shader->Use();

			instance.shader->SetMat4("model", model);
			instance.shader->SetVec3("color", color);
			instance.shader->SetFloat("colorWeight", colorWeight);
			instance.shader->SetMat4("projection", cam->GetOrthoMatrix());
			instance.shader->SetInt("image", 0);
		}

		instance.mesh->Use();
		instance.mesh->Draw(GPU::DrawingType::TRIANGLES);
	}

	TextureRenderer& TextureRenderer::Instance()
	{
		static TextureRenderer* instance = new TextureRenderer();

		return *instance;
	}

	void TextureRenderer::Init()
	{
		const std::string vertShader = { 
			"#version 330 core\n"
			"layout(location = 0) in vec4 vertex;\n"
			"out vec2 uv;\n"
			"uniform mat4 model;\n"
			"uniform mat4 projection;\n"
			"void main()\n"
			"{\n"
			"  uv = vertex.zw;\n"
			"  gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
			"}"
		};

		const std::string fragShader = {
			"#version 330 core\n"
			"layout(location = 0) out vec4 outColor;\n"
			"in vec2 uv;\n"
			"uniform vec3 color;\n"
			"uniform sampler2D image;\n"
			"uniform float colorWeight;\n"
			"void main()\n"
			"{\n"
			"  vec4 texFrag = texture(image, uv);\n"
			"  outColor =  vec4((texFrag.xyz * (1 - colorWeight)) + (color*colorWeight), texFrag.w);\n"
			"}"
		};

		const std::string fragShaderMS = {
			"#version 330 core\n"
			"layout(location = 0) out vec4 outColor;\n"
			"in vec2 uv;\n"

			"uniform vec3 texColor;\n"
			"uniform sampler2DMS image;\n"
			"uniform float colorWeight;\n"
			"uniform vec2 texSize;\n"
			"uniform int samples;\n"

			"void main()\n"
			"{\n"
			"  vec4 color = vec4(0.0);\n"
			"  for(int i = 0; i < samples; i++)\n"
			"  {\n"
			"    color += texelFetch(image, ivec2(uv.x*texSize.x, uv.y*texSize.y), i);\n"
			"  }\n"
			"  color = (color/samples);\n"
			"  outColor =  vec4((color.xyz * (1 - colorWeight)) + (texColor*colorWeight), color.w);\n"
			"}"
		};

		this->shader = GPU::ShaderPtr(new GPU::Shader(vertShader, fragShader, ""));
		this->shaderMultisampled = GPU::ShaderPtr(new GPU::Shader(vertShader, fragShaderMS, ""));

		float vertices[] =
		{
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		const GPU::VertexElement element(4);
		const GPU::VertexDescriptor descriptor({{{element}, vertices, GPU::DataUse::STATIC_DRAW, GPU::VertexBufferType::FLOAT}}, 6);

		this->mesh = GPU::VertexPtr(new GPU::Vertex(descriptor));

		Debug::Logging::Log("[TextureRenderer]: Initialized", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	void TextureRenderer::Release()
	{
		mesh = nullptr;
		shader = nullptr;
		shaderMultisampled = nullptr;

		Debug::Logging::Log("[TextureRenderer]: Released", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}
}}}