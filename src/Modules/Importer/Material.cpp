#include <BoxEngine.hpp>
#include "Material.hpp"

namespace BoxEngine {
namespace Modules {
namespace Importer {
	
	Material::Material()
	{
		this->color = { 1, 1, 1 };
	}

	Material::~Material()
	{
	}

	void Material::SetAlbedoTexture(GPU::TexturePtr texture)
	{
		this->albedoTexture = texture;
	}

	GPU::TexturePtr Material::GetAlbedoTexture() const
	{
		return this->albedoTexture.lock();
	}

	void Material::SetColor(const glm::vec3& color)
	{
		this->color = color;
	}

	glm::vec3 Material::GetColor() const
	{
		return this->color;
	}

	void Material::SetName(const std::string name)
	{
		this->name;
	}

	std::string Material::GetName() const
	{
		return this->name;
	}
}}}