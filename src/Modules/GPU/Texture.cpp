#include <BoxEngine.hpp>
#include "Texture.hpp"

namespace BoxEngine {
namespace Modules {
namespace GPU {

	int Texture::TotalInstances = 0;

	Texture::Texture(const TextureDataConfiguration& configuration, Utils::ImagePtr image)
	{
		Texture::TotalInstances++;

		if (image == nullptr)
			Debug::Logging::LogException("[Texture]: Texture is null: " + image->GetLoadedPath(), Debug::LogOrigin::Engine);

		this->id = 0;
		this->size = image->GetSize();

		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)configuration.textureWrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)configuration.textureWrapT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)configuration.minifyingFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)configuration.magnificationFilter);

		if(configuration.textureWrapS == TextureWrap::CLAMP_TO_BORDER || configuration.textureWrapT == TextureWrap::CLAMP_TO_EDGE)
		{
			float color[] = { configuration.borderColor.x, configuration.borderColor.y, configuration.borderColor.z, 1.0f};
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		}

		if(configuration.ansiotropicFilter > 0 && glfwExtensionSupported("GL_ARB_texture_filter_anisotropic"))
		{
			float largest_supported_anisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
				
			unsigned int supported = std::min((unsigned int)largest_supported_anisotropy, configuration.ansiotropicFilter);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, supported);
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			(GLint)configuration.internalFormat,
			image->GetSize().x,
			image->GetSize().y,
			0, 
			(GLint)image->GetFormat(),
			(GLenum)configuration.pixelFormat,
			image->GetData()
		);

		if(configuration.minifyingFilter != MinifyingFilter::ONLY_LINEAR && configuration.minifyingFilter != MinifyingFilter::ONLY_NEAREST)
			glGenerateMipmap(GL_TEXTURE_2D);

		if (this->id == 0)
			Debug::Logging::LogException("[Texture]: Failed to create texture: " + image->GetLoadedPath(), Debug::LogOrigin::Engine);
	
		else 
			Debug::Logging::Log("[Texture]: Created with id " + std::to_string(this->id), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

	Texture::Texture(const TextureConfiguration& configuration)
	{
		Texture::TotalInstances++;

		if (configuration.size.x <= 0 || configuration.size.y <= 0)
			Debug::Logging::LogException(
				"[Texture]: Cant create. Texture have invalid size: " + 
				std::to_string(configuration.size.x) + 
				" x " +
				std::to_string(configuration.size.y),
				Debug::LogOrigin::Engine
			);

		this->id = 0;
		this->size = configuration.size;

		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)configuration.textureWrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)configuration.textureWrapT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)configuration.minifyingFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)configuration.magnificationFilter);

		if (configuration.textureWrapS == TextureWrap::CLAMP_TO_BORDER || configuration.textureWrapT == TextureWrap::CLAMP_TO_EDGE)
		{
			float color[] = { configuration.borderColor.x, configuration.borderColor.y, configuration.borderColor.z, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		}

		if (configuration.ansiotropicFilter > 0 && glfwExtensionSupported("GL_ARB_texture_filter_anisotropic"))
		{
			float largest_supported_anisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);

			unsigned int supported = std::min((unsigned int)largest_supported_anisotropy, configuration.ansiotropicFilter);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, supported);
		}

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			(GLint)configuration.internalFormat,
			this->size.x,
			this->size.y,
			0,
			(GLint)configuration.format,
			(GLenum)configuration.pixelFormat,
			nullptr
		);

		if (configuration.minifyingFilter != MinifyingFilter::ONLY_LINEAR && configuration.minifyingFilter != MinifyingFilter::ONLY_NEAREST)
			glGenerateMipmap(GL_TEXTURE_2D);

		if (this->id == 0)
			Debug::Logging::LogException("[Texture]: Failed to create texture", Debug::LogOrigin::Engine);
		else
			Debug::Logging::Log("[Texture]: Created with id " + std::to_string(this->id), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

	Texture::Texture(const MultisampleTextureConfiguration& configuration)
	{
		Texture::TotalInstances++;

		if (configuration.size.x <= 0 || configuration.size.y <= 0)
			Debug::Logging::LogException(
				"[Texture]: Cant create. Texture have invalid size: " +
				std::to_string(configuration.size.x) +
				" x " +
				std::to_string(configuration.size.y),
				Debug::LogOrigin::Engine
			);

		this->id = 0;
		this->size = configuration.size;
		this->internalType = GL_TEXTURE_2D_MULTISAMPLE;
		this->samples = configuration.samples;

		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->id);

		glTexImage2DMultisample(
			GL_TEXTURE_2D_MULTISAMPLE,
			configuration.samples,
			(GLint)configuration.internalFormat,
			configuration.size.x,
			configuration.size.y,
			(GLint)configuration.fixedSamples
		);

		if (this->id == 0)
			Debug::Logging::LogException("[Texture]: Failed to create texture", Debug::LogOrigin::Engine);
		else
			Debug::Logging::Log("[Texture]: Created with id " + std::to_string(this->id), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

	Texture::~Texture()
	{
		Texture::TotalInstances--;

		if (this->id != 0)
		{
			glDeleteTextures(1, &this->id);
			Debug::Logging::Log("[Texture]: Deleted with id " + std::to_string(this->id), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
		}
	}

	unsigned int Texture::GetId() const
	{
		return this->id;
	}

	void Texture::Use(unsigned int slot) const
	{
		if(this->id == 0)
			Debug::Logging::LogException("[Texture]: Cant use a texture if its empty", Debug::LogOrigin::Engine);

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(this->internalType, this->id);
	}

	int Texture::GetInternalType() const
	{
		return this->internalType;
	}

	bool Texture::IsMultiSampled() const
	{
		return this->internalType == GL_TEXTURE_2D_MULTISAMPLE;
	}

	int Texture::GetNumberOfSamples() const
	{
		return this->samples;
	}

	glm::vec<2, unsigned int> Texture::GetSize() const
	{
		return this->size;
	}

	void Texture::DisableTextureUnit(const unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_2D_MULTISAMPLE);
	}

	unsigned int Texture::GetMaxTextureUnits()
	{
		int max = 0;

		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max);

		return (unsigned int)max;
	}
	
	int Texture::GetInstanceCount()
	{
		return Texture::TotalInstances;
	}
}}}