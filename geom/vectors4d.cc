#include <cmath>

#include "m4x4d.h"

#include "v3d.h"

using namespace math;


/***************************
 *
 *			m4x4d
 *
 * *************************/

m4x4d m4x4d::identity()
{
	m4x4d a;
	for(int i = 0; i < 4; ++i)
	{
		a.m[i*5] = 1;
	}
	return a;
}


m4x4d& m4x4d::transpose()
{
	double x;
	for(int f = 0; f < 4; ++f)
	{
		for(int c = 0; c < 4; ++c)
		{
			x = m[4*f + c];
			m[4*f + c] = m[4*c + f];
			m[4*c + f] = x;
		}
	}
	return *this;
}


v3d operator* (v3d v, const m4x4d& m)
{
	v3d r;
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			r.v[i] += v.v[j] * m.m[i + 4*j];
		}
		r.v[i] += m.m[i + 12];
	}
	return r;
}


v3d operator* (const m4x4d& m, v3d v)
{
	v3d r;
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			r.v[i] += v.v[j] * m.m[4*i + j];
		}
		r.v[i] += m.m[4*i + 3];
	}

	double k = m.m[12] + m.m[13] + m.m[14] + m.m[15];
	
	if(fabs(k - 1) > 0.000001)
	{
		r /= k;
	}
	return r;
}
