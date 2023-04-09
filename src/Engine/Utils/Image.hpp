#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Utils {

	/// <summary>
	/// Represents a image in CPU memory.
	/// </summary>
	class Image
	{
	private:
		unsigned char* data;

		glm::vec<2, int> size;

		GPU::TextureFormat format;

		std::string path;
	public:
		Image(const std::string& path, bool flipVertically = false);
		~Image();

		void SetSize(const glm::vec<2, int>& size);
		void SetData(unsigned char* data);
		void SetFormat(const GPU::TextureFormat& format);

		glm::vec<2, int> GetSize() const;
		unsigned char* GetData() const;
		GPU::TextureFormat GetFormat() const;
		std::string GetLoadedPath() const;
	};

	typedef std::shared_ptr<Image> ImagePtr;
}}