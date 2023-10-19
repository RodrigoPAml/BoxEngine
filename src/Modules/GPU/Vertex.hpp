#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace GPU {

	/// <summary>
	/// Represents vertices in GPU.
	/// </summary>
	class Vertex
	{
	private:
		/// <summary>
		/// Vertex Array Object Id
		/// </summary>
		unsigned int vao;

		/// <summary>
		/// The number of vertices in the Vao.
		/// </summary>
		unsigned int vaoSize;

		/// <summary>
		/// Vertex Buffer Objects Ids
		/// </summary>
		unsigned int* vbos; 

		/// <summary>
		/// How many Vbos exists.
		/// </summary>
		unsigned int vbosSize;

		/// <summary>
		/// Indices Buffer Object.
		/// </summary>
		unsigned int ibo;

		/// <summary>
		/// The number of indices in the Ibo.
		/// </summary>
		unsigned int iboSize;

		static int TotalInstances;
	public:
		Vertex(const VertexDescriptor& descriptor);
		Vertex(const VertexDescriptor& descriptor, const VertexIndicesDescriptor& indicesDescriptor);
		~Vertex();

		/// <summary>
		/// Activate Vao.
		/// </summary>
		void Use() const;

		/// <summary>
		/// Draw current Vao.
		/// </summary>
		void Draw(const DrawingType& drawingType) const;

		/// <summary>
		/// To modify the data of some buffer.
		/// </summary>
		void ModifyData(const unsigned int buffer, const unsigned int start, const unsigned int tam, void* data) const;

		static void ClearCurrentActive();

		/// <summary>
		/// Get current existing vertex
		/// </summary>
		static int GetInstanceCount();
	};

	typedef std::shared_ptr<Vertex> VertexPtr;
}}}