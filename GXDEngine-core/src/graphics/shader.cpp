// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "../stdafx.h"
#include "shader.h"
#include "../debug.h"

namespace GXDEngine { namespace graphics {

	Shader::Shader(const char* vertPath, const char* fragPath) :
		m_VertPath(vertPath), m_FragPath(fragPath)
	{
		m_ShaderID = load();
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderID);
	}



	void Shader::setUniform1iv(const GLchar* name, const int count, const int* value) {
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1fv(const GLchar* name, const int count, const float* value) {
		glUniform1fv(getUniformLocation(name), count, value);
	}



	void Shader::setUniform1i(const GLchar* name, const int& value) {
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform1f(const GLchar* name, const float& value) {
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const maths::vec2& vec) {
		glUniform2f(getUniformLocation(name), vec.m_x, vec.m_y);
		float res[2] = { 0,0 };
		glGetUniformfv(m_ShaderID, getUniformLocation(name), res);
#if _GXDE_ENABLE_DEBUG
		GLuint error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "setUni2f: " << error << std::endl;
#endif
	}
	
	void Shader::setUniform3f(const GLchar* name, const maths::vec3& vec) {
		glUniform3f(getUniformLocation(name), vec.m_x, vec.m_y, vec.m_z);
	}
	
	void Shader::setUniform4f(const GLchar* name, const maths::vec4& vec) {
		glUniform4f(getUniformLocation(name), vec.m_x, vec.m_y, vec.m_z, vec.m_w);
	}
	
	void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.m_elements);
	}



	GLuint Shader::load() {

		GLint result;

		glGetIntegerv(GL_SHADER_COMPILER, &result);
#if _GXDE_ENABLE_DEBUG
		if (result == GL_FALSE) {
			std::cout << "Shader compiling not supported by hardware!" << std::endl;
			return 0;
		}
#endif
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = read_file(m_VertPath);
		std::string fragSourceString = read_file(m_FragPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

#if _GXDE_ENABLE_DEBUG		
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}
#endif
		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

#if _GXDE_ENABLE_DEBUG
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}
#endif
		glAttachShader(program, vertex);
#if _GXDE_ENABLE_DEBUG
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Attatch Vertex Shader Error: " << error << std::endl;
#endif
		glAttachShader(program, fragment);
#if _GXDE_ENABLE_DEBUG
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Attatch Vertex Shader Error: " << error << std::endl;
#endif
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &result);
#if _GXDE_ENABLE_DEBUG
		if (result == GL_FALSE)
		{
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(program, length, &length, &error[0]);
			std::cout << "Failed to link program!" << std::endl << &error[0] << std::endl;
			glDeleteProgram(program);
			return 0;
		}
#endif
		glValidateProgram(program);

#if _GXDE_ENABLE_DEBUG
		glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(program, length, &length, &error[0]);
			std::cout << "Failed to validate program!" << std::endl << &error[0] << std::endl;
			glDeleteProgram(program);
			return 0;
		}

		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;
#endif
		glDeleteShader(vertex);
#if _GXDE_ENABLE_DEBUG
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Delete Vertex Shader Error: " << error << std::endl;
#endif
		glDeleteShader(fragment);
#if _GXDE_ENABLE_DEBUG
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Delete Fragment Shader Error: " << error << std::endl;
#endif
		return program;
	}

	void Shader::enable() const  {
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() const  {
		glUseProgram(0);
	}

	GLint Shader::getUniformLocation(const GLchar* name)  {
		GLint res = glGetUniformLocation(m_ShaderID, name);
#if _GXDE_ENABLE_DEBUG
		GLuint error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "getUniformLocation: " << error << std::endl;
#endif
		return res;
	}

} }