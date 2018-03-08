#pragma once
#include "vector3D.h"
#include <cmath>
//float cos(float);
//float sin(float);

namespace Math
{
	struct __declspec(dllexport) matrix3D
	{
		float r0c0, r0c1, r0c2,
			  r1c0, r1c1, r1c2,
			  r2c0, r2c1, r2c2;

		explicit matrix3D(float r0c0 = 1.0f, float r0c1 = 0.0f, float r0c2 = 0.0f,
			float r1c0 = 0.0f, float r1c1 = 1.0f, float r1c2 = 0.0f,
			float r2c0 = 0.0f, float r2c1 = 0.0f, float r2c2 = 1.0f): 
			r0c0(r0c0), r0c1(r0c1), r0c2(r0c2),
			r1c0(r1c0), r1c1(r1c1), r1c2(r1c2),
			r2c0(r2c0), r2c1(r2c1), r2c2(r2c2){}
		vector3D operator*(const vector3D& rhs);
		matrix3D operator*(const matrix3D& rhs);
		static matrix3D rotateZ(float angleInRadians);
			static matrix3D translate(float x, float y);
	};





}
