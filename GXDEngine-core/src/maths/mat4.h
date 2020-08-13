#pragma once
#pragma optimize( "f", on )

#include "../stdafx.h"

namespace GXDEngine { namespace maths {

	struct mat4 {

		union {
			float m_elements[16];
			vec4 m_colums[4];
		};
		
		/* ordering coloum-major
			0  4   8  12 
			1  5   9  13
			2  6  10  14
			3  7  11  15
		*/


		mat4();
		mat4(float diagonal);

		vec4 getColumn(int index)
		{
			index *= 4; //-V112
			return vec4(m_elements[index], m_elements[index + 1], m_elements[index + 2], m_elements[index + 3]);
		}

		static mat4 identity();

		mat4& invert();

		mat4& multiply(const mat4& other);
		mat4& multiply(const bool bol);

		vec4 multiply(const vec4& vec) const;
		vec3 multiply(const vec3& vec) const;		

		friend mat4 operator*(mat4 left, const mat4& right);
		friend mat4 operator*(mat4 left, const bool bol);

		mat4& operator*=(const mat4& other);
		mat4& operator*=(const bool bol);
		
		friend vec4 operator*(const mat4& left, const vec4& vec);
		friend vec3 operator*(const mat4& left, const vec3& vec);

		static mat4 orthographic(float left, float right, float top, float bottom, float near, float far);
		static mat4 perspective(float fov, float aspectRatio, float near, float far);

		static mat4 translation(const vec3& translation);
		static mat4 rotation(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);
	};

} }