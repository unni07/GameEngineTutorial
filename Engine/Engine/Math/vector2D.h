#pragma once

namespace Math {

	struct vector2D
	{
		float x;
		float y;
		vector2D(float i = 0.0f , float j= 0.0f) :x(i), y(j) {}
		//vector2D() {}
	};

	inline vector2D operator+(const vector2D& left, const vector2D& right);
	inline vector2D operator*(float scalar, const vector2D& right);
	inline vector2D operator*(const vector2D& left, float scalar);
#include "vector2D.inl"
}