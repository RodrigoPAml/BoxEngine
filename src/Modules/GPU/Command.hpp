#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {	
namespace Modules {
namespace GPU {
namespace Command {

	/// <summary>
	/// Changes how the polygons will be drawn.
	/// </summary>
	void SetPolygonDrawMode(const PolygonMode mode);

	/// <summary>
	/// Controls the depth testing.
	/// </summary>
	void EnableDepthTesting();
	void DisableDepthTesting();
	bool IsDepthTestingEnabled();
	void SetDepthTestingMode(DepthTestingMode mode);

	/// <summary>
	/// Controls the culling face.
	/// </summary>
	void EnableCullingFace();
	void DisableCullingFace();
	void SetCullingFaceMode(CullingFaceMode mode);

	/// <summary>
	/// Controls the primitives size.
	/// </summary>
	void SetPrimitivePointSize(const float size);
	void SetPrimitiveLineSize(const float size);

	/// <summary>
	/// Controls the Vsync.
	/// </summary>
	void EnableVSync();
	void DisableVSync();

	/// <summary>
	/// Controls the bleding.
	/// </summary>
	void EnableBlending();
	void DisableBlending();
}}}}