#include "vector2D.h"
using Math::vector2D;

vector2D Math::operator+(const vector2D& left, const vector2D& right)
{
	return vector2D(left.x + right.x, left.y + right.y);
}

vector2D Math::operator*(float scalar, const vector2D& right)
{
	return vector2D(scalar * right.x, scalar*right.y);
}

vector2D Math::operator*(const vector2D& left, float scalar)
{
	return scalar * left;
}

vector2D& vector2D::operator+=(const vector2D& right)
{
	*this = *this + right;// slower compared to normal float arithmatic
	return *this;
}
vector2D& vector2D::operator-=(const vector2D& right)
{
	x -= right.x;// faster compared to creating a temp object
	y -= right.y;
	return *this;
}
//vector2D& vector2D::operator=(const vector2D& right)
//{
//	x = right.x;
//	y = right.y;
//	return *this;
//}
//vector2D::vector2D(const vector2D& source)
//{
//	x = source.x;
//	y = source.y;
//}





