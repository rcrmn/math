
#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include <ostream>
#include "../conf.h"

#include "v3d.h"

namespace math
{

class quaternion
{
	public:

		static quaternion fromAngleAxis(math_float_t a, math_float_t x, math_float_t y, math_float_t z);
		static inline quaternion fromAngleAxis(math_float_t a, const v3d& axis) { return fromAngleAxis(a, axis.x, axis.y, axis.z); }

	public:
		union {
			struct{
				math_float_t w, x, y, z;
			};
			math_float_t q[4];
		};

		quaternion () : w(0), x(0), y(0), z(0) {}
		quaternion (math_float_t _w, math_float_t _x, math_float_t _y, math_float_t _z) : w(_w), x(_x), y(_y), z(_z) {}
		quaternion (v3d pos) : w(0), x(pos.x), y(pos.y), z(pos.z) {}

		quaternion (const quaternion& b) : w(b.w), x(b.x), y(b.y), z(b.z) {}
		quaternion& operator= (const quaternion& b) { w = b.w; x = b.x; y = b.y; z = b.z; return *this; }

		quaternion& operator+= (const quaternion& b) { w += b.w; x += b.x; y += b.y; z += b.z; return *this; }
		quaternion& operator-= (const quaternion& b) { w -= b.w; x -= b.x; y -= b.y; z -= b.z; return *this; }

		quaternion& operator*= (const quaternion& b) 
		{ 
			quaternion a; 
			a.w = w*b.w - (x*b.x + y*b.y + z*b.z); 
			a.x = (w*b.x + x*b.w) + (y*b.z - z*b.y); 
			a.y = (w*b.y + y*b.w) + (z*b.x - x*b.z); 
			a.z = (w*b.z + z*b.w) + (x*b.y - y*b.x);
			*this = a;
			return *this; 
		}

		quaternion& operator*= (math_float_t d) { w *= d; x *= d; y *= d; z *= d; return *this; }
		quaternion& operator/= (math_float_t d) { (*this) *= 1/d; return *this; }

		quaternion operator~ () const { quaternion a(*this); a.x = -a.x; a.y = -a.y; a.z = -a.z; return a; }
		void conjugate() { (*this) = ~(*this); }

		math_float_t norm() const;

		void normalize();

		void invert();

		v3d rotateVector(const v3d& v) const;


};

inline quaternion operator+ (quaternion a, const quaternion& b) { a+=b; return a; }
inline quaternion operator- (quaternion a, const quaternion& b) { a-=b; return a; }
inline quaternion operator- (const quaternion& a) { return quaternion(-a.w, -a.x, -a.y, -a.z); }
inline quaternion operator* (quaternion a, const quaternion& b) { a*=b; return a; }

inline math_float_t dot(const quaternion& a, const quaternion& b) { return a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z; }


inline std::ostream& operator<< (std::ostream& out, const quaternion& q) { out << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")"; return out; }


};

#endif

