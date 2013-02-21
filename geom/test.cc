#include "v3d.h"
#include "m3x3d.h"
//#include "m4x4d.h"
#include "quaternion.h"
#include "dualquat.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	using namespace math;

	cout << "Testing v3d" << endl;
	v3d a(0,1,2), b(1,0,-1);

	v3d c;

	cout << a << endl << b << endl;
	
	c = a+b;
	cout << c << endl;

	c = a - b;
	cout << c << endl;

	c = a ^ b;
	cout << c << endl;

	cout << (a*b) << endl;

	cout << c.length() << endl;

	c.normalize();
	cout << c << endl;

	cout << c.length() << endl;
	
	cout << "Testing m3x3d" << endl;

	m3x3d m1 = m3x3d::identity();
	m1.m[0] = 2;
	
	m3x3d m2 = m3x3d::identity();
	m2.m[1] = 3;

	m3x3d m3 = m1 * m2;

	cout << m1 << endl << m2 << endl << m3 << endl;

	cout << (m1 * a) << endl;
	cout << (m2 * a) << endl;
	cout << (m3 * a) << endl;

	cout << m1.determinant() << endl;

	m3x3d inv(m3);
	inv.invert();

	cout << inv << endl;

	cout << ((m3*inv)*a) << endl;


	cout << "Testing quaternion" << endl;

	quaternion q1(0, 0, 0, 1), q2(1, 0, 0, 0), q3(0, 1, 0, 0);

	cout << q1 << q2 << q3 << endl;

	cout << (q1*q1) << endl;
	
	cout << q3.rotateVector(a) << endl;

	{
#define k 0.5

		v3d a(1, 0, 0);

		cout << "---------" << endl;

		cout << a << endl;

		dualquat dq = dualquat::translate(v3d(1, 0, 0));

		cout << "T: " << dq.transform(a) << endl;

		dq = dualquat::rotate(v3d(0, 0, 1), k*3.141592);

		cout << "R: " << dq.transform(a) << endl;

		dq = dualquat::translateThenRotate(v3d(1, 0, 0), v3d(0, 0, 1), k*3.141592);

		cout << "T+R: " << dq.transform(a) << endl;

		dq = dualquat::rotateThenTranslate(v3d(1, 0, 0), v3d(0, 0, 1), k*3.141592);

		cout << "R+T: " << dq.transform(a) << endl;

		dq = dualquat::rotateAboutPoint(v3d(-1, 0, 0), v3d(0, 0, 1), k*3.141592);

		cout << "R(c): " << dq.transform(a) << endl;
	}

	return 0;
}

