#include "matrix2DH.h"
//
using Math::matrix2DH;
//
//matrix2DH::matrix2DH(float r0c0, float r0c1,
//	float r1c0, float r1c1)
//{
//	this->r0c0 = r0c0;
//	this->r0c1 = r0c1;
//	this->r1c0 = r1c0;
//	this->r1c1 = r1c1;
//}
//
Math::vector3D matrix2DH::operator*(const Math::vector3D& rhs)
{
	/*vector3D temp;
	temp.x = this->r0c0 * rhs.x + this->r0c1 * rhs.y + this->r0c2 + rhs.z;
	temp.y = this->r1c0 * rhs.x + this->r1c1 * rhs.y + this->r1c2 + rhs.z;
	temp.z = this->r2c0 * rhs.x + this->r2c1 * rhs.y + this->r2c2 + rhs.z;

	return temp;*/

	return vector3D(
		this->r0c0 * rhs.x + this->r0c1 * rhs.y + this->r0c2 * rhs.z,
		this->r1c0 * rhs.x + this->r1c1 * rhs.y + this->r1c2 * rhs.z,
		rhs.z
	);
}
matrix2DH Math::matrix2DH::operator*(const matrix2DH & rhs)
{
	return matrix2DH(
		this->r0c0 * rhs.r0c0 + this->r0c1 * rhs.r1c0,
		this->r0c0 * rhs.r0c1 + this->r0c1 * rhs.r1c1,
		this->r0c0 * rhs.r0c2 + this->r0c1 * rhs.r1c2 + this->r0c2,

		this->r1c0 * rhs.r0c0 + this->r1c1 * rhs.r1c0,
		this->r1c0 * rhs.r0c1 + this->r1c1 * rhs.r1c1,
		this->r1c0 * rhs.r0c2 + this->r1c1 * rhs.r1c2 + this->r1c2);
}
//
matrix2DH Math::matrix2DH::rotateZ(float angleInRadians)
{
	float cosResult = cos(angleInRadians);
	float sinResult = sin(angleInRadians);
	return matrix2DH(
		cosResult, -sinResult, 0.0f,
		sinResult, cosResult, 0.0f);
}

matrix2DH Math::matrix2DH::translate(float x, float y)
{
	return matrix2DH(
		1, 0, x,
		0, 1, y);
}

matrix2DH Math::matrix2DH::translate(vector3D position)
{
	return translate(position.x,position.y);
}

matrix2DH Math::matrix2DH::scale(float x, float y)
{
	return matrix2DH(
		x, 0, 0,
		0, y, 0);
}
