#pragma once

namespace Math {

	struct __declspec(dllexport) vector2D
	{
		float x;
		float y;
		explicit vector2D(float i = 0.0f, float j = 0.0f) : x(i), y(j) {}// explicit will make sure that Compiler will not be type casting anything automatically
		vector2D& operator+= (const vector2D& right);
		vector2D& operator-= (const vector2D& right);
		//vector2D& operator= (const vector2D& right);
		//vector2D (const vector2D& source);
		
	};

	__declspec(dllexport) vector2D operator+(const vector2D& left, const vector2D& right);
	__declspec(dllexport) vector2D operator*(float scalar, const vector2D& right);
	__declspec(dllexport) vector2D operator*(const vector2D& left, float scalar);

}