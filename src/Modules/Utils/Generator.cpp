#include <BoxEngine.hpp>
#include "Generator.hpp"

namespace BoxEngine {
namespace Modules {
namespace Utils {
namespace Generator {

	GPU::VertexPtr Generate2DPoint(const GPU::DataUse use)
	{
		using namespace GPU;

		float verticesPoint[] = { 0.0f, 0.0f };

		VertexElement element(2);
		VertexDescriptor descriptor({{{element}, verticesPoint, use, GPU::VertexBufferType::FLOAT}}, 1);

		return VertexPtr(new Vertex(descriptor));
	}

	GPU::VertexPtr Generate2DLine(const GPU::DataUse use)
	{
		using namespace GPU;

		float verticesLine[] = {1.0f, 1.0f, 2.0f, 2.0f};

		VertexElement element(2);
		VertexDescriptor descriptor({{{element}, verticesLine, use, GPU::VertexBufferType::FLOAT}}, 2);

		return GPU::VertexPtr(new Vertex(descriptor));
	}

	GPU::VertexPtr Generate2DRect(const GPU::DataUse use, const bool filled)
	{
		using namespace GPU;

		float verticesRect[] =
		{
			1.0f,  1.0f,
			1.0f, -1.0f,
			-1.0f, -1.0f,
			-1.0f,  1.0f,
		};

		unsigned int indicesRect[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		unsigned int indicesUnfilledRect[] =
		{
			0, 1, 2, 3
		};

		VertexElement element(2);
		VertexDescriptor descriptor(
			{{{element}, verticesRect, use, GPU::VertexBufferType::FLOAT}},
			4
		);

		if (filled)
		{
			VertexIndicesDescriptor indicesDescriptor(indicesRect, 6, use);

			return GPU::VertexPtr(new Vertex(descriptor, indicesDescriptor));
		}
		else
		{
			VertexIndicesDescriptor indicesDescriptor(indicesUnfilledRect, 4, use);

			return GPU::VertexPtr(new Vertex(descriptor, indicesDescriptor));
		}
	}

	GPU::VertexPtr Generate2DCircle(const unsigned int nsegments, const GPU::DataUse use, const bool filled)
	{
		using namespace GPU;

		if (filled)
		{
			float* verticesCircle = new float[(nsegments + 1) * 2]();

			verticesCircle[0] = 0.0f;
			verticesCircle[1] = 0.0f;

			for (int i = 1; i < nsegments + 1; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(nsegments - 1);

				verticesCircle[i * 2] = cosf(theta);
				verticesCircle[(i * 2) + 1] = sinf(theta);
			}

			VertexElement element(2);
			VertexDescriptor descriptor(
				{{{element}, verticesCircle, use, VertexBufferType::FLOAT}},
				nsegments + 1
			);

			GPU::VertexPtr arr = GPU::VertexPtr(new Vertex(descriptor));

			delete[] verticesCircle;

			return arr;
		}
		else
		{
			float* verticesCircle = new float[(nsegments) * 2]();

			for (int i = 0; i < nsegments; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(nsegments);

				verticesCircle[i * 2] = cosf(theta);
				verticesCircle[(i * 2) + 1] = sinf(theta);
			}

			VertexElement element(2);
			VertexDescriptor descriptor(
				{{{element}, verticesCircle, use, VertexBufferType::FLOAT}},
				nsegments
			);

			GPU::VertexPtr arr = GPU::VertexPtr(new Vertex(descriptor));

			delete[] verticesCircle;

			return arr;
		}
	}

	GPU::VertexPtr Generate2DTriangle(const GPU::DataUse use, const bool filled)
	{
		using namespace GPU;

		float verticeTriBase[] =
		{
			-0.5f, -0.5f,
				0.5f, -0.5f,
				0.0f,  0.5f,
		};

		VertexElement element(2);
		VertexDescriptor descriptor(
			{{{element}, verticeTriBase, use, VertexBufferType::FLOAT}},
			3
		);

		return GPU::VertexPtr(new Vertex(descriptor));
	}

	GPU::VertexPtr Generate3DPoint(const GPU::DataUse use)
	{
		using namespace GPU;

		float verticesPoint[] =
		{
			0.0f, 0.0f, 0.0f
		};

		VertexElement element(3);
		VertexDescriptor descriptor(
			{{{element}, verticesPoint, use, VertexBufferType::FLOAT}},
			1
		);

		return GPU::VertexPtr(new Vertex(descriptor));
	}

	GPU::VertexPtr Generate3DLine(const GPU::DataUse use)
	{
		using namespace GPU;

		float verticesLine[] =
		{
			1.0f, 1.0f, 1.0f,
			2.0f, 2.0f, 1.0f
		};

		VertexElement element(3);
		VertexDescriptor descriptor(
			{{{element}, verticesLine, use, VertexBufferType::FLOAT}},
			2
		);

		return GPU::VertexPtr(new Vertex(descriptor));
	}

	GPU::VertexPtr Generate3DRect(const GPU::DataUse use, const bool filled)
	{
		using namespace GPU;

		float verticesRect[] =
		{
			0.5f,  0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		unsigned int indicesRect[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		unsigned int indicesUnfilledRect[] =
		{
			0, 1, 2, 3
		};

		VertexElement element(3);
		VertexDescriptor descriptor(
			{{{element}, verticesRect, use, VertexBufferType::FLOAT}},
			4
		);

		if (filled)
		{
			VertexIndicesDescriptor indicesDescriptor(indicesRect, 6, use);

			return GPU::VertexPtr(new Vertex(descriptor, indicesDescriptor));
		}
		else
		{
			VertexIndicesDescriptor indicesDescriptor(indicesUnfilledRect, 4, use);

			return GPU::VertexPtr(new Vertex(descriptor, indicesDescriptor));
		}
	}

	GPU::VertexPtr Generate3DCircle(const unsigned int nsegments, const GPU::DataUse use, const bool filled)
	{
		using namespace GPU;

		if (filled)
		{
			float* verticesCircle = new float[(nsegments + 1) * 3]();

			verticesCircle[0] = 0.0f;
			verticesCircle[1] = 0.0f;
			verticesCircle[2] = 0.0f;

			for (unsigned int i = 1; i < nsegments + 1; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(nsegments - 1);

				verticesCircle[i * 3] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 1] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = 0;
			}

			VertexElement element(3);
			VertexDescriptor descriptor(
				{{{element}, verticesCircle, use, VertexBufferType::FLOAT}},
				nsegments + 1
			);

			GPU::VertexPtr arr = GPU::VertexPtr(new Vertex(descriptor));

			delete[] verticesCircle;

			return arr;
		}
		else
		{
			float* verticesCircle = new float[(nsegments) * 3]();

			for (unsigned int i = 0; i < nsegments; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(nsegments);

				verticesCircle[i * 3] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 1] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = 0;
			}

			VertexElement element(3);
			VertexDescriptor descriptor(
				{{{element}, verticesCircle, use, VertexBufferType::FLOAT}},
				nsegments
			);

			GPU::VertexPtr arr = GPU::VertexPtr(new Vertex(descriptor));

			delete[] verticesCircle;

			return arr;
		}
	}

	GPU::VertexPtr Generate3DTriangle(const GPU::DataUse use, const bool filled)
	{
		using namespace GPU;

		float trianglesVert[] =
		{
			0.0f, 1.0f, 0.0f,
			-0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
		};

		VertexElement element(3);
		VertexDescriptor descriptor(
			{{{element}, trianglesVert, use, VertexBufferType::FLOAT}},
			3
		);

		return GPU::VertexPtr(new Vertex(descriptor));
	}

	GPU::VertexPtr Generate3DSphere(const GPU::DataUse use, const unsigned int n_segments, const bool filled)
	{
		using namespace GPU;

		if (filled)
		{
			std::vector<float> vert;
			std::vector<unsigned int> indices;

			for (unsigned int y = 0; y <= n_segments; ++y)
			{
				for (unsigned int x = 0; x <= n_segments; ++x)
				{
					float xSegment = (float)x / (float)n_segments;
					float ySegment = (float)y / (float)n_segments;

					float xPos = std::cos(xSegment * glm::pi<float>() * 2.0f) * std::sin(ySegment * glm::pi<float>());
					float yPos = std::cos(ySegment * glm::pi<float>());
					float zPos = std::sin(xSegment * glm::pi<float>() * 2.0f) * std::sin(ySegment * glm::pi<float>());

					vert.push_back(xPos * 0.5f);
					vert.push_back(yPos * 0.5f);
					vert.push_back(zPos * 0.5f);
				}
			}

			for (int y = 0; y < n_segments; ++y)
			{
				for (int x = 0; x < n_segments; ++x)
				{
					indices.push_back((y + 1) * (n_segments + 1) + x);
					indices.push_back(y * (n_segments + 1) + x);
					indices.push_back(y * (n_segments + 1) + x + 1);

					indices.push_back((y + 1) * (n_segments + 1) + x);
					indices.push_back(y * (n_segments + 1) + x + 1);
					indices.push_back((y + 1) * (n_segments + 1) + x + 1);
				}
			}

			VertexElement element(3);
			VertexDescriptor descriptor(
				{{{element}, &vert[0], use, VertexBufferType::FLOAT}},
				(unsigned int)vert.size() / 3
			);

			VertexIndicesDescriptor indicesDescriptor(&indices[0], (unsigned int)indices.size(), use);

			return GPU::VertexPtr(new Vertex(descriptor, indicesDescriptor));
		}
		else
		{
			float* verticesCircle = new float[(n_segments * 3) * 3];

			std::vector<unsigned int> indices;

			for (int i = 0; i < n_segments; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(n_segments);

				verticesCircle[i * 3] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 1] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = 0;

				indices.push_back(i);
				indices.push_back(i + 1);
			}

			indices[indices.size() - 1] = 0;

			for (int i = n_segments; i < n_segments * 2; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(n_segments);

				verticesCircle[i * 3] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3) + 1] = 0;

				indices.push_back(i);
				indices.push_back(i + 1);
			}

			indices[indices.size() - 1] = n_segments;

			for (int i = n_segments * 2; i < n_segments * 3; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(n_segments);

				verticesCircle[i * 3 + 1] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3)] = 0;

				indices.push_back(i);
				indices.push_back(i + 1);
			}

			indices[indices.size() - 1] = n_segments * 2;

			VertexElement element(3);
			VertexDescriptor descriptor(
				{{{element}, verticesCircle, use, VertexBufferType::FLOAT}},
				(unsigned int)n_segments * 3
			);

			VertexIndicesDescriptor indicesDescriptor(&indices[0], indices.size(), GPU::DataUse::STATIC_DRAW);

			GPU::VertexPtr arr = GPU::VertexPtr(new Vertex(descriptor, indicesDescriptor));

			delete[] verticesCircle;

			return arr;
		}
	}

	GPU::VertexPtr Generate3DCube(const GPU::DataUse use, const bool filled)
	{
		using namespace GPU;

		float cubeVertices[] =
		{
			-0.5, -0.5, 0.5,
			0.5, -0.5, 0.5,
			-0.5, 0.5, 0.5,
			0.5, 0.5, 0.5,
			-0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			-0.5,  0.5, -0.5,
			0.5,  0.5, -0.5,
		};

		unsigned int cubeIndices[] =
		{
			0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
		};

		unsigned int cubeUnfilledIndices[] =
		{
			0, 1, 0, 2, 0, 4, 4, 5, 5, 7, 2, 3, 3, 7, 3, 1, 1, 5, 7, 6, 4, 6, 6, 2
		};

		VertexElement element(3);
		VertexDescriptor descriptor(
			{{{element}, cubeVertices, use, VertexBufferType::FLOAT}},
			10
		);

		if (filled)
		{
			VertexIndicesDescriptor indicesDescriptor(cubeIndices, 14, use);

			return GPU::VertexPtr(new Vertex(descriptor, indicesDescriptor));
		}
		else
		{
			VertexIndicesDescriptor indicesDescriptor(cubeUnfilledIndices, 24, use);

			return GPU::VertexPtr(new Vertex(descriptor, indicesDescriptor));
		}
	}
}}}}