#include <BoxEngine.hpp>
#include "Vertex.hpp"

namespace BoxEngine {
namespace Modules {
namespace GPU {

	int Vertex::TotalInstances = 0;

	Vertex::Vertex(const VertexDescriptor& descriptor)
	{
		Vertex::TotalInstances++;

		if(descriptor.buffers.size() == 0 || descriptor.verticesCount == 0)
			Debug::Logging::LogException("[Vertex]: Number of buffer or vertices can't be zero", Debug::LogOrigin::Engine);

		this->vao = 0;
		this->vaoSize = descriptor.verticesCount;

		this->ibo = 0;
		this->iboSize = 0;

		this->vbos = new unsigned int[descriptor.buffers.size()];
		this->vbosSize = descriptor.buffers.size();

		// First create an Vertex Array Object
		glGenVertexArrays(1, &this->vao);

		if (this->vao == 0)
			Debug::Logging::LogException("[Vertex]: Failed to create Vao", Debug::LogOrigin::Engine);

		glBindVertexArray(this->vao);

		// Then allocate the Vertex Buffers Objects
		glGenBuffers(descriptor.buffers.size(), this->vbos);

		for (int i = 0; i < descriptor.buffers.size(); i++)
		{
			if (this->vbos[i] == 0)
				Debug::Logging::LogException("[Vertex]: Failed to create Vbo", Debug::LogOrigin::Engine);
		}

		// Now for each buffer we allocate the required memory.
		for(int i = 0; i < descriptor.buffers.size(); i++)
		{
			if(descriptor.buffers[i].elements.size() == 0)
				Debug::Logging::LogException("[Vertex]: Number of elements of buffer can't be empty", Debug::LogOrigin::Engine);

			int elementsSize = 0;
			auto type = descriptor.buffers[i].type;

			for(const VertexElement& element : descriptor.buffers[i].elements)
			{
				if (element.count == 0)
					Debug::Logging::LogException("[Vertex]: Element of buffer can't have zero size", Debug::LogOrigin::Engine);

				// Elements size will be the all elements multiplied by the ocurrences ex: (3 * FLOAT_SIZE + 2 * FLOAT_SIZE)
				elementsSize += GetSizeOfVertexBufferType(type) * element.count;
			}

			// The buffer size is the elements size multiplied by how many elements are.
			int bufferSize = elementsSize * descriptor.verticesCount;
			glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);

			// Allocate memory for the buffer
			glBufferData(GL_ARRAY_BUFFER, bufferSize, descriptor.buffers[i].data, (GLenum)descriptor.buffers[i].use);
		}

		int index = 0;
		// Here we bind the elements layout into the buffers
		for(int i = 0; i < descriptor.buffers.size(); i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);

			int elementsSize = 0, currentOffset = 0;
			auto type = descriptor.buffers[i].type;

			for(const VertexElement& element : descriptor.buffers[i].elements)
			{
				elementsSize += GetSizeOfVertexBufferType(type) * element.count;
			}

			for(const VertexElement element : descriptor.buffers[i].elements)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.count, (GLenum)type, (GLboolean)element.isNormalized, elementsSize, (void*)currentOffset);
					
				currentOffset += element.count * GetSizeOfVertexBufferType(type);

				index++;
			}
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		Debug::Logging::Log("[Vertex]: Vertex array created with id " + std::to_string(this->vao), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

	Vertex::Vertex(const VertexDescriptor& descriptor, const VertexIndicesDescriptor& indicesDescriptor) : Vertex(descriptor)
	{
		if (indicesDescriptor.count == 0 || indicesDescriptor.indices == nullptr)
			Debug::Logging::LogException("[Vertex]: Indices can't be empty or null", Debug::LogOrigin::Engine);

		glBindVertexArray(this->vao);

		this->iboSize = indicesDescriptor.count;
		glGenBuffers(1, &this->ibo);

		if (this->ibo == 0)
			Debug::Logging::LogException("[Vertex]: Failed to create Ibo", Debug::LogOrigin::Engine);

		unsigned int IndiceBufferSize = GetSizeOfVertexBufferType(VertexBufferType::UINT) * indicesDescriptor.count;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndiceBufferSize, indicesDescriptor.indices, (GLenum)indicesDescriptor.use);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		Debug::Logging::Log("[Vertex]: Indexed vertex array created with id " + std::to_string(this->vao), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

	Vertex::~Vertex()
	{
		Vertex::TotalInstances--;

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (this->vao != 0)
		{
			glDeleteVertexArrays(1, &this->vao);
			glDeleteBuffers(this->vbosSize, this->vbos);

			Debug::Logging::Log("[Vertex]: Vertex array deleted with id " + std::to_string(this->vao), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
		}

		if(this->ibo != 0)
			glDeleteBuffers(1, &this->ibo);

		if (this->vbos != nullptr)
		{
			delete[] this->vbos;
			this->vbos = nullptr;
		}
	}

	void Vertex::Use() const
	{
		if (this->vao == 0)
			Debug::Logging::LogException("[Vertex]: Can't activate an empty vertex array", Debug::LogOrigin::Engine);

		glBindVertexArray(this->vao);
	}

	int Vertex::GetId() const
	{
		return this->vao;
	}

	void Vertex::Draw(const DrawingType& drawingType) const
	{
		if (this->vao == 0)
			Debug::Logging::LogException("[Vertex]: Can't draw an empty vertex array", Debug::LogOrigin::Engine);

		if(this->ibo != 0)
			glDrawElements((GLenum)drawingType, this->iboSize, (GLenum)VertexBufferType::UINT, 0);
		else 
			glDrawArrays((GLenum)drawingType, 0, this->vaoSize);
	}

	void Vertex::ModifyData(const unsigned int buffer, const unsigned int start, const unsigned int tam, void* data) const
	{
		if (this->vao == 0)
			Debug::Logging::LogException("[Vertex]: Can't activate empty vertex array", Debug::LogOrigin::Engine);

		if(buffer < 0 || buffer >= vbosSize)
			Debug::Logging::LogException("[Vertex]: Can't modify buffer out of index", Debug::LogOrigin::Engine);

		glBindBuffer(GL_ARRAY_BUFFER, this->vbos[buffer]);
		glBufferSubData(GL_ARRAY_BUFFER, start, tam, data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vertex::ClearCurrentActive()
	{
		glBindVertexArray(0);
	}
	
	int Vertex::GetInstanceCount()
	{
		return Vertex::TotalInstances;
	}
}}}