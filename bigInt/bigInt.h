
#ifndef __BIG_INT_H__
#define __BIG_INT_H__

#include <vector>
#include <string>

extern "C" {
#include <stdint.h>
}

namespace math {

	using namespace std;

	class BigInt
	{
		public:
			BigInt ();
			BigInt (int32_t i);
			BigInt (const string& i);
			BigInt (const BigInt& i);

			const BigInt operator- () const;
			BigInt& operator= (const BigInt& a);
			BigInt& operator+= (const BigInt& a);
			BigInt& operator-= (BigInt a);
			BigInt& operator*= (const BigInt& a);
			BigInt& operator/= (const BigInt& a);

			const string toStr() const;

		private:
			void normalize();

		private:
			typedef uint8_t uchr;

			vector<uchr> m_number;
			bool m_sign;

	};

};

inline math::BigInt operator+ (math::BigInt a, const math::BigInt& b)
{
	a += b;
	return a;
}

inline math::BigInt operator- (math::BigInt a, const math::BigInt& b)
{
	a -= b;
	return a;
}

inline math::BigInt operator* (math::BigInt a, const math::BigInt& b)
{
	a *= b;
	return a;
}

inline math::BigInt operator/ (math::BigInt a, const math::BigInt& b)
{
	a /= b;
	return a;
}


#endif // __BIG_INT_H__

