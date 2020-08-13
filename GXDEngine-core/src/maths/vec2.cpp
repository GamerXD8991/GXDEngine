// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )
#include "vec2.h"

namespace GXDEngine { namespace maths {

		vec2::vec2()  {
			m_x = 0.0f;
			m_y = 0.0f;
		}

		vec2::vec2(const float& x, const float& y)  {
			m_x = x;
			m_y = y;
		}



		vec2& vec2::add(const vec2& other)  {
			m_x += other.m_x;
			m_y += other.m_y;

			return *this;
		}

		vec2& vec2::subtract(const vec2& other)  {
			m_x -= other.m_x;
			m_y -= other.m_y;

			return *this;
		}

		vec2& vec2::multiply(const vec2& other)  {
			m_x *= other.m_x;
			m_y *= other.m_y;

			return *this;
		}

		vec2& vec2::divide(const vec2& other)  {
			m_x /= other.m_x;
			m_y /= other.m_y;

			return *this;
		}



		vec2 operator+(vec2 left, const vec2& right) {
			return left.add(right);
		}

		vec2 operator-(vec2 left, const vec2& right) {
			return left.subtract(right);
		}

		vec2 operator*(vec2 left, const vec2& right) {
			return left.multiply(right);
		}

		vec2 operator/(vec2 left, const vec2& right) {
			return left.divide(right);
		}



		vec2& vec2::operator+=(const vec2& other) {
			return add(other);
		}

		vec2& vec2::operator-=(const vec2& other) {
			return subtract(other);
		}

		vec2& vec2::operator*=(const vec2& other) {
			return multiply(other);
		}

		vec2& vec2::operator/=(const vec2& other) {
			return divide(other);
		}



		bool vec2::operator==(const vec2& other) const  {
			return (fabs(m_x - other.m_x) < 0.00000001) && (fabs(m_y - other.m_y) < 0.00000001);
			//return m_x == other.m_x && m_y == other.m_y;
		}

		bool vec2::operator!=(const vec2& other) const
		{
			return !(*this == other);
		}



		std::ostream& operator<<(std::ostream& stream, const vec2& vec) {
			stream << "vec: (" << vec.m_x << ", " << vec.m_y << ")";
			return stream;
		}

} }