#include "vector3D.h"
using Math::vector3D;

vector3D Math::operator+(const vector3D& left, const vector3D& right)
{
	return vector3D(left.x + right.x, left.y + right.y, left.z + right.z);
}

vector3D Math::operator*(float scalar, const vector3D& right)
{
	return vector3D(scalar * right.x, scalar*right.y, scalar*right.z);
}

vector3D Math::operator*(const vector3D& left, float scalar)
{
	return scalar * left;
}

vector3D& vector3D::operator+=(const vector3D& right)
{
	*this = *this + right;// slower compared to normal float arithmatic
	return *this;
}
vector3D& vector3D::operator-=(const vector3D& right)
{
	x -= right.x;// faster compared to creating a temp object
	y -= right.y;
	z -= right.z;
	return *this;
}
//vector3D& vector3D::operator=(const vector3D& right)
//{
//	x = right.x;
//	y = right.y;
//	z = right.z;
//	return *this;
//}
//vector3D::vector3D(const vector3D& source)
//{
//	x = source.x;
//	y = source.y;
//	z = source.z;
//}





