#include <BoxEngine.hpp>
#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace BoxEngine {
namespace Modules {
namespace Utils {

	Image::Image(const std::string& path, bool flipVertically)
	{
		stbi_set_flip_vertically_on_load(flipVertically);

		int numComponents = 0;
		this->data = stbi_load(path.c_str(), &this->size.x, &this->size.y, &numComponents, 0);
		this->path = path;

		if (!this->data && stbi_failure_reason())
			Debug::Logging::LogException("[Image]: Failed to open texture: " + std::string(stbi_failure_reason()), Debug::LogOrigin::Engine);

		if (!this->data)
			Debug::Logging::LogException("[Image]: Failed to open texture: " + path, Debug::LogOrigin::Engine);
		
		if (this->size.x <= 0 || this->size.y <= 0)
		{
			if (this->data != nullptr)
				delete[] this->data;

			Debug::Logging::LogException("[Image]: Failed to open texture " + path + " because size can't be zero or negative", Debug::LogOrigin::Engine);
		}

		switch (numComponents)
		{
			case 1:
				this->format = GPU::TextureFormat::R;
				break;
			case 3:
				this->format = GPU::TextureFormat::RGB;
				break;
			case 4:
				this->format = GPU::TextureFormat::RGBA;
				break;
			default:
			{
				if (this->data != nullptr)
					delete[] this->data;
			
				Debug::Logging::LogException("[Image]: Failed to open texture " + path + " because invalid format with " + std::to_string(numComponents) + " components", Debug::LogOrigin::EngineInternal);
			}
		}
	
		Debug::Logging::Log("[Image]: Image " + path + " was opened", Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

	Image::~Image()
	{
		Debug::Logging::Log("[Image]: Image " + path + " was released", Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);

		if (this->data != nullptr)
			delete[] this->data;
	}

	void Image::SetSize(const glm::vec<2, int>& size)
	{
		this->size = size;
	}

	void Image::SetData(unsigned char* data)
	{
		this->data = data;
	}

	void Image::SetFormat(const  GPU::TextureFormat& format)
	{
		this->format = format;
	}

	glm::vec<2, int> Image::GetSize() const
	{
		return this->size;
	}

	unsigned char* Image::GetData() const
	{
		return this->data;
	}

	GPU::TextureFormat Image::GetFormat() const
	{
		return this->format;
	}

	GPU::TextureInternalFormat Image::GetInternalFormat()
	{
		switch (this->format)		
		{	
		case GPU::TextureFormat::RGB:
			return GPU::TextureInternalFormat::RGB;
		case GPU::TextureFormat::RG:
			return GPU::TextureInternalFormat::RG;
		case GPU::TextureFormat::R:
			return GPU::TextureInternalFormat::R;
		case GPU::TextureFormat::RGBA:
			return GPU::TextureInternalFormat::RGBA;
		default:
			break;
		}

		return GPU::TextureInternalFormat::RGB;
	}

	std::string Image::GetLoadedPath() const
	{
		return this->path;
	}
}}}