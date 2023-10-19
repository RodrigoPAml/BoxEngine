#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace Camera {

	class Camera3D;
	typedef std::shared_ptr<Camera3D> Camera3DPtr;

	/// <summary>
	/// Represents a 3D FPS camera, using perspective projection.
	/// </summary>
	class Camera3D
	{
	private:
		/// <summary>
		/// Position and vectors of camera.
		/// </summary>
		glm::vec3 position, frontVec, rightVec, upVec;

		/// <summary>
		/// The matrix to project to 3D world and to apply camera transformations.
		/// </summary>
		glm::mat4 projectionMatrix, viewMatrix;

		/// <summary>
		/// Current yaw and pitch of camera.
		/// </summary>
		float yaw, pitch;
			
		/// <summary>
		/// FOV, AR of Camera.
		/// </summary>
		float fov, aspectRatio;
			
		/// <summary>
		/// ZFar and ZNear currently used for projection.
		/// </summary>
		float zFar, zNear;

		/// <summary>
		/// Current camera used
		/// </summary>
		static std::weak_ptr<Camera3D> current;
	public:
		Camera3D(const CameraConfiguration& config = CameraConfiguration());
		~Camera3D();

		/// <summary>
		/// Translate the camera relative to currently vectors of the camera.
		/// </summary>
		void TranslateRelative(const CameraMovement direction, const float velocity);

		/// <summary>
		/// Translate the camera in relation to the x,y,z axis.
		/// </summary>
		void TranslateAbsolute(const CameraMovement direction, const float velocity);

		/// <summary>
		/// Rotate the camera given the yaw and pitch amount.
		/// </summary>
		void Rotate(const float yaw, const float pitch);

		/// <summary>
		/// Set the camera to the exaclty pitch and yaw.
		/// </summary>
		void SetRotation(const float yaw, const float pitch);

		/// <summary>
		/// Set the camera rotation based on a given front vector.
		/// </summary>
		void SetRotation(const glm::vec3& front);

		/// <summary>
		/// Update matrices with the current class state.
		/// </summary>
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;

		void SetPosition(const glm::vec3& position);
		glm::vec3 GetPosition() const;

		void SetYaw(const float yaw);
		float GetYaw() const;

		void SetPitch(const float pitch);
		float GetPitch() const;

		void SetZNear(const float zNear);
		float GetZNear() const;

		void SetZFar(const float zFar);
		float GetZFar() const;

		void SetFOV(const float fov);
		float GetFOV() const;

		void SetAspectRatio(const float aspect);
		float GetAspectRatio() const;

		glm::vec3 GetFront() const;
		glm::vec3 GetRight() const;
		glm::vec3 GetUp() const;

		static void SetCurrentCamera(const Camera3DPtr camera);
		static Camera3DPtr GetCurrentCamera();

		/// <summary>
		/// Transform a front vector to Pitch/Yaw 
		/// </summary>
		static glm::vec2 TransformFrontVectorToPitchYaw(const glm::vec3& front);
	};
}}}
