#pragma once

namespace Math {

	struct vector2D
	{
		float x;
		float y;
		explicit vector2D(float i = 0.0f , float j= 0.0f) :x(i), y(j) {}// explicit will make sure that Compiler will not be type casting anything automatically
		//vector2D() {}
	};

	/*inline vector2D operator+(const vector2D& left, const vector2D& right);
	inline vector2D operator*(float scalar, const vector2D& right);
	inline vector2D operator*(const vector2D& left, float scalar);
*/

	vector2D operator+(const vector2D& left, const vector2D& right)
	{
		return vector2D(left.x + right.x, left.y + right.y);
	}

	vector2D operator*(float scalar, const vector2D& right)
	{
		return vector2D(scalar * right.x, scalar*right.y);
	}

	vector2D operator*(const vector2D& left, float scalar)
	{
		return scalar * left;
	}
}