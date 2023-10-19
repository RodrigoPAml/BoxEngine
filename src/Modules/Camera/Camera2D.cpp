#include <BoxEngine.hpp>
#include "Camera2D.hpp"

namespace BoxEngine {
namespace Modules {
namespace Camera {

	std::weak_ptr<Camera2D> Camera2D::current;

	Camera2D::Camera2D(
		const float left, 
		const float right, 
		const float top, 
		const float bottom 
	)
	{
		this->l = left;
		this->r = right;
		this->t = top;
		this->b = bottom;
	}

	glm::mat4 Camera2D::GetOrthoMatrix() const
	{
		return glm::ortho<float>(this->l, this->r, this->b, this->t);
	}

	void Camera2D::SetLeft(const float l)
	{
		this->l = l;
	}

	void Camera2D::SetRight(const float r)
	{
		this->r = r;
	}

	void Camera2D::SetTop(const float t)
	{
		this->t = t;
	}

	void Camera2D::SetBottom(const float b)
	{
		this->b = b;
	}

	float Camera2D::GetLeft() const
	{
		return this->l;
	}

	float Camera2D::GetRight() const
	{
		return this->r;
	}

	float Camera2D::GetTop() const
	{
		return this->t;
	}

	float Camera2D::GetBottom() const
	{
		return this->b;
	}

	Camera2DPtr Camera2D::GetCurrentCamera()
	{
		if (Camera2D::current.expired())
			return nullptr;
		else
			return Camera2D::current.lock();
	}

	void Camera2D::SetCurrentCamera(Camera2DPtr camera)
	{
		Camera2D::current = camera;
	}
}}}