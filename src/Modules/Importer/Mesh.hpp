#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Importer {

    class Mesh
    {
        friend class Importer;
    private:
        glm::vec3 minBox;
        glm::vec3 maxBox;

        GPU::VertexPtr mesh;

        int materialIndex = -1;

        std::string name;
    public:
        glm::vec3 GetMinBox() const;
        glm::vec3 GetMaxBox() const;

        void SetMinBox(const glm::vec3 vec);
        void SetMaxBox(const glm::vec3 vec);
    
        void SetMesh(GPU::VertexPtr mesh);
        GPU::VertexPtr GetMesh() const;

        void SetMaterialIndex(int index);
        int GetMaterialIndex() const;

        void SetName(const std::string& name);
        std::string GetName() const;
    };

    typedef std::shared_ptr<Mesh> MeshPtr;
}}}