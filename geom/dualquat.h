
#ifndef __DUALQUAT_H__
#define __DUALQUAT_H__

#include "quaternion.h"

namespace math
{

class v3d;
class m4x4d;

class dualquat
{
	public:

		static dualquat translatedRotation(const v3d& translation, const v3d& rotationAxis, double angle);

	public:
		quaternion r, d;

		dualquat () : r(), d() {}
		dualquat (quaternion _r, quaternion _d) : r(_r), d(_d) {}
		dualquat (const dualquat& b) : r(b.r), d(b.d) {}
		dualquat& operator= (const dualquat& b) { r = b.r; d = b.d; return *this; }

		dualquat& operator+= (const dualquat& b) { r += b.r; d += b.d; return *this; }
		dualquat& operator-= (const dualquat& b) { r -= b.r; d -= b.d; return *this; }

		dualquat& operator*= (const dualquat& b) 
		{ 
			dualquat a(*this);
			r = a.r * b.r;
			d = (a.r * b.d) + (a.d * b.r);
			return *this;
		}

		dualquat operator~ () { dualquat a; a.r = ~r; a.d = ~d; return a; }

		void normalize();

		void invert();

		v3d transform(const v3d& p) const;
		v3d rotateVector(const v3d& v) const;

		m4x4d getMatrix() const;
};

inline dualquat operator+ (dualquat a, const dualquat& b) { a+=b; return a; }
inline dualquat operator- (dualquat a, const dualquat& b) { a-=b; return a; }
inline dualquat operator* (dualquat a, const dualquat& b) { a*=b; return a; }

};

#endif


