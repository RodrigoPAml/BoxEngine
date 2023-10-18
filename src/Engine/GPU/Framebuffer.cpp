#include <BoxEngine.hpp>
#include "Framebuffer.hpp"

namespace BoxEngine {
namespace GPU {

	unsigned int Framebuffer::ClearModeSum = (unsigned int)ClearMode::COLOR;

	int Framebuffer::TotalInstances = 0;

	int Framebuffer::CurrentUsedId = 0;

	Framebuffer::Framebuffer(const FramebufferConfiguration& configuration)
	{
		Framebuffer::TotalInstances++;

		this->id = 0;
		this->renderBufferId = 0;

		if(configuration.textureAttachments.empty())
			Debug::Logging::LogException("[Framebuffer]: Attempt to create a framebuffer without texture attachments", Debug::LogOrigin::Engine);

		glGenFramebuffers(1, &this->id);
		glBindFramebuffer(GL_FRAMEBUFFER, this->id);

		GLenum attach = GL_COLOR_ATTACHMENT0;

		unsigned int* attachments = new unsigned int[configuration.textureAttachments.size()]();

		for(auto i = 0; i < configuration.textureAttachments.size(); i++)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, attach, configuration.textureAttachments[i]->GetInternalType(), configuration.textureAttachments[i]->GetId(), 0);

			attachments[i] = attach;
			attach++;

			this->texturesAttachments.push_back(configuration.textureAttachments[i]);
		}

		if (configuration.textureAttachments.size() > 0)
			glDrawBuffers(configuration.textureAttachments.size(), attachments);

		if(configuration.depthAttachment.texture != nullptr)
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, configuration.depthAttachment.texture->GetInternalType(), configuration.depthAttachment.texture->GetId(), 0);
		
		delete[] attachments;

		if(configuration.renderBufferAttachment.type != RenderBufferAttachmentType::DONT_USE)
		{
			glGenRenderbuffers(1, &this->renderBufferId);
			glBindRenderbuffer(GL_RENDERBUFFER, this->renderBufferId);

			if (configuration.renderBufferAttachment.aliasing > 0)
			{
				glRenderbufferStorageMultisample(
					GL_RENDERBUFFER,
					configuration.renderBufferAttachment.aliasing,
					(GLenum)configuration.renderBufferAttachment.format,
					configuration.renderBufferAttachment.size.x,
					configuration.renderBufferAttachment.size.y
				);
			}
			else
			{
				glRenderbufferStorage(
					GL_RENDERBUFFER,
					(GLenum)configuration.renderBufferAttachment.format,
					configuration.renderBufferAttachment.size.x,
					configuration.renderBufferAttachment.size.y
				);
			}

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, (GLenum)configuration.renderBufferAttachment.type, GL_RENDERBUFFER, this->renderBufferId);
		}

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			if (configuration.textureAttachments.empty())
				Debug::Logging::LogException("[Framebuffer]: Failed to complete framebuffer creation", Debug::LogOrigin::Engine);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		if (this->id == 0)
			Debug::Logging::LogException("[Framebuffer]: Failed to create framebuffer", Debug::LogOrigin::Engine);
		else if (this->renderBufferId == 0 && configuration.renderBufferAttachment.type != RenderBufferAttachmentType::DONT_USE)
			Debug::Logging::LogException("[Framebuffer]: Failed to create render buffer", Debug::LogOrigin::Engine);
		else 
			Debug::Logging::Log("[Framebuffer]: Created with id " + std::to_string(this->id), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

	Framebuffer::~Framebuffer()
	{
		Framebuffer::TotalInstances--;

		if (this->id == CurrentUsedId)
			CurrentUsedId = 0;

		if (this->id != 0)
		{
			Debug::Logging::Log("[Framebuffer]: Deleted with id " + std::to_string(this->id), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
			glDeleteFramebuffers(1, &this->id);
		}

		if (this->renderBufferId != 0)
			glDeleteRenderbuffers(1, &this->renderBufferId);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Framebuffer::Use() 
	{
		if (this->id == 0)
			Debug::Logging::LogException("[Framebuffer]: Can't use an empty framebuffer", Debug::LogOrigin::Engine);

		CurrentUsedId = this->id;

		glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	}

	unsigned int Framebuffer::GetAttachmentSize() const
	{
		return this->texturesAttachments.size();
	}

	TexturePtr Framebuffer::GetTextureAttachment(const unsigned int index) const
	{
		if(index < 0 || index > this->texturesAttachments.size())
			Debug::Logging::LogException("[Framebuffer]: Can't access texture attachment out of index", Debug::LogOrigin::Engine);

		return this->texturesAttachments[index];
	}

	void Framebuffer::ActiveDefault()
	{
		CurrentUsedId = 0;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Framebuffer::SwitchViewPort(const glm::vec2& pos, const glm::vec2& size)
	{
		glViewport(pos.x, pos.y, size.x, size.y);
	}

	void Framebuffer::SetClearModes(const std::set<ClearMode>& clearModes)
	{
		if(clearModes.empty()) return;

		Framebuffer::ClearModeSum = 0;

		for(ClearMode mode : clearModes)
		{
			Framebuffer::ClearModeSum |= (unsigned int)mode;
		}
	}

	void Framebuffer::Clear(const glm::vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
		glClear((GLbitfield)Framebuffer::ClearModeSum);
	}

	int Framebuffer::GetInstanceCount()
	{
		return Framebuffer::TotalInstances;
	}

	int Framebuffer::GetCurrendUsedId()
	{
		return Framebuffer::CurrentUsedId;
	}
}}