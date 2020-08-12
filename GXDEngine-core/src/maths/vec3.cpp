#pragma optimize( "f", on )
#include "vec3.h"

namespace GXDEngine { namespace maths {

		vec3::vec3()  {
			m_x = 0.0f;
			m_y = 0.0f;
			m_z = 0.0f;
		}

		vec3::vec3(const float& x, const float& y, const float& z)  {
			m_x = x;
			m_y = y;
			m_z = z;
		}



		vec3& vec3::add(const vec3& other)  {
			m_x += other.m_x;
			m_y += other.m_y;
			m_z += other.m_z;

			return *this;
		}

		vec3& vec3::subtract(const vec3& other)  {
			m_x -= other.m_x;
			m_y -= other.m_y;
			m_z -= other.m_z;

			return *this;
		}

		vec3& vec3::multiply(const vec3& other)  {
			m_x *= other.m_x;
			m_y *= other.m_y;
			m_z *= other.m_z;

			return *this;
		}

		vec3& vec3::divide(const vec3& other)  {
			m_x /= other.m_x;
			m_y /= other.m_y;
			m_z /= other.m_z;

			return *this;
		}

		vec3 operator+(vec3 left, const vec3& right) {
			return left.add(right);
		}

		vec3 operator-(vec3 left, const vec3& right) {
			return left.subtract(right);
		}

		vec3 operator*(vec3 left, const vec3& right)
		{
			return left.multiply(right);
		}

		vec3 operator/(vec3 left, const vec3& right)
		{
			return left.divide(right);
		}



		vec3& vec3::operator+=(const vec3& other)
		{
			return add(other);
		}

		vec3& vec3::operator-=(const vec3& other)
		{
			return subtract(other);
		}

		vec3& vec3::operator*=(const vec3& other)
		{
			return multiply(other);
		}

		vec3& vec3::operator/=(const vec3& other)
		{
			return divide(other);
		}


		bool vec3::operator==(const vec3& other) const  {
			return (m_x == other.m_x && m_y == other.m_y);
		}

		bool vec3::operator!=(const vec3& other) const {
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vec) {
			stream << "vec: (" << vec.m_x << ", " << vec.m_y << ")";
			return stream;
		}

} }