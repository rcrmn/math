

#ifndef __M4x4D_H__
#define __M4x4D_H__

#include <ostream>
#include "../conf.h"

namespace math
{

class v3d;

class m4x4d
{
	public:

		static m4x4d identity();

	public:
		math_float_t m[16];

		m4x4d() { for(int i = 0; i < 16; ++i) m[i] = 0; }

		m4x4d(math_float_t* d) { for(int i = 0; i < 16; ++i) m[i] = d[i]; }


		m4x4d(const m4x4d& b) { for(int i = 0; i < 16; ++i) m[i] = b.m[i]; }
		m4x4d& operator= (const m4x4d& b) { for(int i = 0; i < 16; ++i) m[i] = b.m[i]; return *this; }

		m4x4d& operator+= (const m4x4d& b) { for(int i = 0; i < 16; ++i) m[i] += b.m[i]; return *this; }
		m4x4d& operator-= (const m4x4d& b) { for(int i = 0; i < 16; ++i) m[i] -= b.m[i]; return *this; }

		m4x4d& operator*= (const m4x4d& b) 
		{ 
			m4x4d c(*this);
			for(int i = 0; i < 4; ++i) 
				for(int j = 0; j < 4; ++j)
				{
					m[4*i + j] = 0;
					for(int k = 0; k < 4; ++k)
						m[4*i + j] += c.m[4*i+k] * b.m[4*k + j];
				}
			return *this;
		}

		m4x4d& operator*= (math_float_t k) { for(int i = 0; i < 16; ++i) m[i] *= k; return *this; }
		m4x4d& operator/= (math_float_t k) { k = 1.0/k; (*this) *= k; return *this; }


		m4x4d& transpose();

};

inline m4x4d operator+ (m4x4d a, const m4x4d& b) { a += b; return a; }
inline m4x4d operator- (m4x4d a, const m4x4d& b) { a -= b; return a; }
inline m4x4d operator* (m4x4d a, const m4x4d& b) { a *= b; return a; }

inline m4x4d operator- (const m4x4d& a) { m4x4d b; b-=a; return b; }

inline m4x4d operator* (m4x4d a, math_float_t k) { a *= k; return a; }
inline m4x4d operator/ (m4x4d a, math_float_t k) { a /= k; return a; }


v3d operator* (v3d v, const m4x4d& m);
v3d operator* (const m4x4d& m, v3d v);


inline std::ostream& operator<< (std::ostream& out, const m4x4d& m) 
{ 
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			out << m.m[4*i + j] << "\t";
		}
		out << std::endl;
	}

	return out;
}

};


#endif


