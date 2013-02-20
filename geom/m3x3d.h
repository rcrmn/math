

#ifndef __M3x3D_H__
#define __M3x3D_H__

#include <ostream>

namespace math
{

class m3x3d
{
	public:

		static m3x3d identity();

	public:
		double m[9];

		m3x3d() { for(int i = 0; i < 9; ++i) m[i] = 0; };

		m3x3d(const m3x3d& b) { for(int i = 0; i < 9; ++i) m[i] = b.m[i]; }
		m3x3d& operator= (const m3x3d& b) { for(int i = 0; i < 9; ++i) m[i] = b.m[i]; return *this; }

		m3x3d& operator+= (const m3x3d& b) { for(int i = 0; i < 9; ++i) m[i] += b.m[i]; return *this; }
		m3x3d& operator-= (const m3x3d& b) { for(int i = 0; i < 9; ++i) m[i] -= b.m[i]; return *this; }

		m3x3d& operator*= (const m3x3d& b) 
		{ 
			m3x3d c(*this);
			for(int i = 0; i < 3; ++i) 
				for(int j = 0; j < 3; ++j)
				{
					m[3*i + j] = 0;
					for(int k = 0; k < 3; ++k)
						m[3*i + j] += c.m[3*i+k] * b.m[3*k + j];
				}
			return *this;
		}

		m3x3d& operator*= (double k) { for(int i = 0; i < 9; ++i) m[i] *= k; return *this; }
		m3x3d& operator/= (double k) { k = 1.0/k; (*this) *= k; return *this; }

		m3x3d& invert();
		m3x3d& transpose();
		double determinant() const;


};

inline m3x3d operator+ (m3x3d a, const m3x3d& b) { a += b; return a; }
inline m3x3d operator- (m3x3d a, const m3x3d& b) { a -= b; return a; }
inline m3x3d operator* (m3x3d a, const m3x3d& b) { a *= b; return a; }

inline m3x3d operator- (const m3x3d& a) { m3x3d b; b-=a; return b; }

inline m3x3d operator* (m3x3d a, double k) { a *= k; return a; }
inline m3x3d operator/ (m3x3d a, double k) { a /= k; return a; }


v3d operator* (v3d v, const m3x3d& m);
v3d operator* (const m3x3d& m, v3d v);


inline std::ostream& operator<< (std::ostream& out, const m3x3d& m) 
{ 
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			out << m.m[3*i + j] << "\t";
		}
		out << std::endl;
	}

	return out;
}

};


#endif

