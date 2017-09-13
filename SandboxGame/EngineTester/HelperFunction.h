#pragma once
#include <cmath>
inline bool closeEnough(float left, float right, float threshold = 0.00001f)
{
	bool b = abs(left - right) < threshold;
	return abs(left - right) < threshold;
}