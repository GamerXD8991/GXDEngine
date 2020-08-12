#pragma once
#pragma optimize( "f", on )

#define _USE_MATH_DEFINES
#include <math.h>

namespace GXDEngine { namespace maths {
	inline float toRadians(float degrees)  {
		return (float) ((double) degrees * M_PI / 180.0f);
	}
} }