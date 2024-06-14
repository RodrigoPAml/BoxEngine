#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Importer {

    class Object
    {
        friend class Importer;
    private:
        std::string path;
        std::string basePath;
        std::string name;

        // Temporary pointer holder
        std::vector<GPU::VertexPtr> vertexRefs;
        std::vector<GPU::TexturePtr> textureRefs;

        std::vector<MeshPtr> meshes;
        std::map<std::string, MaterialPtr> materials;
    public:
        std::string GetPath() const;
        std::string GetBasePath() const;

        std::string GetName() const;
        void SetName(std::string name);

        void ClearRefs();

        std::vector<MeshPtr> GetMeshes() const;
        std::vector<MaterialPtr> GetMaterials() const;
        MaterialPtr GetMaterial(const std::string name);
    };

    typedef std::shared_ptr<Object> ObjectPtr;
}}}
