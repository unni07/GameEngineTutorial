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