#pragma once
#include<cmath>
namespace Math {

	struct __declspec(dllexport) vector3D
	{
		float x;
		float y;
		float z;
		explicit vector3D(float i = 0.0f, float j = 0.0f, float k = 0.0f) : x(i), y(j), z(k) {}// explicit will make sure that Compiler will not be type casting anything automatically
		vector3D& operator+= (const vector3D& right);
		vector3D& operator-= (const vector3D& right);
		vector3D perpCwXY() const;
		vector3D perpCcwXY() const;
		float dot(const vector3D& second) const;
		float magnitude()const;
		vector3D normalized()const;
		float magnitudeSquared() const;
		vector3D projectOnto(const vector3D& target) const;
		//vector3D& operator= (const vector3D& right);
		//vector3D (const vector3D& source);

	};

	__declspec(dllexport) vector3D operator+(const vector3D& left, const vector3D& right);
	__declspec(dllexport) vector3D operator-(const vector3D& left, const vector3D& right);
	__declspec(dllexport) vector3D operator*(float scalar, const vector3D& right);
	__declspec(dllexport) vector3D operator*(const vector3D& left, float scalar);
	__declspec(dllexport) vector3D lerp(float alpha, const vector3D& source, const vector3D target);

}