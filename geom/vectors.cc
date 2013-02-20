#include <cmath>


#include "v3d.h"
#include "m3x3d.h"

namespace math
{


/***************************
 *
 *			v3d
 *
 * *************************/

v3d& v3d::normalize()
{
	double d = x*x + y*y + z*z;

	d = sqrt(d);

	x /= d;
	y /= d;
	z /= d;

	return *this;
}

double v3d::sqlength() const
{
	return (x*x + y*y + z*z);
}

double v3d::length() const
{
	return sqrt(x*x + y*y + z*z);
}


double operator% (const v3d& a, const v3d& b)
{
	double d;
	d = (a.x-b.x)*(a.x-b.x);
	d += (a.y-b.y)*(a.y-b.y);
	d += (a.z-b.z)*(a.z-b.z);
	return sqrt(d);
}


/***************************
 *
 *			m3x3d
 *
 * *************************/

m3x3d m3x3d::identity()
{
	m3x3d a;
	for(int i = 0; i < 3; ++i)
	{
		a.m[i*4] = 1;
	}
	return a;
}

m3x3d& m3x3d::invert()
{
	double d = determinant();

	if(fabs(d) > 0.0000001f )
	{
		m3x3d a(*this);
		(*this) *= 0;
		double s[4];
		for(int f = 0; f < 3; ++f)
		{
			for(int c = 0; c < 3; ++c)
			{
				int n = 0;
				for(int i = 0; i < 3; ++i)
				{
					if(i==f) continue;
					for(int j = 0; j < 3; ++j)
					{
						if(j==c) continue;
						s[n++] = a.m[3*i + j];
					}
				}
				m[c*3 + f] = ((f+c)&0x1) ? -(s[0]*s[3] - s[1]*s[2]) : (s[0]*s[3] - s[1]*s[2]);
			}
		}
		(*this) *= 1/d;
	}
	else
	{
		(*this) *= 0;
		return *this;
	}
	return *this;
}


m3x3d& m3x3d::transpose()
{
	double x;
	for(int f = 0; f < 3; ++f)
	{
		for(int c = 0; c < 3; ++c)
		{
			x = m[3*f + c];
			m[3*f + c] = m[3*c + f];
			m[3*c + f] = x;
		}
	}
	return *this;
}

double m3x3d::determinant() const
{
	return m[0]*m[4]*m[8] + m[1]*m[5]*m[6] + m[3]*m[7]*m[2] - (m[6]*m[4]*m[2] + m[3]*m[1]*m[8] + m[5]*m[7]*m[0]);
}


v3d operator* (v3d v, const m3x3d& m)
{
	v3d r;
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			r.v[i] += v.v[j] * m.m[i + 3*j];
		}
	}
	return r;
}


v3d operator* (const m3x3d& m, v3d v)
{
	v3d r;
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			r.v[i] += v.v[j] * m.m[3*i + j];
		}
	}
	return r;
}


};
