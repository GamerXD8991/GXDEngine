// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "../stdafx.h"

namespace GXDEngine { namespace maths {

	mat4::mat4()  {
		A_memset(m_elements, 0, 16 * sizeof(float));
	}

	mat4::mat4(float diagonal)  {

		//for (int i = 0; i < 16; ++i) {
		//	m_elements[i] = 0.0f;
		//}

		A_memset(m_elements, 0, 16 * sizeof(float));

		m_elements[0 + 0 * 4] = diagonal;
		m_elements[1 + 1 * 4] = diagonal;
		m_elements[2 + 2 * 4] = diagonal;
		m_elements[3 + 3 * 4] = diagonal;

	}



	mat4 mat4::identity() {
		return mat4(1.0f);
	}

	

	mat4& mat4::invert()  {
	
		float temp[16];

		temp[0] = m_elements[5] * m_elements[10] * m_elements[15] -
			m_elements[5] * m_elements[11] * m_elements[14] -
			m_elements[9] * m_elements[6] * m_elements[15] +
			m_elements[9] * m_elements[7] * m_elements[14] +
			m_elements[13] * m_elements[6] * m_elements[11] -
			m_elements[13] * m_elements[7] * m_elements[10];

		temp[4] = -m_elements[4] * m_elements[10] * m_elements[15] +
			m_elements[4] * m_elements[11] * m_elements[14] +
			m_elements[8] * m_elements[6] * m_elements[15] -
			m_elements[8] * m_elements[7] * m_elements[14] -
			m_elements[12] * m_elements[6] * m_elements[11] +
			m_elements[12] * m_elements[7] * m_elements[10];

		temp[8] = m_elements[4] * m_elements[9] * m_elements[15] -
			m_elements[4] * m_elements[11] * m_elements[13] -
			m_elements[8] * m_elements[5] * m_elements[15] +
			m_elements[8] * m_elements[7] * m_elements[13] +
			m_elements[12] * m_elements[5] * m_elements[11] -
			m_elements[12] * m_elements[7] * m_elements[9];

		temp[12] = -m_elements[4] * m_elements[9] * m_elements[14] +
			m_elements[4] * m_elements[10] * m_elements[13] +
			m_elements[8] * m_elements[5] * m_elements[14] -
			m_elements[8] * m_elements[6] * m_elements[13] -
			m_elements[12] * m_elements[5] * m_elements[10] +
			m_elements[12] * m_elements[6] * m_elements[9];

		temp[1] = -m_elements[1] * m_elements[10] * m_elements[15] +
			m_elements[1] * m_elements[11] * m_elements[14] +
			m_elements[9] * m_elements[2] * m_elements[15] -
			m_elements[9] * m_elements[3] * m_elements[14] -
			m_elements[13] * m_elements[2] * m_elements[11] +
			m_elements[13] * m_elements[3] * m_elements[10];

		temp[5] = m_elements[0] * m_elements[10] * m_elements[15] -
			m_elements[0] * m_elements[11] * m_elements[14] -
			m_elements[8] * m_elements[2] * m_elements[15] +
			m_elements[8] * m_elements[3] * m_elements[14] +
			m_elements[12] * m_elements[2] * m_elements[11] -
			m_elements[12] * m_elements[3] * m_elements[10];

		temp[9] = -m_elements[0] * m_elements[9] * m_elements[15] +
			m_elements[0] * m_elements[11] * m_elements[13] +
			m_elements[8] * m_elements[1] * m_elements[15] -
			m_elements[8] * m_elements[3] * m_elements[13] -
			m_elements[12] * m_elements[1] * m_elements[11] +
			m_elements[12] * m_elements[3] * m_elements[9];

		temp[13] = m_elements[0] * m_elements[9] * m_elements[14] -
			m_elements[0] * m_elements[10] * m_elements[13] -
			m_elements[8] * m_elements[1] * m_elements[14] +
			m_elements[8] * m_elements[2] * m_elements[13] +
			m_elements[12] * m_elements[1] * m_elements[10] -
			m_elements[12] * m_elements[2] * m_elements[9];

		temp[2] = m_elements[1] * m_elements[6] * m_elements[15] -
			m_elements[1] * m_elements[7] * m_elements[14] -
			m_elements[5] * m_elements[2] * m_elements[15] +
			m_elements[5] * m_elements[3] * m_elements[14] +
			m_elements[13] * m_elements[2] * m_elements[7] -
			m_elements[13] * m_elements[3] * m_elements[6];

		temp[6] = -m_elements[0] * m_elements[6] * m_elements[15] +
			m_elements[0] * m_elements[7] * m_elements[14] +
			m_elements[4] * m_elements[2] * m_elements[15] -
			m_elements[4] * m_elements[3] * m_elements[14] -
			m_elements[12] * m_elements[2] * m_elements[7] +
			m_elements[12] * m_elements[3] * m_elements[6];

		temp[10] = m_elements[0] * m_elements[5] * m_elements[15] -
			m_elements[0] * m_elements[7] * m_elements[13] -
			m_elements[4] * m_elements[1] * m_elements[15] +
			m_elements[4] * m_elements[3] * m_elements[13] +
			m_elements[12] * m_elements[1] * m_elements[7] -
			m_elements[12] * m_elements[3] * m_elements[5];

		temp[14] = -m_elements[0] * m_elements[5] * m_elements[14] +
			m_elements[0] * m_elements[6] * m_elements[13] +
			m_elements[4] * m_elements[1] * m_elements[14] -
			m_elements[4] * m_elements[2] * m_elements[13] -
			m_elements[12] * m_elements[1] * m_elements[6] +
			m_elements[12] * m_elements[2] * m_elements[5];

		temp[3] = -m_elements[1] * m_elements[6] * m_elements[11] +
			m_elements[1] * m_elements[7] * m_elements[10] +
			m_elements[5] * m_elements[2] * m_elements[11] -
			m_elements[5] * m_elements[3] * m_elements[10] -
			m_elements[9] * m_elements[2] * m_elements[7] +
			m_elements[9] * m_elements[3] * m_elements[6];

		temp[7] = m_elements[0] * m_elements[6] * m_elements[11] -
			m_elements[0] * m_elements[7] * m_elements[10] -
			m_elements[4] * m_elements[2] * m_elements[11] +
			m_elements[4] * m_elements[3] * m_elements[10] +
			m_elements[8] * m_elements[2] * m_elements[7] -
			m_elements[8] * m_elements[3] * m_elements[6];

		temp[11] = -m_elements[0] * m_elements[5] * m_elements[11] +
			m_elements[0] * m_elements[7] * m_elements[9] +
			m_elements[4] * m_elements[1] * m_elements[11] -
			m_elements[4] * m_elements[3] * m_elements[9] -
			m_elements[8] * m_elements[1] * m_elements[7] +
			m_elements[8] * m_elements[3] * m_elements[5];

		temp[15] = m_elements[0] * m_elements[5] * m_elements[10] -
			m_elements[0] * m_elements[6] * m_elements[9] -
			m_elements[4] * m_elements[1] * m_elements[10] +
			m_elements[4] * m_elements[2] * m_elements[9] +
			m_elements[8] * m_elements[1] * m_elements[6] -
			m_elements[8] * m_elements[2] * m_elements[5];

		float determinant = m_elements[0] * temp[0] + m_elements[1] * temp[4] + m_elements[2] * temp[8] + m_elements[3] * temp[12];
		determinant = 1.0f / determinant;

		for (int i = 0; i < 16; i++) //-V112
			m_elements[i] = temp[i] * determinant;

		return *this;

	}



	mat4& mat4::multiply(const mat4& other)  {

		float data[16];

#pragma loop (hint_parallel (4))

		for (int y = 0; y < 4; ++y) { //-V112
			for (int x = 0; x < 4; ++x) { //-V112
				float sum = 0.0f;
				for (int e = 0; e < 4; ++e) { //-V112
					sum += m_elements[x + e * 4] * other.m_elements[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
		A_memcpy(m_elements, data, 16 * sizeof(float));

		return *this;
	}

	mat4& mat4::multiply(const bool bol)  {
		
		if (!bol) A_memset(m_elements, 0, 16 * sizeof(float));

		return *this;
	}



	vec4 mat4::multiply(const vec4& vec) const {

		const float x = vec.m_x;
		const float y = vec.m_y;
		const float z = vec.m_z;
		const float w = vec.m_w;
		 
		const float x1 = m_elements[0 + 0 * 4] * x;
		const float x2 = m_elements[1 + 0 * 4] * x;
		const float x3 = m_elements[2 + 0 * 4] * x;
		const float x4 = m_elements[3 + 0 * 4] * x;
		 
		const float y1 = m_elements[0 + 1 * 4] * y;
		const float y2 = m_elements[1 + 1 * 4] * y;
		const float y3 = m_elements[2 + 1 * 4] * y;
		const float y4 = m_elements[3 + 1 * 4] * y;
		 
		const float z1 = m_elements[0 + 2 * 4] * z;
		const float z2 = m_elements[1 + 2 * 4] * z;
		const float z3 = m_elements[2 + 2 * 4] * z;
		const float z4 = m_elements[3 + 2 * 4] * z;
		 
		const float w1 = m_elements[0 + 2 * 4] * w;
		const float w2 = m_elements[1 + 2 * 4] * w;
		const float w3 = m_elements[2 + 2 * 4] * w;
		const float w4 = m_elements[3 + 2 * 4] * w;

		return vec4(x1 + y1 + z1 + w1, x2 + y2 + z2 + w2, x3 + y3 + z3 + w3, x4 + y4 + z4 + w4);
	}

	vec3 mat4::multiply(const vec3& vec) const {
		const float x = vec.m_x;
		const float y = vec.m_y;
		const float z = vec.m_z;
		 
		const float x1 = m_elements[0 + 0 * 4] * x;
		const float x2 = m_elements[1 + 0 * 4] * x;
		const float x3 = m_elements[2 + 0 * 4] * x;
		const float x4 = m_elements[3 + 0 * 4] * x;
		 
		const float y1 = m_elements[0 + 1 * 4] * y;
		const float y2 = m_elements[1 + 1 * 4] * y;
		const float y3 = m_elements[2 + 1 * 4] * y;
		const float y4 = m_elements[3 + 1 * 4] * y;
		 
		const float z1 = m_elements[0 + 2 * 4] * z;
		const float z2 = m_elements[1 + 2 * 4] * z;
		const float z3 = m_elements[2 + 2 * 4] * z;
		const float z4 = m_elements[3 + 2 * 4] * z;
		 
		const float w1 = m_elements[12];
		const float w2 = m_elements[13];
		const float w3 = m_elements[14];

		return vec3(x1 + y1 + z1 + w1, x2 + y2 + z2 + w2, x3 + y3 + z3 + w3);
	}



	mat4 operator*(mat4 left, const mat4& right) {
		return left.multiply(right);
	}
	
	mat4 operator*(mat4 left, const bool bol) {
		return left.multiply(bol);
	}



	mat4& mat4::operator*=(const mat4& other) {
		return multiply(other);
	}

	mat4& mat4::operator*=(const bool bol) {
		return multiply(bol);
	}



	vec4 operator*(const mat4& left, const vec4& vec) {
		return left.multiply(vec);
	}


	vec3 operator*(const mat4& left, const vec3& vec) {
		return left.multiply(vec);
	}



	mat4 mat4::orthographic(float leftVal, float rightVal, float bottomVal, float topVal, float nearVal, float farVal) {
		mat4 result(1.0f);

		result.m_elements[0 + 0 * 4] = 2.0f / (rightVal - leftVal);

		result.m_elements[1 + 1 * 4] = 2.0f / (topVal - bottomVal);

		result.m_elements[2 + 2 * 4] = 2.0f / (nearVal - farVal);

		result.m_elements[0 + 3 * 4] = (leftVal + rightVal) / (leftVal - rightVal);
		result.m_elements[1 + 3 * 4] = (bottomVal + topVal) / (bottomVal - topVal);
		result.m_elements[2 + 3 * 4] = (farVal + nearVal) / (farVal - nearVal);

		return result;
	}

	mat4 mat4::perspective(float fovVal, float aspectRatioVal, float nearVal, float farVal) {
		mat4 result(0.0f);

		const float top = nearVal * tan(toRadians(0.5f * fovVal));
		const float bottom = -top;
		const float right = top * aspectRatioVal;
		const float left = -right;
 
		const float n2 = 2.0f * nearVal;
		const float fmn = farVal - nearVal;
		const float c = n2 * farVal / fmn ;

		result.m_elements[0 + 0 * 4] = n2 / (float) (2.0f * right);	//0
		result.m_elements[1 + 1 * 4] = n2 / (float) (2.0f * top);	//5
		result.m_elements[2 + 2 * 4] = - (farVal + nearVal) / fmn;	//10
		result.m_elements[3 + 2 * 4] = -1.0f;						//11
		result.m_elements[2 + 3 * 4] = - c ;						//14

		return result;
	}



	mat4 mat4::translation(const vec3& translation) {
		mat4 result(1.0f);

		result.m_elements[0 + 3 * 4] = translation.m_x;
		result.m_elements[1 + 3 * 4] = translation.m_y;
		result.m_elements[2 + 3 * 4] = translation.m_z;
		
		return result;
	}

	mat4 mat4::rotation(float angle, const vec3& axis) {
		mat4 result(1.0f);

		const float r = toRadians(angle);
		const float c = cos(r);
		const float s = sin(r);
		const float omc = 1.0f - c; //One minus c
		 
		const float x = axis.m_x;
		const float y = axis.m_y;
		const float z = axis.m_z;

		result.m_elements[0 + 0 * 4] = x * x * omc + c;
		result.m_elements[1 + 0 * 4] = x * y * omc + z * s;
		result.m_elements[2 + 0 * 4] = x * z * omc - y * s;

		result.m_elements[0 + 1 * 4] = y * x * omc - z * s;
		result.m_elements[1 + 1 * 4] = y * y * omc + c;
		result.m_elements[2 + 1 * 4] = y * z * omc + x * s;
		
		result.m_elements[0 + 2 * 4] = z * x * omc + y * s;
		result.m_elements[1 + 2 * 4] = z * y * omc - x * s;
		result.m_elements[2 + 2 * 4] = z * z * omc + c;

		return result;
	}

	mat4 mat4::scale(const vec3& scale) {
		mat4 result(1.0f);

		result.m_elements[0 + 0 * 4] = scale.m_x;
		result.m_elements[1 + 1 * 4] = scale.m_y;
		result.m_elements[2 + 2 * 4] = scale.m_z;

		return result;
	}

} }