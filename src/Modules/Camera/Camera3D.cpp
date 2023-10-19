#include <BoxEngine.hpp>
#include "Camera3D.hpp"

namespace BoxEngine {	
namespace Modules {
namespace Camera {

	std::weak_ptr<Camera3D> Camera3D::current;

	Camera3D::Camera3D(const CameraConfiguration& config)
	{
		this->position = config.position;
		this->pitch = config.pitch;
		this->yaw = config.yaw;

		this->fov = config.fov;
		this->aspectRatio = config.aspectRatio;
		this->zNear = config.zNear;
		this->zFar = config.zFar;

		this->UpdateProjectionMatrix();
		this->UpdateViewMatrix();
	}

	Camera3D::~Camera3D() = default;

	void Camera3D::TranslateRelative(const CameraMovement direction, const  float velocity)
	{
		if(direction == CameraMovement::FORWARD)
			this->position += this->frontVec * velocity;
		else if(direction == CameraMovement::BACKWARD)
			this->position -= this->frontVec * velocity;
		else if(direction == CameraMovement::LEFT)
			this->position -= this->rightVec * velocity;
		else if(direction == CameraMovement::RIGHT)
			this->position += this->rightVec * velocity;
		else if(direction == CameraMovement::UP)
			this->position += this->upVec * velocity;
		else if(direction == CameraMovement::DOWN)
			this->position -= this->upVec * velocity;
	}

	void Camera3D::TranslateAbsolute(const CameraMovement direction, const  float velocity)
	{
		if(direction == CameraMovement::FORWARD)
			this->position += glm::vec3(0.0f, 0.0f, 1.0f) * velocity;
		else if(direction == CameraMovement::BACKWARD)
			this->position -= glm::vec3(0.0f, 0.0f, -1.0f) * velocity;
		else if(direction == CameraMovement::LEFT)
			this->position -= glm::vec3(-1.0f, 0.0f, 0.0f) * velocity;
		else if(direction == CameraMovement::RIGHT)
			this->position += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
		else if(direction == CameraMovement::UP)
			this->position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
		else if(direction == CameraMovement::DOWN)
			this->position -= glm::vec3(0.0f, -1.0f, 0.0f) * velocity;
	}

	void Camera3D::Rotate(const float yaw, const float pitch)
	{
		this->yaw += yaw;
		this->pitch += pitch;

		if(this->pitch > 89.0f)
			this->pitch = 89.0f;
		else if(this->pitch < -89.0f)
			this->pitch = -89.0f;
	}

	void Camera3D::SetRotation(const float yaw, const float pitch)
	{
		this->yaw = yaw;
		this->pitch = pitch;

		if(this->pitch > 89.0f)
			this->pitch = 89.0f;
		else if(this->pitch < -89.0f)
			this->pitch = -89.0f;
	}

	void Camera3D::SetRotation(const glm::vec3& front)
	{
		glm::vec2 angles = Camera3D::TransformFrontVectorToPitchYaw(front);

		this->SetRotation(angles.x, angles.y);
	}

	void Camera3D::UpdateViewMatrix()
	{
		const glm::vec3 front(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
			sin(glm::radians(pitch)), 
			sin(glm::radians(yaw)) * cos(glm::radians(pitch))
		);

		this->frontVec = glm::normalize(front);
		this->rightVec = glm::normalize(glm::cross(this->frontVec, glm::vec3(0.0f, 1.0f, 0.0f)));
		this->upVec = glm::normalize(glm::cross(this->rightVec, this->frontVec));

		this->viewMatrix = glm::lookAt(this->position, this->position + this->frontVec, this->upVec);
	}

	void Camera3D::UpdateProjectionMatrix()
	{
		this->projectionMatrix = glm::perspective(
			glm::radians(this->fov), 
			this->aspectRatio, 
			this->zNear, 
			this->zFar
		);
	}

	glm::mat4 Camera3D::GetViewMatrix() const
	{
		return this->viewMatrix;
	}

	glm::mat4 Camera3D::GetProjectionMatrix() const
	{
		return this->projectionMatrix;
	}

	void Camera3D::SetPosition(const glm::vec3& position)
	{
		this->position = position;
	}

	glm::vec3 Camera3D::GetPosition() const
	{
		return this->position;
	}

	void Camera3D::SetYaw(const float yaw)
	{
		this->yaw = yaw;
	}

	float Camera3D::GetYaw() const
	{
		return this->yaw;
	}

	void Camera3D::SetPitch(const float pitch)
	{
		this->pitch = pitch;
	}

	float Camera3D::GetPitch() const
	{
		return this->pitch;
	}

	void Camera3D::SetZNear(const float zNear)
	{
		this->zNear = zNear;
	}

	float Camera3D::GetZNear() const
	{
		return this->zNear;
	}

	void Camera3D::SetZFar(const float zFar)
	{
		this->zFar = zFar;
	}

	float Camera3D::GetZFar() const
	{
		return this->zFar;
	}

	void Camera3D::SetFOV(const float fov)
	{
		this->fov = fov;
	}

	float Camera3D::GetFOV() const
	{
		return this->fov;
	}

	void Camera3D::SetAspectRatio(const float aspect)
	{
		this->aspectRatio = aspect;
	}

	float Camera3D::GetAspectRatio() const
	{
		return this->aspectRatio;
	}

	glm::vec3 Camera3D::GetFront() const
	{
		return this->frontVec;
	}

	glm::vec3 Camera3D::GetRight() const
	{
		return this->rightVec;
	}

	glm::vec3 Camera3D::GetUp() const
	{
		return this->upVec;
	}

	void Camera3D::SetCurrentCamera(const Camera3DPtr camera)
	{
		Camera3D::current = camera;
	}

	Camera3DPtr Camera3D::GetCurrentCamera()
	{
		if(Camera3D::current.expired())
			return nullptr;
		else
			return Camera3D::current.lock();
	}

	glm::vec2 Camera3D::TransformFrontVectorToPitchYaw(const glm::vec3& front)
	{
		const glm::vec3 normFront(glm::normalize(front));

		float pitch = asin(-normFront.y);
		float yaw = atan2(normFront.x, normFront.z);

		return { yaw, pitch };
	}
}}}
