#ifndef __V2D_H__
#define __V2D_H__

#include <ostream>
#include "../conf.h"

namespace math
{

class v2d
{
	public:
		union {
			struct {
				math_float_t x, y;
			};
			math_float_t v[2];
		};

		v2d() : x(0), y(0) {}
		v2d(math_float_t _x, math_float_t _y) : x(_x), y(_y) {}

		v2d(const v2d& b) : x(b.x), y(b.y) {}
		v2d& operator= (const v2d& b) { x = b.x; y = b.y; return *this; }

		v2d& operator+= (const v2d& b) { x += b.x; y += b.y; return *this; }
		v2d& operator-= (const v2d& b) { x -= b.x; y -= b.y; return *this; }

		v2d& operator*= (math_float_t d) { x*=d; y*=d; return *this; }
		v2d& operator/= (math_float_t d) { d = 1/d; return (*this)*=d; }

		v2d& normalize();

		math_float_t length() const;
		math_float_t sqlength() const;
};

inline v2d operator+ (v2d a, const v2d& b) { a += b; return a; }
inline v2d operator- (v2d a, const v2d& b) { a -= b; return a; }

inline v2d operator- (v2d a) { a.x = -a.x; a.y = -a.y; return a; }

inline math_float_t operator* (v2d a, const v2d& b) { return a.x*b.x + a.y*b.y; }

inline v2d operator* (v2d v, math_float_t d) { return v*=d; }
inline v2d operator* (math_float_t d, v2d v) { return v*=d; }
inline v2d operator/ (v2d v, math_float_t d) { return v/=d; }
inline v2d operator/ (math_float_t d, v2d v) { return v/=d; }

math_float_t operator% (const v2d& a, const v2d& b);
inline math_float_t distance (const v2d& a, const v2d& b) { return a%b; }


inline std::ostream& operator<< (std::ostream& out, const v2d& q) { out << "(" << q.x << ", " << q.y << ")"; return out; }

}

#endif // V2D_H
