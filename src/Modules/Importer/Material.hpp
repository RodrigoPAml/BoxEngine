#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Importer {

    class Material
    {
        friend class Importer;
    private:
        glm::vec3 color;

        GPU::TextureRef albedoTexture;

        std::string name;
    public:
        Material();
        ~Material();

        void SetAlbedoTexture(GPU::TexturePtr texture);
        GPU::TexturePtr GetAlbedoTexture() const;

        void SetColor(const glm::vec3& color);
        glm::vec3 GetColor() const;

        void SetName(const std::string name);
        std::string GetName() const;
    };

    typedef std::shared_ptr<Material> MaterialPtr;
}}}