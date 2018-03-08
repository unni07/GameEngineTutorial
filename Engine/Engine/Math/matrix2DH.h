#pragma once
#include "vector3D.h"
#include <cmath>
//float cos(float);
//float sin(float);

namespace Math
{
	struct __declspec(dllexport) matrix2DH
	{
		float r0c0, r0c1, r0c2,
			r1c0, r1c1, r1c2;

			explicit matrix2DH(float r0c0 = 1.0f, float r0c1 = 0.0f, float r0c2 = 0.0f,
				float r1c0 = 0.0f, float r1c1 = 1.0f, float r1c2 = 0.0f):
			r0c0(r0c0), r0c1(r0c1), r0c2(r0c2),
			r1c0(r1c0), r1c1(r1c1), r1c2(r1c2) {}
		vector3D operator*(const vector3D& rhs);
		matrix2DH operator*(const matrix2DH& rhs);
		static matrix2DH rotateZ(float angleInRadians);
		static matrix2DH translate(float x, float y);
		static matrix2DH translate(vector3D position);
		static matrix2DH scale(float x, float y);
	};





}
