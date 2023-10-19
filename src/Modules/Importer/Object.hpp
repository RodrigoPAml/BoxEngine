#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Importer {

    class Object
    {
        friend class Importer;
    public:
        std::string basePath;

        std::vector<MeshPtr> meshes;
        std::vector<MaterialPtr> materials;
    };

    typedef std::shared_ptr<Object> ObjectPtr;
}}}
