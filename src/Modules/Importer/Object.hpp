#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Importer {

    class Object
    {
        friend class Importer;
    public:
        std::string path;
        std::string basePath;

        std::vector<GPU::VertexPtr> vertexRefs;
        std::vector<GPU::TexturePtr> textureRefs;

        std::vector<MeshPtr> meshes;
        std::vector<MaterialPtr> materials;
    };

    typedef std::shared_ptr<Object> ObjectPtr;
}}}
