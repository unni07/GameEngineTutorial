#include "vector3D.h"
using Math::vector3D;

vector3D Math::operator+(const vector3D& left, const vector3D& right)
{
	return vector3D(left.x + right.x, left.y + right.y, left.z + right.z);
}

vector3D Math::operator-(const vector3D & left, const vector3D & right)
{
	return vector3D(
		left.x - right.x, 
		left.y - right.y, 
		left.z - right.z);
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
vector3D Math::vector3D::perpCwXY() const
{
	return vector3D(this->y,-this->x,this->z);
}
vector3D Math::vector3D::perpCcwXY() const
{
	return vector3D(-this->y, this->x, this->z);
}

float Math::vector3D::dot(const vector3D & second) const
{
	return x*second.x+y*second.y+z*second.z;
}

float Math::vector3D::magnitude() const
{
	return sqrt(this->dot(*this));
}

vector3D Math::vector3D::normalized() const
{
	float inverseMagnitude = 1.0f / magnitude();

	return inverseMagnitude* (*this);
}

float Math::vector3D::magnitudeSquared() const
{
	return this->dot(*this);
}

vector3D Math::vector3D::projectOnto(const vector3D & target) const
{
	return (this->dot(target)/target.magnitudeSquared()) * target;
}

vector3D Math::lerp(float alpha, const vector3D & source, const vector3D target)
{

	return (1.0f-alpha)*source + alpha * target;
}
