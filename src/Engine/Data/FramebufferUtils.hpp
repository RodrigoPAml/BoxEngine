#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace GPU {

	/// <summary>
	/// Get clear mode from string
	/// </summary>
	static ClearMode GetClearModeFromString(std::string key)
	{
		if (key == "COLOR")
			return ClearMode::COLOR;
		else if (key == "DEPTH")
			return ClearMode::DEPTH;
		else if (key == "STENCIL")
			return ClearMode::STENCIL;

		return ClearMode::COLOR;
	}

	/// <summary>
	/// Get Render Buffer Attachment Type from string
	/// </summary>
	static RenderBufferAttachmentType GetRenderBufferAttachmentTypeFromString(std::string key)
	{
		if (key == "DEPTH_ATTACHMENT")
			return RenderBufferAttachmentType::DEPTH_ATTACHMENT;
		else if (key == "DEPTH_STENCIL_ATTACHMENT")
			return RenderBufferAttachmentType::DEPTH_STENCIL_ATTACHMENT;
		else if (key == "DONT_USE")
			return RenderBufferAttachmentType::DONT_USE;
		else if (key == "STENCIL_ATTACHEMT")
			return RenderBufferAttachmentType::STENCIL_ATTACHEMT;

		return RenderBufferAttachmentType::DONT_USE;
	}

	/// <summary>
	/// Get Render Buffer Format from string
	/// </summary>
	static RenderBufferFormat GetRenderBufferFormatFromString(std::string key)
	{
		if (key == "DEPTH24_STENCIL8")
			return RenderBufferFormat::DEPTH24_STENCIL8;
		else if (key == "DEPTH32F_STENCIL8")
			return RenderBufferFormat::DEPTH32F_STENCIL8;
		else if (key == "DEPTH_COMPONENT16")
			return RenderBufferFormat::DEPTH_COMPONENT16;
		else if (key == "DEPTH_COMPONENT24")
			return RenderBufferFormat::DEPTH_COMPONENT24;
		else if (key == "DEPTH_COMPONENT32F")
			return RenderBufferFormat::DEPTH_COMPONENT32F;
		else if (key == "STENCIL_INDEX8")
			return RenderBufferFormat::STENCIL_INDEX8;

		return RenderBufferFormat::DEPTH32F_STENCIL8;
	}
}}