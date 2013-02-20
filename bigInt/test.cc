

#include "bigInt.h"

#include <iostream>

int main(int argc, char** argv)
{
	using namespace math;

	BigInt a(35);

	BigInt b(-13);

	BigInt c = a - b;

	cout << a.toStr() << " - " << b.toStr() << " = " << c.toStr() << endl;

	return 0;
}

