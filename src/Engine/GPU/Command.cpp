#include <BoxEngine.hpp>
#include "Command.hpp"

namespace BoxEngine {
namespace GPU {
namespace Command {

	void SetPolygonDrawMode(const PolygonMode mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
	}

	void EnableDepthTesting()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void DisableDepthTesting()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void SetDepthTestingMode(DepthTestingMode mode)
	{
		glDepthFunc((GLenum)mode);
	}

	void EnableCullingFace()
	{
		glEnable(GL_CULL_FACE);
	}

	void DisableCullingFace()
	{
		glDisable(GL_CULL_FACE);
	}

	void SetCullingFaceMode(CullingFaceMode mode)
	{
		glCullFace((GLenum)mode);
	}

	void SetPrimitivePointSize(const float size)
	{
		glPointSize(size);
	}

	void SetPrimitiveLineSize(const float size)
	{
		glLineWidth(size);
	}

	void EnableVSync()
	{
		glfwSwapInterval(1);
	}

	void DisableVSync()
	{
		glfwSwapInterval(0);
	}

	void EnableBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void DisableBlending()
	{
		glDisable(GL_BLEND);
	}
}}}
