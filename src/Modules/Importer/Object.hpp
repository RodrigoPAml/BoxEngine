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

        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;

        std::vector<MeshPtr> meshes;
        std::vector<MaterialPtr> materials;
    };

    typedef std::shared_ptr<Object> ObjectPtr;
}}}
