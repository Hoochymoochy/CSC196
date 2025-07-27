#pragma once
#include <stdlib.h>
#include <cmath>
#include <corecrt_math_defines.h>
namespace math {
	
	inline float degToRad(float degrees) {
		return degrees * (M_PI / 180.0f);
	}
	using std::sqrt;
	using std::atan2f;
	using std::cosf;
	using std::sinf;
};