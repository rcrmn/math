

#ifndef __V3D_H__
#define __V3D_H__

#include <ostream>
#include "../conf.h"

namespace math
{

class v3d
{

	public:
		union {
			struct {
				math_float_t x, y, z;
			};
			math_float_t v[3];
		};

		v3d() : x(0), y(0), z(0) {}
		v3d(math_float_t _x, math_float_t _y, math_float_t _z) : x(_x), y(_y), z(_z) {}

		v3d(const v3d& b) : x(b.x), y(b.y), z(b.z) {}
		v3d& operator= (const v3d& b) { x = b.x; y = b.y; z = b.z; return *this; }

		v3d& operator+= (const v3d& b) { x += b.x; y += b.y; z += b.z; return *this; }
		v3d& operator-= (const v3d& b) { x -= b.x; y -= b.y; z -= b.z; return *this; }

		v3d& operator^= (const v3d& b) { v3d a(*this); x = a.y*b.z - a.z*b.y; y = a.z*b.x - a.x*b.z; z = a.x*b.y - a.y*b.x; return *this; }

		v3d& operator*= (math_float_t d) { x*=d; y*=d; z*=d; return *this; }
		v3d& operator/= (math_float_t d) { d = 1/d; return (*this)*=d; }

		v3d& normalize();

		math_float_t length() const;
		math_float_t sqlength() const;
};

inline v3d operator+ (v3d a, const v3d& b) { a += b; return a; }
inline v3d operator- (v3d a, const v3d& b) { a -= b; return a; }

inline v3d operator- (v3d a) { a.x = -a.x; a.y = -a.y; a.z = -a.z; return a; }

inline math_float_t operator* (v3d a, const v3d& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
inline v3d operator^ (v3d a, const v3d& b) { a ^= b; return a; }

inline v3d operator* (v3d v, math_float_t d) { return v*=d; }
inline v3d operator* (math_float_t d, v3d v) { return v*=d; }
inline v3d operator/ (v3d v, math_float_t d) { return v/=d; }
inline v3d operator/ (math_float_t d, v3d v) { return v/=d; }

math_float_t operator% (const v3d& a, const v3d& b);
inline math_float_t distance (const v3d& a, const v3d& b) { return a%b; }


inline std::ostream& operator<< (std::ostream& out, const v3d& q) { out << "(" << q.x << ", " << q.y << ", " << q.z << ")"; return out; }

};


#endif

