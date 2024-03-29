#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace GPU {

	#pragma region TextureData

	/// <summary>
	/// Configuration so send a texture in memory to GPU.
	/// </summary>
	struct TextureDataConfiguration
	{
		MinifyingFilter minifyingFilter = MinifyingFilter::LINEAR_MIPMAP_LINEAR;
		MagnificationFilter magnificationFilter = MagnificationFilter::LINEAR;

		TextureWrap textureWrapT = TextureWrap::MIRRORED_REPEAT;
		TextureWrap textureWrapS = TextureWrap::MIRRORED_REPEAT;

		TextureInternalFormat internalFormat = TextureInternalFormat::RGB;
		TexturePixelFormat pixelFormat = TexturePixelFormat::FLOAT;

		glm::vec3 borderColor = { 0, 0, 0 };
		unsigned int ansiotropicFilter = 2;
	};

	/// <summary>
	/// Configuration to create an empty multisampled texture in GPU.
	/// </summary>
	struct MultisampleTextureConfiguration
	{
		unsigned int samples = 0;
		TextureInternalFormat internalFormat = TextureInternalFormat::RGB;
		glm::vec2 size = { 0,0 };
		bool fixedSamples = false;
	};

	/// <summary>
	/// Configuration to create an empty texture in GPU.
	/// </summary>
	struct TextureConfiguration : TextureDataConfiguration
	{
		TextureFormat format = TextureFormat::RGB;

		glm::vec2 size = { 0,0 };
	};

	#pragma endregion

	#pragma region VertexData

	/// <summary>
	/// Describe an element that compose a vertex array.
	/// </summary>
	struct VertexElement
	{
		unsigned int count = 0;

		bool isNormalized = false;

		VertexElement() = default;

		VertexElement( const unsigned int count, const bool isNormalized = false)
		{
			this->count = count;
			this->isNormalized = isNormalized;
		}
	};

	/// <summary>
	/// Describes a buffer of vertices.
	/// </summary>
	struct VertexBufferDescriptor
	{
		std::vector<VertexElement> elements = std::vector<VertexElement>();

		void* data = nullptr;

		DataUse use = DataUse::STATIC_DRAW;

		VertexBufferType type = VertexBufferType::FLOAT;

		VertexBufferDescriptor() = default;

		VertexBufferDescriptor(const std::vector<VertexElement>& elements, void* data, const DataUse use, VertexBufferType type)
		{
			this->elements = elements;
			this->data = data;
			this->use = use;
			this->type = type;
		}
	};

	/// <summary>
	/// Describes a Vertex Array in GPU.
	/// </summary>
	struct VertexDescriptor
	{
		std::vector<VertexBufferDescriptor> buffers = std::vector<VertexBufferDescriptor>();

		unsigned int verticesCount = 0;

		VertexDescriptor() = default;

		VertexDescriptor(const std::vector<VertexBufferDescriptor>& buffers, const unsigned int verticesCount)
		{
			this->buffers = buffers;
			this->verticesCount = verticesCount;
		}
	};

	/// <summary>
	/// Describes a the indices of a Vertex Array.
	/// </summary>
	struct VertexIndicesDescriptor
	{
		unsigned int* indices = nullptr;

		unsigned int count = 0;

		DataUse use = DataUse::STATIC_DRAW;

		VertexIndicesDescriptor() = default;

		VertexIndicesDescriptor(unsigned int* indices, const unsigned int count, const DataUse use)
		{
			this->indices = indices;
			this->count = count;
			this->use = use;
		}
	};

	#pragma endregion 
}}}