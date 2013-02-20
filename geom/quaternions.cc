#include <cmath>

#include "quaternion.h"
#include "dualquat.h"

#include "m4x4d.h"

using namespace std;

using namespace math;

/*****************************
 *
 *		  quaternion
 *
 * ***************************/

double quaternion::norm() const
{
	return sqrt(w*w + x*x + y*y + z*z);
}

void quaternion::normalize()
{
	double n = norm();

	if(fabs(n) < 0.000001)
	{
		w = 1;
		x = y = z = 0;
	}
	else
	{
		n = 1/n;
		w *= n;
		x *= n;
		y *= n;
		z *= n;
	}
}


v3d quaternion::rotateVector(const v3d& v) const
{
	quaternion dv(v);
	quaternion inv(*this);
	inv.invert();

	dv = ((*this)* dv)*inv;

	return v3d(dv.x, dv.y, dv.z);
}

void quaternion::invert()
{
	(*this) = ~(*this);
	(*this) /= (w*w + x*x + y*y + z*z);
}


quaternion quaternion::fromAngleAxis(double a, double x, double y, double z)
{
	a *= 0.5;
	double c = cos(a);
	double s = sin(a);
	v3d v(x, y, z);
	v.normalize();
	v *= s;
	return quaternion(c, v.x, v.y, v.z);
}


/*****************************
 *
 *		dual quaternion
 *
 * ***************************/

void dualquat::normalize()
{
	const double n = r.norm();

	if(n == 0) return;

	r *= 1/n;
	d *= 1/n;

	quaternion real(r);

	real *= -dot(r, d);
	d += real;
}


void dualquat::invert()
{
	double n = r.norm();
	double rdd = dot(r, d);

	r = ~r;
	d = ~d;

	r *= n;
	d *= n - 2*rdd;
}


v3d dualquat::transform(const v3d& p) const
{
	dualquat inv(*this);
	inv.invert();

	dualquat dpos(quaternion(1, 0, 0, 0), quaternion(p));
	dpos = ((*this) * dpos) * inv;

	return v3d(dpos.d.x, dpos.d.y, dpos.d.z);
}

v3d dualquat::rotateVector(const v3d& v) const
{
	return r.rotateVector(v);
}


dualquat dualquat::translatedRotation(const v3d& translation, const v3d& rotationAxis, double angle)
{
	dualquat ret;
	ret.r = quaternion::fromAngleAxis(angle, rotationAxis);
	ret.d = quaternion(0, translation.x/2, translation.y/2, translation.z/2);
	return ret;
}


m4x4d dualquat::getMatrix() const
{
	m4x4d ret;
	double k, l;

	ret.m[0] = ret.m[5] = ret.m[10] = r.w*r.w;
	k = r.x*r.x;
	l = r.y*r.y;
	ret.m[10] -= k+l;
	
	k -= l;
	ret.m[0] += k;
	ret.m[5] -= k;

	l = r.z*r.z;
	ret.m[0] -= l;
	ret.m[5] -= l;
	ret.m[10] += l;

	ret.m[1] = ret.m[4] = r.x*r.y;
	k = r.w*r.z;
	ret.m[1] -= k;
	ret.m[1] *= 2;
	ret.m[4] += k;
	ret.m[4] *= 2;

	ret.m[2] = ret.m[8] = r.x*r.z;
	k = r.w*r.y;
	ret.m[2] += k;
	ret.m[2] *= 2;
	ret.m[8] -= k;
	ret.m[8] *= 2;

	ret.m[6] = ret.m[9] = r.z*r.y;
	k = r.w*r.x;
	ret.m[6] -= k;
	ret.m[6] *= 2;
	ret.m[9] += k;
	ret.m[9] *= 2;

	ret.m[3] = 2*d.x;
	ret.m[7] = 2*d.y;
	ret.m[11] = 2*d.z;

	ret.m[12] = 0;
	ret.m[13] = 0;
	ret.m[14] = 0;
	ret.m[15] = 1;

	return ret;
}


