#pragma once
#include "vector2d.h"
#include <cmath>
//float cos(float);
//float sin(float);

namespace Math
{
	struct __declspec(dllexport) matrix2D
	{
		float r0c0, r0c1,
			  r1c0, r1c1;
		explicit matrix2D(float r0c0 = 1.0f, float r0c1 = 0.0f,
			float r1c0 = 0.0f, float r1c1 = 1.0f);

		vector2D operator*(const vector2D& rhs);
		static matrix2D rotate(float angleInRadians);
	};





}
