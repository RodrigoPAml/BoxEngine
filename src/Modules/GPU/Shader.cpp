#include <BoxEngine.hpp>
#include "Shader.hpp"

namespace BoxEngine {
namespace Modules {
namespace GPU {

	int Shader::TotalInstances = 0;

	Shader::Shader(
		const std::string& verticeShader, 
		const std::string& fragmentShader, 
		const std::string& geometryShader
	)
	{
		Shader::TotalInstances++;

		this->id = 0;

		std::string error = "";

		char* VS = nullptr;
		char* FS = nullptr;
		char* GS = nullptr;

		if(verticeShader.size() > 0)
		{
			VS = new char[verticeShader.size() + 1];
			strcpy(VS, verticeShader.c_str());
		}
		else 
			Debug::Logging::LogException("[Shader]: Vertex shader is empty", Debug::LogOrigin::Engine);

		if(fragmentShader.size() > 0)
		{
			FS = new char[fragmentShader.size() + 1];
			strcpy(FS, fragmentShader.c_str());
		}
			
		if(geometryShader.size() > 0)
		{
			GS = new char[geometryShader.size() + 1];
			strcpy(GS, geometryShader.c_str());
		}		
			
		unsigned int vertex, fragment, geometry;

		vertex = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertex, 1, &VS, NULL);
		glCompileShader(vertex);

		error = Shader::GetError(vertex, "VertexData");
			
		if(!error.empty())
		{
			glDeleteShader(vertex);

			delete[] VS;
			delete[] FS;
			delete[] GS;

			Debug::Logging::LogException("[Shader]: Error compiling vertex shader: " + error, Debug::LogOrigin::Engine);
		}

		if (!fragmentShader.empty())
		{
			fragment = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(fragment, 1, &FS, NULL);
			glCompileShader(fragment);

			error = Shader::GetError(fragment, "FRAGMENT");

			if (!error.empty())
			{
				glDeleteShader(vertex);
				glDeleteShader(fragment);

				delete[] VS;
				delete[] FS;
				delete[] GS;

				Debug::Logging::LogException("[Shader]: Error compiling fragment shader: " + error, Debug::LogOrigin::Engine);
			}
		}

		if(!geometryShader.empty())
		{
			geometry = glCreateShader(GL_GEOMETRY_SHADER);

			glShaderSource(geometry, 1, &GS, NULL);
			glCompileShader(geometry);

			error = Shader::GetError(fragment, "GEOMETRY");

			if(!error.empty())
			{
				glDeleteShader(vertex);
				glDeleteShader(fragment);
				glDeleteShader(geometry);

				delete[] VS;
				delete[] FS;
				delete[] GS;

				Debug::Logging::LogException("[Shader]: Error compiling geometry shader: " + error, Debug::LogOrigin::Engine);
			}
		}

		this->id = glCreateProgram();

		glAttachShader(this->id, vertex);

		if(!fragmentShader.empty())
			glAttachShader(this->id, fragment);

		if(!geometryShader.empty())
			glAttachShader(this->id, geometry);

		glLinkProgram(this->id);

		error = Shader::GetError(fragment, "FRAGMENT");

		glDeleteShader(vertex);

		if (!fragmentShader.empty())
			glDeleteShader(fragment);

		if (!geometryShader.empty())
			glDeleteShader(geometry);

		delete[] VS;
		delete[] FS;
		delete[] GS;

		if(!error.empty())
		{
			glDeleteShader(this->id);

			this->id = 0;

			Debug::Logging::LogException("[Shader]: Error compiling shader: " + error, Debug::LogOrigin::Engine);
		}

		if (this->id == 0)
			Debug::Logging::LogException("[Shader]: Failed to create shader, unknow exception", Debug::LogOrigin::Engine);
		else 
			Debug::Logging::Log("[Shader]: Created with id " + std::to_string(this->id), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);
	}

	Shader::~Shader()
	{
		Shader::TotalInstances--;

		if(this->id != 0)
		{
			if(Shader::currentID == this->id)
			{
				Shader::currentID = 0;
				glUseProgram(0);
			}

			Debug::Logging::Log("[Shader]: Deleted with id " + std::to_string(this->id), Debug::LogSeverity::Notify, Debug::LogOrigin::EngineInternal);

			glDeleteProgram(this->id);
		}
	}

	unsigned int Shader::GetId() const
	{
		return this->id;
	}

	void Shader::Use() const
	{
		if (this->id == 0)
			Debug::Logging::LogException("[Shader]: Cant use an empty shader", Debug::LogOrigin::Engine);

		glUseProgram(this->id);
		Shader::currentID = this->id;
	}
	
	void Shader::SetBool(const std::string& label, bool value) 
	{
		glUniform1i(GetUniform(label), (int)value);
	}

	void Shader::SetInt(const std::string& label, int value) 
	{
		glUniform1i(GetUniform(label), value);
	}

	void Shader::SetFloat(const std::string& label, float value) 
	{
		glUniform1f(GetUniform(label), value);
	}

	void Shader::SetVec2(const std::string& label, const glm::vec2& value) 
	{
		glUniform2fv(GetUniform(label), 1, &value[0]);
	}

	void Shader::SetXY(const std::string& label, float x, float y) 
	{
		glUniform2f(GetUniform(label), x, y);
	}

	void Shader::SetVec3(const std::string& label, const glm::vec3& value) 
	{
		glUniform3fv(GetUniform(label), 1, &value[0]);
	}

	void Shader::SetXYZ(const std::string& label, float x, float y, float z) 
	{
		glUniform3f(GetUniform(label), x, y, z);
	}

	void Shader::SetVec4(const std::string& label, const glm::vec4& value) 
	{
		glUniform4fv(GetUniform(label), 1, &value[0]);
	}

	void Shader::SetXYZW(const std::string& label, float x, float y, float z, float w) 
	{
		glUniform4f(GetUniform(label), x, y, z, w);
	}

	void Shader::SetMat2(const std::string& label, const glm::mat2& mat) 
	{
		glUniformMatrix2fv(GetUniform(label), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat3(const std::string& label, const glm::mat3& mat) 
	{
		glUniformMatrix3fv(GetUniform(label), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat4(const std::string& label, const glm::mat4& mat) 
	{
		glUniformMatrix4fv(GetUniform(label), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::ClearCurrentShader()
	{
		glUseProgram(0);
		Shader::currentID = 0;
	}

	int Shader::GetInstanceCount()
	{
		return Shader::TotalInstances;
	}

	unsigned int Shader::GetUniform(const std::string& label)
	{
		if (this->id == 0)
			Debug::Logging::LogException("[Shader]: Cant get an uniform on an empty shader", Debug::LogOrigin::Engine);

		unsigned int uniform;
		auto it = this->uniforms.find(label);

		if (it != this->uniforms.end())
			uniform = it->second;
		else
		{
			uniform = glGetUniformLocation(this->id, label.c_str());
			this->uniforms[label] = uniform;
		}

		return uniform;
	}

	std::string Shader::GetError(unsigned int shader, const std::string& type)
	{
		GLint success = 0;
		GLchar error[1024];

		if(type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if(!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, error);

				return error;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);

			if(!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, error);
					
				return error;
			}
		}

		return "";
	}

	unsigned int Shader::currentID = 0;
}}}
