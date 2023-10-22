#include <BoxEngine.hpp>
#include "Importer.hpp"

namespace BoxEngine {
namespace Modules {
namespace Importer {

    ObjectPtr Importer::Load(const std::string& path)
    {
        srand(time(NULL));

        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(
            path, 
            aiProcess_Triangulate | 
            aiProcess_GenSmoothNormals | 
            aiProcess_GenNormals | 
            aiProcess_OptimizeMeshes | 
            aiProcess_GenBoundingBoxes |
            aiProcess_GenUVCoords
        );

        ObjectPtr object = ObjectPtr(new Object());
        object->basePath = path;

        if(scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            return nullptr;
        else
        {
            ProcessNode(scene->mRootNode, scene, object);
            ProcessMaterials(scene, object);
        }

        return object;
    }

    void Importer::ProcessNode(aiNode* node, const aiScene* scene, ObjectPtr object)
    {
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
            ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene, object);

        for(unsigned int i = 0; i < node->mNumChildren; i++)
           ProcessNode(node->mChildren[i], scene, object);
    }

    void Importer::ProcessMesh(aiMesh* mesh, const aiScene* scene, ObjectPtr object)
    {
        if(!mesh->HasPositions() || mesh->mNumVertices == 0 || mesh->mNumFaces == 0)
            return;

        // 9 vertices for position per face
        // 9 vertices for normals per face
        // 6 vertitices for uvs per face
        int totalSize = (mesh->mNumFaces * 9) + (mesh->mNumFaces * 9) + (mesh->mNumFaces * 6);
        unsigned int index = 0;

        unsigned int* indices = new unsigned int[totalSize];

        for(int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            indices[index++] = face.mIndices[0];
            indices[index++] = face.mIndices[1];
            indices[index++] = face.mIndices[2];
        }

        float* data = new float[totalSize];
        index = 0;

        for (int i = 0; i < mesh->mNumVertices; i++)
        {
            aiVector3D vert = mesh->mVertices[i];
            aiVector3D normal = mesh->mNormals[i];
            aiVector3D uv = mesh->mTextureCoords[0] != nullptr ?
                mesh->mTextureCoords[0][i]
                : aiVector3D(0, 0, 0);

            data[index++] = vert.x;
            data[index++] = vert.y;
            data[index++] = vert.z;

            data[index++] = normal.x;
            data[index++] = normal.y;
            data[index++] = normal.z;

            data[index++] = uv.x;
            data[index++] = uv.y;
        }

        // Indices configuration
        GPU::VertexIndicesDescriptor idescriptor;

        idescriptor.count = mesh->mNumFaces * 3;
        idescriptor.indices = indices;

        // Vertex layout
        GPU::VertexElement element1(3);
        GPU::VertexElement element2(3);
        GPU::VertexElement element3(2);

        GPU::VertexDescriptor descriptor = GPU::VertexDescriptor({ {{element1, element2, element3}, data, GPU::DataUse::STATIC_DRAW, GPU::VertexBufferType::FLOAT} }, mesh->mNumFaces*3);
        GPU::VertexPtr vertex = GPU::VertexPtr(new GPU::Vertex(descriptor, idescriptor));

        delete[] data;
        delete[] indices;

        MeshPtr m = MeshPtr(new Mesh());

        m->maxBox = { mesh->mAABB.mMax.x,  mesh->mAABB.mMax.y,  mesh->mAABB.mMax.z };
        m->minBox = { mesh->mAABB.mMin.x,  mesh->mAABB.mMin.y,  mesh->mAABB.mMin.z };
        m->materialIndex = mesh->mMaterialIndex;
        m->name = mesh->mName.C_Str();
        m->mesh = vertex;
        
        object->meshes.push_back(m);
    }

    void Importer::ProcessMaterials(const aiScene* scene, ObjectPtr object)
    {
        using namespace Utils;

        std::map<std::string, GPU::TexturePtr> textures;

        aiString* path = new aiString("");
        for (int i = 0; i < scene->mNumMaterials; i++)
        {
            aiMaterial* material = scene->mMaterials[i];

            MaterialPtr mtl = MaterialPtr(new Material());
            
            aiColor4D diffuseColor(1.0f, 1.0f, 1.0f, 1.0f); 
            if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor)) 
                mtl->color = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);

            if (material->GetTexture(aiTextureType_DIFFUSE, 0, path) == AI_SUCCESS)
            {
                std::string texturePath = path->C_Str();

                if (!textures.contains(texturePath))
                {
                    auto image = ImagePtr(new Image(object->basePath + "//" + texturePath));
                    auto texture = GPU::TexturePtr(new GPU::Texture(GPU::TextureDataConfiguration(), image));

                    textures[texturePath] = texture;
                }

                mtl->albedoTexture = textures[texturePath];
            }

            object->materials.push_back(mtl);
        }
    }
}}}