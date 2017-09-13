#include "matrix2D.h"

using Math::matrix2D;

matrix2D::matrix2D(float r0c0, float r0c1,
	float r1c0, float r1c1)
{
	this->r0c0 = r0c0;
	this->r0c1 = r0c1;
	this->r1c0 = r1c0;
	this->r1c1 = r1c1;
}

Math::vector2D matrix2D::operator*(const Math::vector2D& rhs)
{
	/*vector2D temp;
	temp.x = this->r0c0 * rhs.x + this->r0c1 * rhs.y;
	temp.y = this->r1c0 * rhs.x + this->r1c1 * rhs.y;
	return temp;*/

	return vector2D(this->r0c0 * rhs.x + this->r0c1 * rhs.y, this->r1c0 * rhs.x + this->r1c1 * rhs.y);
}

matrix2D Math::matrix2D::rotate(float angleInRadians)
{
	float cosResult = cos(angleInRadians);
	float sinResult = sin(angleInRadians);
	return matrix2D(
		cosResult,-sinResult,
		sinResult, cosResult);
}
