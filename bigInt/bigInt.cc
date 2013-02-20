
#include "bigInt.h"
#include <vector>
#include <string>
#include <cmath>

#include <iostream>

extern "C" {
#include <stdint.h>
}

using namespace math;

using namespace std;



BigInt::BigInt()
	: m_sign(false)
{
	m_number.push_back(0);
}

BigInt::BigInt(int32_t i)
	: m_sign(false)
{
	if(i<0)
	{
		m_sign = true;
		i = -i;
	}

	m_number.push_back((uchr)(i&0x000000FF));
	m_number.push_back((uchr)((i&0x0000FF00)>>8));
	m_number.push_back((uchr)((i&0x00FF0000)>>16));
	m_number.push_back((uchr)((i&0xFF000000)>>24));

	normalize();
}

BigInt::BigInt(const string& s)
	: m_sign(false)
{

}

BigInt::BigInt(const BigInt& i)
	: m_sign(i.m_sign)
	, m_number(i.m_number)
{
	normalize();
}

void BigInt::normalize()
{
	// Eliminem els zeros del principi
	for(int i = m_number.size()-1; i > 0; --i)
	{
		if(m_number[i] != 0)
			break;

		m_number.pop_back();
	}
}

const string BigInt::toStr() const
{
	string r = "";

	BigInt a = *this;

	a.normalize();

	if(a.m_number.size()==0)
	{
		return "0";
	}

	bool totZeros;

	do {
		uint16_t mod = 0;

		totZeros = true;

		if(a.m_number[0] != 0) totZeros = false;

		for(int i = a.m_number.size()-1; i >= 0; --i)
		{
			if(totZeros && a.m_number[i] == 0)
			{
				continue;
			}
			totZeros = false;

			mod <<= 8;
			mod += a.m_number[i];

			a.m_number[i] = mod / 10;

			mod = mod % 10;
		}

		if(r.size() == 0 || !totZeros)
		{
			r += ((char) mod) + '0';
		}


	} while(!totZeros);

	if(a.m_sign)
		r += '-';

	string rr = "";

	for(int i = r.size()-1; i >= 0; --i)
	{
		rr += r[i];
	}

	return rr;
}


const BigInt BigInt::operator- () const
{
	BigInt r(*this);
	r.m_sign = !r.m_sign;
	return r;
}


BigInt& BigInt::operator= (const BigInt& a)
{
	m_sign = a.m_sign;
	m_number.clear();
	m_number = a.m_number;
}

BigInt& BigInt::operator+= (const BigInt& a)
{
	BigInt r;

	if(a.m_sign != m_sign)
	{
		if(m_sign) // *this is negative
		{
			BigInt b = *this;
			b.m_sign = false;
			*this = a - b;
		}
		else // a is negative
		{
			BigInt b = a;
			b.m_sign = false;
			*this -= b;
		}
		return *this;
	}
	else
	{
		r.m_sign = m_sign;
	}

	uint16_t tmp = 0;

	size_t n = min(m_number.size(), a.m_number.size());

	r.m_number.clear();

	for(size_t j = 0; j < n; ++j)
	{
		tmp += ((uint16_t) m_number[j]) + ((uint16_t)a.m_number[j]);
		r.m_number.push_back((uchr) (tmp & 0xFF));
		tmp = tmp >> 8;
	}

	if(m_number.size() > a.m_number.size())
	{
		for(size_t j = a.m_number.size(); j < m_number.size(); ++j )
		{
			tmp += m_number[j];
			r.m_number.push_back((uchr) (tmp&0xFF));
			tmp = tmp >> 8;
		}
	}
	else if(m_number.size() < a.m_number.size())
	{
		for(size_t j = m_number.size(); j < a.m_number.size(); ++j )
		{
			tmp += a.m_number[j];
			r.m_number.push_back((uchr) (tmp&0xFF));
			tmp = tmp >> 8;
		}
	}


	while(tmp > 0)
	{
		r.m_number.push_back((uchr) (tmp&0xFF));
		tmp = tmp >> 8;
	}

	r.normalize();

	*this = r;
	return *this;
}

BigInt& BigInt::operator-= (BigInt a)
{

	if(a.m_sign != m_sign)
	{
		if(a.m_sign)
		{
			a.m_sign = false;
			*this += a;
		}
		else
		{
			a.m_sign = true;
			*this += a;
		}
		return *this;
	}

	normalize();
	a.normalize();

#define SIGNEDCHAR 0x80
	// Igualem la llargada dels numeros
	if(a.m_number.size() < m_number.size())
	{
		a.m_number.resize(m_number.size(), 0);
	}
	a.m_number.push_back(SIGNEDCHAR);
#undef SIGNEDCHAR

	bool signe_original = m_sign;

	// Fem complement a 2 del segon numero
	for(int i = 0; i < a.m_number.size(); ++i)
	{
		a.m_number[i] ^= 0xFF;
	}
	a.m_sign = false;
	a += 1;


	a.m_sign = m_sign;

	// Sumem els dos nombres
	a += *this;

	
	bool sign = (a.m_number.back() & 0x40) > 0;

	a.m_number.back() &= 0x7F;

	if(sign)
	{
		// Canviem el signe i el carry
		a.m_number.back() |= 0xC0;
		for(int i = 0; i < a.m_number.size(); ++i)
		{
			a.m_number[i] ^= 0xFF;
		}

		a.m_sign = false;
		a += 1;

		a.m_sign = !signe_original;
	}
	else
	{
		a.m_sign = signe_original;
	}

	a.normalize();

	*this = a;
	return *this;
}

BigInt& BigInt::operator*= (const BigInt& a)
{
	BigInt r;

	*this = r;
	return *this;
}

BigInt& BigInt::operator/= (const BigInt& a)
{
	BigInt r;

	*this = r;
	return *this;
}



