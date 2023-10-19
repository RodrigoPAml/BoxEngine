#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
namespace GPU {

	/// <summary>
	/// A class to use OpenGL shaders.
	/// </summary>
	class Shader
	{
	private:
		/// <summary>
		/// Shader identifier.
		/// </summary>
		unsigned int id;

		/// <summary>
		/// Cached uniforms.
		/// </summary>
		std::map<std::string, unsigned int> uniforms;

		static int TotalInstances;
	public:
		/// <summary>
		/// Construct a shader from shaders content.
		/// Vertex shader is the only necessary.
		/// </summary>
		Shader(
			const std::string& verticeShader, 
			const std::string& fragmentShader, 
			const std::string& geometryShader
		);

		/// <summary>
		/// Deconstructor
		/// </summary>
		~Shader();
			
		unsigned int GetId() const;

		/// <summary>
		/// Active this shader for use.
		/// </summary>
		void Use() const;

		/// <summary>
		/// Uniforms setters.
		/// </summary>
		void SetBool(const std::string& label, bool value);
		void SetInt(const std::string& label, int value);
		void SetFloat(const std::string& label, float value);
		void SetVec2(const std::string& label, const glm::vec2& value);
		void SetXY(const std::string& label, float x, float y);
		void SetVec3(const std::string& label, const glm::vec3& value);
		void SetXYZ(const std::string& label, float x, float y, float z);
		void SetVec4(const std::string& label, const glm::vec4& value);
		void SetXYZW(const std::string& label, float x, float y, float z, float w);
		void SetMat2(const std::string& label, const glm::mat2& mat);
		void SetMat3(const std::string& label, const glm::mat3& mat);
		void SetMat4(const std::string& label, const glm::mat4& mat);

		/// <summary>
		/// Remove the current activated shader.
		/// </summary>
		static void ClearCurrentShader();

		/// <summary>
		/// Current existing shaders
		/// </summary>
		static int GetInstanceCount();
	private:
		/// <summary>
		/// Get uniforms from cache if founded, otherwise get from GPU and save it.
		/// </summary>
		unsigned int GetUniform(const std::string& label);

		/// <summary>
		/// Return shader compilation errors.
		/// </summary>
		static std::string GetError(unsigned int shader, const std::string& type);

		/// <summary>
		/// The ID from current active shader.
		/// </summary>
		static unsigned int currentID;
	};

	typedef std::shared_ptr<Shader> ShaderPtr;
}}}