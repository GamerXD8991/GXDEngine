#pragma optimize( "f", on )
#include "vec4.h"

namespace GXDEngine {
	namespace maths {

		vec4::vec4(const float& x, const float& y, const float& z, const float& w) {
			this->m_x = x;
			this->m_y = y;
			this->m_z = z;
			this->m_w = w;
		}



		vec4& vec4::add(const vec4& other) {
			m_x += other.m_x;
			m_y += other.m_y;
			m_z += other.m_z;
			m_w += other.m_w;

			return *this;
		}

		vec4& vec4::subtract(const vec4& other) {
			m_x -= other.m_x;
			m_y -= other.m_y;
			m_z -= other.m_z;
			m_w -= other.m_w;

			return *this;
		}

		vec4& vec4::multiply(const vec4& other) {
			m_x *= other.m_x;
			m_y *= other.m_y;
			m_z *= other.m_z;
			m_w *= other.m_w;

			return *this;
		}

		vec4& vec4::divide(const vec4& other) {
			m_x /= other.m_x;
			m_y /= other.m_y;
			m_z /= other.m_z;
			m_w /= other.m_w;

			return *this;
		}



		vec4 operator+(vec4 left, const vec4& right) {
			return left.add(right);
		}

		vec4 operator-(vec4 left, const vec4& right) {
			return left.subtract(right);
		}

		vec4 operator*(vec4 left, const vec4& right) {
			return left.multiply(right);
		}

		vec4 operator/(vec4 left, const vec4& right) {
			return left.divide(right);
		}



		bool vec4::operator==(const vec4& other) {
			return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z && m_w == other.m_w;
		}

		bool vec4::operator!=(const vec4& other) {
			return !(*this == other);
		}



		vec4& vec4::operator+=(const vec4& other) {
			return add(other);
		}

		vec4& vec4::operator-=(const vec4& other) {
			return subtract(other);
		}

		vec4& vec4::operator*=(const vec4& other) {
			return multiply(other);
		}

		vec4& vec4::operator/=(const vec4& other) {
			return divide(other);
		}

		std::ostream& operator<<(std::ostream& stream, const vec4& vector) {
			stream << "vec4: (" << vector.m_x << ", " << vector.m_y << ", " << vector.m_z << ", " << vector.m_w << ")";
			return stream;
		}


	}
}