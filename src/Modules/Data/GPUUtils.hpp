#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace GPU {

	/// <summary>
	/// Get the drawing type from string
	/// </summary>
	static DrawingType DrawingTypeFromString(std::string key)
	{
		if (key == "LINES")
			return DrawingType::LINES;
		else if (key == "LINE_ADJACENCY")
			return DrawingType::LINE_ADJACENCY;
		else if (key == "LINE_LOOP")
			return DrawingType::LINE_LOOP;
		else if (key == "LINE_STRIP")
			return DrawingType::LINE_STRIP;
		else if (key == "LINE_STRIP_ADJACENCY")
			return DrawingType::LINE_STRIP_ADJACENCY;
		else if (key == "POINTS")
			return DrawingType::POINTS;
		else if (key == "TRIANGLES")
			return DrawingType::TRIANGLES;
		else if (key == "TRIANGLES_ADJACENCY")
			return DrawingType::TRIANGLES_ADJACENCY;
		else if (key == "TRIANGLE_FAN")
			return DrawingType::TRIANGLE_FAN;
		else if (key == "TRIANGLE_STRIP")
			return DrawingType::TRIANGLE_STRIP;
		else if (key == "TRIANGLE_STRIP_ADJACENCY")
			return DrawingType::TRIANGLE_STRIP_ADJACENCY;

		Debug::Logging::Log(
			"Failed to map DrawingType with value " + key + " instead the default value TRIANGLES will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return DrawingType::TRIANGLES;
	}

	/// <summary>
	/// Get data use mode from string
	/// </summary>
	static DataUse DataUseFromString(std::string key)
	{
		if (key == "DYNAMIC_COPY")
			return DataUse::DYNAMIC_COPY;
		else if (key == "DYNAMIC_DRAW")
			return DataUse::DYNAMIC_DRAW;
		else if (key == "DYNAMIC_READ")
			return DataUse::DYNAMIC_READ;
		else if (key == "STATIC_COPY")
			return DataUse::STATIC_COPY;
		else if (key == "STATIC_DRAW")
			return DataUse::STATIC_DRAW;
		else if (key == "STATIC_READ")
			return DataUse::STATIC_READ;
		else if (key == "STREAM_COPY")
			return DataUse::STREAM_COPY;
		else if (key == "STREAM_DRAW")
			return DataUse::STREAM_DRAW;
		else if (key == "STREAM_READ")
			return DataUse::STREAM_READ;

		Debug::Logging::Log(
			"Failed to map DataUse with value " + key + " instead the default value STATIC_DRAW will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return DataUse::STATIC_DRAW;
	}

	/// <summary>
	/// Get depth testing mode from string
	/// </summary>
	static DepthTestingMode DepthTestingFromString(std::string key)
	{
		if (key == "ALWAYS")
			return DepthTestingMode::ALWAYS;
		else if (key == "GREATER_EQUAL")
			return DepthTestingMode::GEQUAL;
		else if (key == "GREATER")
			return DepthTestingMode::GREATER;
		else if (key == "LESS_EQUAL")
			return DepthTestingMode::LEQUAL;
		else if (key == "LESS")
			return DepthTestingMode::LESS;
		else if (key == "NEVER")
			return DepthTestingMode::NEVER;
		else if (key == "NOT_EQUAL")
			return DepthTestingMode::NOTEQUAL;

		Debug::Logging::Log(
			"Failed to map DepthTestingMode with value " + key + " instead the default value NEVER will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return DepthTestingMode::NEVER;
	}

	/// <summary>
	/// Get culling face mode from string
	/// </summary>
	static CullingFaceMode CullingFaceFromString(std::string key)
	{
		if (key == "FRONT")
			return CullingFaceMode::FRONT;
		else if (key == "BACK")
			return CullingFaceMode::BACK;
		else if (key == "BOTH")
			return CullingFaceMode::BOTH;

		Debug::Logging::Log(
			"Failed to map CullingFaceMode with value " + key + " instead the default value BACK will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return CullingFaceMode::BACK;
	}

	/// <summary>
	/// Get polygon mode from string
	/// </summary>
	static PolygonMode PolygonModeFromString(std::string key)
	{
		if (key == "FILL")
			return PolygonMode::FILL;
		else if (key == "LINE")
			return PolygonMode::LINE;
		else if (key == "POINT")
			return PolygonMode::POINT;

		Debug::Logging::Log(
			"Failed to map PolygonMode with value " + key + " instead the default value FILL will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return PolygonMode::FILL;
	}

	/// <summary>
	/// Get magnification filter from string
	/// </summary>
	static MagnificationFilter MagnificationFilterFromString(std::string key)
	{
		if (key == "LINEAR")
			return MagnificationFilter::LINEAR;
		else if (key == "NEAREST")
			return MagnificationFilter::NEAREST;

		Debug::Logging::Log(
			"Failed to map MagnificationFilter with value " + key + " instead the default value LINEAR will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return MagnificationFilter::LINEAR;
	}

	/// <summary>
	/// Get minifying filter from string
	/// </summary>
	static MinifyingFilter MinifyingFilterFromString(std::string key)
	{
		if (key == "LINEAR_MIPMAP_LINEAR")
			return MinifyingFilter::LINEAR_MIPMAP_LINEAR;
		else if (key == "LINEAR_MIPMAP_NEAREST")
			return MinifyingFilter::LINEAR_MIPMAP_NEAREST;
		else if (key == "NEAREST_MIPMAP_LINEAR")
			return MinifyingFilter::NEAREST_MIPMAP_LINEAR;
		else if (key == "NEAREST_MIPMAP_NEAREST")
			return MinifyingFilter::NEAREST_MIPMAP_NEAREST;
		else if (key == "ONLY_LINEAR")
			return MinifyingFilter::ONLY_LINEAR;
		else if (key == "ONLY_NEAREST")
			return MinifyingFilter::ONLY_NEAREST;

		Debug::Logging::Log(
			"Failed to map MinifyingFilter with value " + key + " instead the default value ONLY_NEAREST will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return MinifyingFilter::ONLY_NEAREST;
	}

	/// <summary>
	/// Get texture pixel format from string
	/// </summary>
	static TexturePixelFormat TexturePixelFormatFromString(std::string key)
	{
		if (key == "BYTE")
			return TexturePixelFormat::BYTE;
		else if (key == "FLOAT")
			return TexturePixelFormat::FLOAT;
		else if (key == "HALF_FLOAT")
			return TexturePixelFormat::HALF_FLOAT;
		else if (key == "INT")
			return TexturePixelFormat::INT;
		else if (key == "SHORT")
			return TexturePixelFormat::SHORT;
		else if (key == "UNSIGNED_BYTE")
			return TexturePixelFormat::UNSIGNED_BYTE;
		else if (key == "UNSIGNED_BYTE_2_3_3_REV")
			return TexturePixelFormat::UNSIGNED_BYTE_2_3_3_REV;
		else if (key == "UNSIGNED_BYTE_3_3_2")
			return TexturePixelFormat::UNSIGNED_BYTE_3_3_2;
		else if (key == "UNSIGNED_INT")
			return TexturePixelFormat::UNSIGNED_INT;
		else if (key == "UNSIGNED_INT_10_10_10_2")
			return TexturePixelFormat::UNSIGNED_INT_10_10_10_2;
		else if (key == "UNSIGNED_INT_2_10_10_10_REV")
			return TexturePixelFormat::UNSIGNED_INT_2_10_10_10_REV;
		else if (key == "UNSIGNED_INT_8_8_8_8")
			return TexturePixelFormat::UNSIGNED_INT_8_8_8_8;
		else if (key == "UNSIGNED_INT_8_8_8_8_REV")
			return TexturePixelFormat::UNSIGNED_INT_8_8_8_8_REV;
		else if (key == "UNSIGNED_SHORT")
			return TexturePixelFormat::UNSIGNED_SHORT;
		else if (key == "UNSIGNED_SHORT_1_5_5_5_REV")
			return TexturePixelFormat::UNSIGNED_SHORT_1_5_5_5_REV;
		else if (key == "UNSIGNED_SHORT_4_4_4_4")
			return TexturePixelFormat::UNSIGNED_SHORT_4_4_4_4;
		else if (key == "UNSIGNED_SHORT_4_4_4_4_REV")
			return TexturePixelFormat::UNSIGNED_SHORT_4_4_4_4_REV;
		else if (key == "UNSIGNED_SHORT_5_5_5_1")
			return TexturePixelFormat::UNSIGNED_SHORT_5_5_5_1;
		else if (key == "UNSIGNED_SHORT_5_6_5")
			return TexturePixelFormat::UNSIGNED_SHORT_5_6_5;
		else if (key == "UNSIGNED_SHORT_5_6_5_REV")
			return TexturePixelFormat::UNSIGNED_SHORT_5_6_5_REV;
		
		Debug::Logging::Log(
			"Failed to map TexturePixelFormat with value " + key + " instead the default value BYTE will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return TexturePixelFormat::BYTE;
	}

	/// <summary>
	/// Get texture internal pixel format from string
	/// </summary>
	static TextureInternalFormat TextureInternalFormatToString(std::string key)
	{
		if(key == "DEPTH_COMPONENT")
			return TextureInternalFormat::DEPTH_COMPONENT;
		else if (key == "DEPTH_STENCIL")
			return TextureInternalFormat::DEPTH_STENCIL;
		else if (key == "R")
			return TextureInternalFormat::R;
		else if (key == "RG")
			return TextureInternalFormat::RG;
		else if (key == "RGB")
			return TextureInternalFormat::RGB;
		else if (key == "RGBA")
			return TextureInternalFormat::RGBA;
		else if (key == "R8")
			return TextureInternalFormat::R8;
		else if (key == "R8_SNORM")
			return TextureInternalFormat::R8_SNORM;
		else if (key == "R16")
			return TextureInternalFormat::R16;
		else if (key == "R16_SNORM")
			return TextureInternalFormat::R16_SNORM;
		else if (key == "RG8")
			return TextureInternalFormat::RG8;
		else if (key == "RG8_SNORM")
			return TextureInternalFormat::RG8_SNORM;
		else if (key == "RG16")
			return TextureInternalFormat::RG16;
		else if (key == "RG16_SNORM")
			return TextureInternalFormat::RG16_SNORM;
		else if (key == "R3_G3_B2")
			return TextureInternalFormat::R3_G3_B2;
		else if (key == "RGB4")
			return TextureInternalFormat::RGB4;
		else if (key == "RGB5")
			return TextureInternalFormat::RGB5;
		else if (key == "RGB8_SNORM")
			return TextureInternalFormat::RGB8_SNORM;
		else if (key == "RGB10")
			return TextureInternalFormat::RGB10;
		else if (key == "RGB12")
			return TextureInternalFormat::RGB12;
		else if (key == "RGB16_SNORM")
			return TextureInternalFormat::RGB16_SNORM;
		else if (key == "RGBA2")
			return TextureInternalFormat::RGBA2;
		else if (key == "RGBA4")
			return TextureInternalFormat::RGBA4;
		else if (key == "RGB5_A1")
			return TextureInternalFormat::RGB5_A1;
		else if (key == "RGBA8")
			return TextureInternalFormat::RGBA8;
		else if (key == "RGBA8_SNORM")
			return TextureInternalFormat::RGBA8_SNORM;
		else if (key == "RGB10_A2")
			return TextureInternalFormat::RGB10_A2;
		else if (key == "RGB10_A2UI")
			return TextureInternalFormat::RGB10_A2UI;
		else if (key == "RGBA12")
			return TextureInternalFormat::RGBA12;
		else if (key == "RGBA16")
			return TextureInternalFormat::RGBA16;
		else if (key == "SRGB8")
			return TextureInternalFormat::SRGB8;
		else if (key == "SRGB8_ALPHA8")
			return TextureInternalFormat::SRGB8_ALPHA8;
		else if (key == "R16F")
			return TextureInternalFormat::R16F;
		else if (key == "RG16F")
			return TextureInternalFormat::RG16F;
		else if (key == "RGB16F")
			return TextureInternalFormat::RGB16F;
		else if (key == "RGBA16F")
			return TextureInternalFormat::RGBA16F;
		else if (key == "R32F")
			return TextureInternalFormat::R32F;
		else if (key == "RG32F")
			return TextureInternalFormat::RG32F;
		else if (key == "RGB32F")
			return TextureInternalFormat::RGB32F;
		else if (key == "RGBA32F")
			return TextureInternalFormat::RGBA32F;
		else if (key == "R11F_G11F_B10F")
			return TextureInternalFormat::R11F_G11F_B10F;
		else if (key == "RGB9_E5")
			return TextureInternalFormat::RGB9_E5;
		else if (key == "R8I")
			return TextureInternalFormat::R8I;
		else if (key == "R8UI")
			return TextureInternalFormat::R8UI;
		else if (key == "R16I")
			return TextureInternalFormat::R16I;
		else if (key == "R16UI")
			return TextureInternalFormat::R16UI;
		else if (key == "R32I")
			return TextureInternalFormat::R32I;
		else if (key == "R32UI")
			return TextureInternalFormat::R32UI;
		else if (key == "RG8I")
			return TextureInternalFormat::RG8I;
		else if (key == "RG8UI")
			return TextureInternalFormat::RG8UI;
		else if (key == "RG16I")
			return TextureInternalFormat::RG16I;
		else if (key == "RG16UI")
			return TextureInternalFormat::RG16UI;
		else if (key == "RG32I")
			return TextureInternalFormat::RG32I;
		else if (key == "RG32UI")
			return TextureInternalFormat::RG32UI;
		else if (key == "RGB8I")
			return TextureInternalFormat::RGB8I;
		else if (key == "RGB8UI")
			return TextureInternalFormat::RGB8UI;
		else if (key == "RGB16I")
			return TextureInternalFormat::RGB16I;
		else if (key == "RGB16UI")
			return TextureInternalFormat::RGB16UI;
		else if (key == "RGB32I")
			return TextureInternalFormat::RGB32I;
		else if (key == "RGB32UI")
			return TextureInternalFormat::RGB32UI;
		else if (key == "RGBA8I")
			return TextureInternalFormat::RGBA8I;
		else if (key == "RGBA8UI")
			return TextureInternalFormat::RGBA8UI;
		else if (key == "RGBA16I")
			return TextureInternalFormat::RGBA16I;
		else if (key == "RGBA16UI")
			return TextureInternalFormat::RGBA16UI;
		else if (key == "RGBA32I")
			return TextureInternalFormat::RGBA32I;
		else if (key == "RGBA32UI")
			return TextureInternalFormat::RGBA32UI;
		else if (key == "COMPRESSED_RED")
			return TextureInternalFormat::COMPRESSED_RED;
		else if (key == "COMPRESSED_RG")
			return TextureInternalFormat::COMPRESSED_RG;
		else if (key == "COMPRESSED_RGB")
			return TextureInternalFormat::COMPRESSED_RGB;
		else if (key == "COMPRESSED_RGBA")
			return TextureInternalFormat::COMPRESSED_RGBA;
		else if (key == "COMPRESSED_SRGB")
			return TextureInternalFormat::COMPRESSED_SRGB;
		else if (key == "COMPRESSED_SRGB_ALPHA")
			return TextureInternalFormat::COMPRESSED_SRGB_ALPHA;
		else if (key == "COMPRESSED_RED_RGTC1")
			return TextureInternalFormat::COMPRESSED_RED_RGTC1;
		else if (key == "COMPRESSED_SIGNED_RED_RGTC1")
			return TextureInternalFormat::COMPRESSED_SIGNED_RED_RGTC1;
		else if (key == "COMPRESSED_RG_RGTC2")
			return TextureInternalFormat::COMPRESSED_RG_RGTC2;
		else if (key == "COMPRESSED_SIGNED_RG_RGTC2")
			return TextureInternalFormat::COMPRESSED_SIGNED_RG_RGTC2;

		Debug::Logging::Log(
			"Failed to map TextureInternalFormat with value " + key + " instead the default value RGB will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return TextureInternalFormat::RGB;
	}

	/// <summary>
	/// Get texture wrap from string
	/// </summary>
	static TextureWrap TextureWrapFromString(std::string key)
	{
		if (key == "REPEATED")
			return TextureWrap::REPEATED;
		else if (key == "CLAMP_TO_BORDER")
			return TextureWrap::CLAMP_TO_BORDER;
		else if (key == "CLAMP_TO_EDGE")
			return TextureWrap::CLAMP_TO_EDGE;
		else if (key == "MIRRORED_REPEAT")
			return TextureWrap::MIRRORED_REPEAT;
		else if (key == "MIRROR_CLAMP_TO_EDGE")
			return TextureWrap::MIRROR_CLAMP_TO_EDGE;

		Debug::Logging::Log(
			"Failed to map TextureWrap with value " + key + " instead the default value REPEATED will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return TextureWrap::REPEATED;
	}

	/// <summary>
	/// Get texture format from string
	/// </summary>
	static TextureFormat TextureFormatFromString(std::string key)
	{
		if (key == "BGR")
			return TextureFormat::BGR;
		else if (key == "BGRA")
			return TextureFormat::BGRA;
		else if (key == "BGRA_INTEGER")
			return TextureFormat::BGRA_INTEGER;
		else if (key == "BGR_INTEGER")
			return TextureFormat::BGR_INTEGER;
		else if (key == "DEPTH_COMPONENT")
			return TextureFormat::DEPTH_COMPONENT;
		else if (key == "DEPTH_STENCIL")
			return TextureFormat::DEPTH_STENCIL;
		else if (key == "R")
			return TextureFormat::R;
		else if (key == "RED_INTEGER")
			return TextureFormat::RED_INTEGER;
		else if (key == "RG")
			return TextureFormat::RG;
		else if (key == "RGB")
			return TextureFormat::RGB;
		else if (key == "RGBA")
			return TextureFormat::RGBA;
		else if (key == "RGBA_INTEGER")
			return TextureFormat::RGBA_INTEGER;
		else if (key == "RGB_INTEGER")
			return TextureFormat::RGB_INTEGER;
		else if (key == "RG_INTEGER")
			return TextureFormat::RG_INTEGER;
		else if (key == "STENCIL_INDEX")
			return TextureFormat::STENCIL_INDEX;

		Debug::Logging::Log(
			"Failed to map TextureFormat with value " + key + " instead the default value RGB will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return TextureFormat::RGB;
	}

	/// <summary>
	/// Get the vertex buffer type from string
	/// </summary>
	static VertexBufferType VertexBufferTypeFromString(std::string key)
	{
		if (key == "BYTE")
			return VertexBufferType::BYTE;
		else if (key == "DOUBLE")
			return VertexBufferType::DOUBLE;
		else if (key == "FLOAT")
			return VertexBufferType::FLOAT;
		else if (key == "HALF_FLOAT")
			return VertexBufferType::HALF_FLOAT;
		else if (key == "INT")
			return VertexBufferType::INT;
		else if (key == "INT_2_10_10_10_REV")
			return VertexBufferType::INT_2_10_10_10_REV;
		else if (key == "SHORT")
			return VertexBufferType::SHORT;
		else if (key == "UBYTE")
			return VertexBufferType::UBYTE;
		else if (key == "UINT")
			return VertexBufferType::UINT;
		else if (key == "UINT_2_10_10_10_REV")
			return VertexBufferType::UINT_2_10_10_10_REV;
		else if (key == "USHORT")
			return VertexBufferType::USHORT;
		
		Debug::Logging::Log(
			"Failed to map VertexBufferType with value " + key + " instead the default value FLOAT will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return VertexBufferType::FLOAT;
	}

	/// <summary>
	/// Get the size of each vertex data type in bytes.
	/// </summary>
	static unsigned int GetSizeOfVertexBufferType(const VertexBufferType type)
	{
		switch (type)
		{
			case VertexBufferType::BYTE:
				return 1;
			case VertexBufferType::UBYTE:
				return 1;
			case VertexBufferType::SHORT:
				return 2;
			case VertexBufferType::USHORT:
				return 2;
			case VertexBufferType::INT:
				return 4;
			case VertexBufferType::UINT:
				return 4;
			case VertexBufferType::HALF_FLOAT:
				return 2;
			case VertexBufferType::FLOAT:
				return 4;
			case VertexBufferType::DOUBLE:
				return 8;
			case VertexBufferType::INT_2_10_10_10_REV:
				return 4;
			case VertexBufferType::UINT_2_10_10_10_REV:
				return 4;
			default:
				return 0;
		}
	}
}}}