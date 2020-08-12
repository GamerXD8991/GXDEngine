#pragma once
#pragma optimize( "f", on )

#include "../stdafx.h"

namespace GXDEngine { namespace graphics {

	class Shader {
	private:
		GLuint m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;

	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void setUniform1iv(const GLchar* name, const int count, const int* value);
		void setUniform1fv(const GLchar* name,const int count, const float* value);

		void setUniform1i(const GLchar* name, const int& value);
		void setUniform1f(const GLchar* name, const float& value);
		void setUniform2f(const GLchar* name, const maths::vec2& vec);
		void setUniform3f(const GLchar* name, const maths::vec3& vec);
		void setUniform4f(const GLchar* name, const maths::vec4& vec);
		void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

		void enable() const;
		void disable() const;

		inline GLuint getShaderID()  { return m_ShaderID; }

	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);

	};

} }