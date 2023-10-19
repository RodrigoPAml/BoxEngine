#pragma once
#include <BoxEngine.hpp>

/// <summary>
/// Generate meshes for draw primitives.
/// </summary>
namespace BoxEngine {
namespace Modules {
namespace Utils {
namespace Generator {

	GPU::VertexPtr Generate2DPoint(const GPU::DataUse use = GPU::DataUse::STATIC_DRAW);

	GPU::VertexPtr Generate2DLine(const GPU::DataUse use = GPU::DataUse::STATIC_DRAW);

	GPU::VertexPtr Generate2DRect(
		const GPU::DataUse use = GPU::DataUse::STATIC_DRAW, 
		const bool filled = true
	);

	GPU::VertexPtr Generate2DCircle(
		const unsigned int nsegments = 20, 
		const GPU::DataUse use = GPU::DataUse::STATIC_DRAW, 
		const bool filled = true
	);

	GPU::VertexPtr Generate2DTriangle(const GPU::DataUse use = GPU::DataUse::STATIC_DRAW, const bool filled = true);

	GPU::VertexPtr Generate3DPoint(const GPU::DataUse use = GPU::DataUse::STATIC_DRAW);

	GPU::VertexPtr Generate3DLine(const GPU::DataUse use = GPU::DataUse::STATIC_DRAW);

	GPU::VertexPtr Generate3DRect(
		const GPU::DataUse use = GPU::DataUse::STATIC_DRAW, 
		const bool filled = true
	);

	GPU::VertexPtr Generate3DCircle(
		const unsigned int nsegments = 20, 
		const GPU::DataUse use = GPU::DataUse::STATIC_DRAW, 
		const bool filled = true
	);

	GPU::VertexPtr Generate3DTriangle(const GPU::DataUse use = GPU::DataUse::STATIC_DRAW, const bool filled = true);

	GPU::VertexPtr Generate3DSphere(
		const GPU::DataUse use = GPU::DataUse::STATIC_DRAW, 
		const unsigned int nsegments = 20, 
		const bool filled = true
	);

	GPU::VertexPtr Generate3DCube(
		const GPU::DataUse use = GPU::DataUse::STATIC_DRAW,
		const bool filled = true
	);
}}}}