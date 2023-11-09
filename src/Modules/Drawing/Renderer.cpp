#include <BoxEngine.hpp>
#include "Renderer.hpp"

namespace BoxEngine {
namespace Modules {
namespace Drawing {

	void Renderer::Draw(const Importer::ObjectPtr obj)
	{
		const Camera::Camera3DPtr cam = Camera::Camera3D::GetCurrentCamera();

		if (obj == nullptr)
		{
			Debug::Logging::Log("[TextureRenderer]: Attempt to draw an empty object", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
			return;
		}

		if (cam == nullptr)
		{
			Debug::Logging::Log("[Renderer]: Attempt to draw an object without a camera", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
			return;
		}

		auto instance = Instance();

		if (instance.shader == nullptr)
		{
			Debug::Logging::Log("[Renderer]: Attempt to draw an object without a shader", Debug::LogSeverity::Warning, Debug::LogOrigin::Engine);
			return;
		}
		
		for (const Importer::MeshPtr& mesh : obj->meshes)
		{
			int materialIndex = mesh->GetMaterialIndex();

			if (materialIndex > 0)
			{
				Importer::MaterialPtr mtl = obj->materials[materialIndex];
				GPU::TexturePtr albedoTexture = mtl->GetAlbedoTexture();

				if (albedoTexture == nullptr)
				{
					instance.shaderMtl->Use();
					instance.shaderMtl->SetMat4("model", glm::mat4(1.0f));
					instance.shaderMtl->SetMat4("projection", cam->GetProjectionMatrix());
					instance.shaderMtl->SetMat4("view", cam->GetViewMatrix());
					instance.shaderMtl->SetVec3("color", mtl->GetColor());
				}
				else
				{
					instance.shader->Use();
					instance.shader->SetMat4("model", glm::mat4(1.0f));
					instance.shader->SetMat4("projection", cam->GetProjectionMatrix());
					instance.shader->SetMat4("view", cam->GetViewMatrix());

					albedoTexture->Use(1);
					instance.shader->SetInt("tex", 1);
				}

				mesh->GetMesh()->Use();
				mesh->GetMesh()->Draw(GPU::DrawingType::TRIANGLES);
			}
		}
	}

	Renderer& Renderer::Instance()
	{
		static Renderer* instance = new Renderer();

		return *instance;
	}

	void Renderer::Init()
	{
		const std::string vertShader = { 
			"#version 330 core\n"
			
			"layout(location = 0) in vec3 vertex;\n"
			"layout(location = 1) in vec3 normal;\n"
			"layout(location = 2) in vec2 uv;\n"

			"out vec3 interpNormal;\n"
			"out vec2 interpUV; \n"

			"uniform mat4 projection;\n"
			"uniform mat4 view;\n"

			"void main()\n"
			"{\n"
			"	interpNormal = normal;\n"
			"	interpUV = uv;\n"

			"  gl_Position = projection * view * vec4(vertex, 1.0f);\n"
			"}"
		};

		const std::string fragShader = {
			"#version 330 core\n"

			"layout(location = 0) out vec4 outColor;\n"

			"in vec3 interpNormal;\n"
			"in vec2 interpUV;\n"

			"uniform sampler2D tex;\n"

			"void main()\n"
			"{\n"
			"  float diff = max(dot(interpNormal, vec3(0.5, 1, 0.5)), 0.0);\n"
			"  vec4 texFrag = texture(tex, interpUV);\n"
			"  vec3 color = texFrag.xyz + vec3(0.2f);\n"
			"  outColor = vec4(color * diff, texFrag.w);\n"
			"}"
		};

		const std::string fragShaderMtl = {
			"#version 330 core\n"

			"layout(location = 0) out vec4 outColor;\n"

			"in vec3 interpNormal;\n"
			"in vec2 interpUV;\n"

			"uniform vec3 color;\n"

			"void main()\n"
			"{\n"
			"  outColor = vec4(color, 1.0f);\n"
			"}"
		};

		this->shader = GPU::ShaderPtr(new GPU::Shader(vertShader, fragShader, ""));
		this->shaderMtl = GPU::ShaderPtr(new GPU::Shader(vertShader, fragShaderMtl, ""));

		Debug::Logging::Log("[Renderer]: Initialized", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}

	void Renderer::Release()
	{

		this->shader = nullptr;
		this->shaderMtl = nullptr;

		Debug::Logging::Log("[Renderer]: Released", Debug::LogSeverity::Notify, Debug::LogOrigin::Engine);
	}
}}}