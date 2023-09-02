#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace GPU {

	/// <summary>
	/// Render Buffer attachment to FrameBuffer
	/// </summary>
	struct RenderBufferAttachment
	{
		RenderBufferAttachmentType type = RenderBufferAttachmentType::DONT_USE;

		RenderBufferFormat format = RenderBufferFormat::DEPTH32F_STENCIL8;

		glm::vec2 size = { 0,0 };

		int aliasing = 0;

		RenderBufferAttachment() = default;

		RenderBufferAttachment(const RenderBufferAttachmentType type, const RenderBufferFormat format, const glm::vec2& size, const int aliasing)
		{
			this->type = type;
			this->format = format;
			this->size = size;
			this->aliasing = aliasing;
		}
	};

	/// <summary>
	/// Depth attachment to FrameBuffer
	/// </summary>
	struct DepthAttachment
	{
		TexturePtr texture = nullptr;

		DepthAttachment() = default;

		DepthAttachment(const TexturePtr texture)
		{
			this->texture = texture;
		}
	};

	/// <summary>
	/// Configure framebuffer.
	/// </summary>
	struct FramebufferConfiguration
	{
		std::vector<TexturePtr> textureAttachments;

		RenderBufferAttachment renderBufferAttachment;

		DepthAttachment depthAttachment;

		FramebufferConfiguration() = default;

		FramebufferConfiguration(
			const std::vector<TexturePtr>& textureAttachments,
			const RenderBufferAttachment& renderBufferAttachment,
			const DepthAttachment& depthAttachment
		)
		{
			this->textureAttachments = textureAttachments;
			this->renderBufferAttachment = renderBufferAttachment;
			this->depthAttachment = depthAttachment;
		}
	};
}}