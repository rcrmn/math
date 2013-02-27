#include "v2d.h"

#include <cmath>

using namespace math;

v2d& v2d::normalize()
{
	math_float_t d = x*x + y*y;

	d = 1/sqrt(d);

	x *= d;
	y *= d;

	return *this;
}

math_float_t v2d::length() const
{
	return sqrt(x*x + y*y);
}

math_float_t v2d::sqlength() const
{
	return x*x + y*y;
}

math_float_t operator% (const v2d& a, const v2d& b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
