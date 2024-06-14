#include <BoxEngine.hpp>
#include "Object.hpp"

namespace BoxEngine {
namespace Modules {
namespace Importer {
	
	std::string Object::GetPath() const
	{
		return this->path;
	}

	std::string Object::GetBasePath() const
	{
		return this->basePath;
	}

	std::string Object::GetName() const
	{
		return this->name;
	}

	void Object::SetName(std::string name)
	{
		this->name = name;
	}

	void Object::ClearRefs()
	{
		this->vertexRefs.clear();
		this->textureRefs.clear();
	}

	std::vector<MeshPtr> Object::GetMeshes() const
	{
		return this->meshes;
	}

	std::vector<MaterialPtr> Object::GetMaterials() const
	{
		std::vector<MaterialPtr> mtls;

		for (auto material : this->materials)
			mtls.push_back(material.second);

		return mtls;
	}

	MaterialPtr Object::GetMaterial(const std::string name)
	{
		if (this->materials.contains(name))
			return this->materials[name];

		return nullptr;
	}
}}}