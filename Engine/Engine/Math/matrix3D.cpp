#include "matrix3D.h"
//
using Math::matrix3D;
//
//matrix3D::matrix3D(float r0c0, float r0c1,
//	float r1c0, float r1c1)
//{
//	this->r0c0 = r0c0;
//	this->r0c1 = r0c1;
//	this->r1c0 = r1c0;
//	this->r1c1 = r1c1;
//}
//
Math::vector3D matrix3D::operator*(const Math::vector3D& rhs)
{
	/*vector3D temp;
	temp.x = this->r0c0 * rhs.x + this->r0c1 * rhs.y + this->r0c2 + rhs.z;
	temp.y = this->r1c0 * rhs.x + this->r1c1 * rhs.y + this->r1c2 + rhs.z;
	temp.z = this->r2c0 * rhs.x + this->r2c1 * rhs.y + this->r2c2 + rhs.z;
	
	return temp;*/

	return vector3D(
		this->r0c0 * rhs.x + this->r0c1 * rhs.y + this->r0c2 * rhs.z, 
		this->r1c0 * rhs.x + this->r1c1 * rhs.y + this->r1c2 * rhs.z,
		this->r2c0 * rhs.x + this->r2c1 * rhs.y + this->r2c2 * rhs.z
		);
}
matrix3D Math::matrix3D::operator*(const matrix3D & rhs)
{
	return matrix3D(
		this->r0c0 * rhs.r0c0 + this->r0c1 * rhs.r1c0 + this->r0c2 * rhs.r2c0,
		this->r0c0 * rhs.r0c1 + this->r0c1 * rhs.r1c1 + this->r0c2 * rhs.r2c1,
		this->r0c0 * rhs.r0c2 + this->r0c1 * rhs.r1c2 + this->r0c2 * rhs.r2c2,
										 						 
		this->r1c0 * rhs.r0c0 + this->r1c1 * rhs.r1c0 + this->r1c2 * rhs.r2c0,
		this->r1c0 * rhs.r0c1 + this->r1c1 * rhs.r1c1 + this->r1c2 * rhs.r2c1,
		this->r1c0 * rhs.r0c2 + this->r1c1 * rhs.r1c2 + this->r1c2 * rhs.r2c2,
										 						 
		this->r2c0 * rhs.r0c0 + this->r2c1 * rhs.r1c0 + this->r2c2 * rhs.r2c0,
		this->r2c0 * rhs.r0c1 + this->r2c1 * rhs.r1c1 + this->r2c2 * rhs.r2c1,
		this->r2c0 * rhs.r0c2 + this->r2c1 * rhs.r1c2 + this->r2c2 * rhs.r2c2
		);
}
//
matrix3D Math::matrix3D::rotateZ(float angleInRadians)
{
	float cosResult = cos(angleInRadians);
	float sinResult = sin(angleInRadians);
	return matrix3D(
		cosResult, -sinResult, 0.0f,
		sinResult, cosResult, 0.0f,
		0.0f, 0.0f, 1.0f);
}

matrix3D Math::matrix3D::translate(float x , float y)
{
	return matrix3D(
	1,0,x,
    0,1,y,
    0,0,1);
}
