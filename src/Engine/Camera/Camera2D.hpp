#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {	
namespace Camera {

	class Camera2D;
	typedef std::shared_ptr<Camera2D> Camera2DPtr;

	/// <summary>
	/// Represents a 2D camera, using orthogonal projection.
	/// </summary>
	class Camera2D
	{
	private:
		/// <summary>
		/// Camera data
		/// Camera limits (left, right, top, bottom).
		/// </summary>
		float l, r, t, b;

		/// <summary>
		/// Current camera used. Can be acessed globally.
		/// </summary>
		static std::weak_ptr<Camera2D> current;
	public:
		Camera2D(
			const float left = 0, 
			const float right = 800, 
			const float top = 600, 
			const float bottom = 0
		);

		glm::mat4 GetOrthoMatrix() const;

		void SetLeft(const float l);
		void SetRight(const float r);
		void SetTop(const float t);
		void SetBottom(const float b);

		float GetLeft() const;
		float GetRight() const;
		float GetTop() const;
		float GetBottom() const;

		static Camera2DPtr GetCurrentCamera();
		static void SetCurrentCamera(Camera2DPtr camera);
	};
}}
