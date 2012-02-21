#include "Vector3Test.hpp"

#include "assert.hpp"
#include <Math/Vector3.hpp>

void testVector3()
{
	cout << "Testing Vector3 class..." << endl;

	//Constructor test
	Vector3 v1;
	assertEquals(__LINE__, 0.0f, 0.0f, 0.0f, v1);	

	v1 = Vector3(0.5f, 0.3f, 1.0f);
	assertEquals(__LINE__, 0.5f, 0.3f, 1.0f, v1);	

	float values[] = {1.0f, 0.5f, 0.3f};
	v1 = Vector3(values);
	assertEquals(__LINE__, 1.0f, 0.5f, 0.3f, v1);

	Vector3 v2(v1);
	assertEquals(__LINE__, 1.0f, 0.5f, 0.3f, v2);

	//Setters test
	v1.set(10.0f, 20.0f, 30.0f);
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v1);
	
	v1.set(values);
	assertEquals(__LINE__, 1.0f, 0.5f, 0.3f, v1);

	//Operators
	//Operator []
	v1[0] = 10.0f;
	v1[1] = 20.0f;
	v1[2] = 30.0f;
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v1);
	assertEquals(__LINE__,10.0f, v1[0]);
	assertEquals(__LINE__,20.0f, v1[1]);
	assertEquals(__LINE__,30.0f, v1[2]);

	const Vector3 &constV1 = v1;
	assertEquals(__LINE__,10.0f, constV1[0]);
	assertEquals(__LINE__,20.0f, constV1[1]);
	assertEquals(__LINE__,30.0f, constV1[2]);
	
	//Operator +=
	v1 = Vector3(10.0f, 20.0f, 30.0f);
	v2 = Vector3(1.0f, 2.0f, 3.0f);
	v1 += v2;
	assertEquals(__LINE__, 11.0f, 22.0f, 33.0f, v1);

	//Operator -=
	v1 = Vector3(10.0f, 20.0f, 30.0f);
	v2 = Vector3(1.0f, 2.0f, 3.0f);
	v1 -= v2;
	assertEquals(__LINE__, 9.0f, 18.0f, 27.0f, v1);

	//Operator *= with scalar
	v1 = Vector3(1.0f, 2.0f, 3.0f);
	v1 *= 10;
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v1);

	//Operator *= with vector
	v1 = Vector3(100.0f, 100.0f, 100.0f);
	v2 = Vector3(0.1f, 0.2f, 0.3f);
	v1 *= v2;
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v1);

	//Operator /=
	v1 = Vector3(100.0f, 200.0f, 300.0f);
	v1 /= 10;
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v1);

	//Operator - (unary)
	v1 = Vector3(-10.0f, -20.0f, -30.0f);
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, -v1);

	//Operator +
	v1 = Vector3(10.0f, 20.0f, 30.0f);
	v2 = Vector3(1.0f, 2.0f, 3.0f);
	Vector3 v3 = v1 + v2;
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v1);
	assertEquals(__LINE__, 11.0f, 22.0f, 33.0f, v3);

	//Operator -
	v1 = Vector3(10.0f, 20.0f, 30.0f);
	v2 = Vector3(1.0f, 2.0f, 3.0f);
	v3 = v1 - v2;
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v1);
	assertEquals(__LINE__, 9.0f, 18.0f, 27.0f, v3);

	//Operator * with scalar
	v1 = Vector3(1.0f, 2.0f, 3.0f);
	v2 = v1 * 10;
	assertEquals(__LINE__, 1.0f, 2.0f, 3.0f, v1);
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v2);

	//Operator * with vector
	v1 = Vector3(100.0f, 100.0f, 100.0f);
	v2 = Vector3(0.1f, 0.2f, 0.3f);
	v3 = v1 * v2;
	assertEquals(__LINE__, 100.0f, 100.0f, 100.0f, v1);
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v3);

	//Operator /
	v1 = Vector3(100.0f, 200.0f, 300.0f);
	v2 = v1 / 10;
	assertEquals(__LINE__, 100.0f, 200.0f, 300.0f, v1);
	assertEquals(__LINE__, 10.0f, 20.0f, 30.0f, v2);

	//Operator ==
	v1 = Vector3(10.0f, 20.f, 30.0f);
	v2 = Vector3(v1);
	assertTrue(__LINE__, v1 == v2);
	v2.x = 1.0f;
	assertTrue(__LINE__, !(v1 == v2));

	//Operator !=
	v1 = Vector3(10.0f, 20.f, 30.0f);
	v2 = Vector3(v1);
	assertTrue(__LINE__, !(v1 != v2));
	v2.x = 1.0f;
	assertTrue(__LINE__, v1 != v2);

	//Methods
	//Size
	v1 = Vector3(5, 5, 7);
	assertEquals(__LINE__, 99, v1.sizeSqr());
	assertEquals(__LINE__, sqrt(99.0f), v1.size());
	
	//Resize
	v1.resize(100);
	assertEquals(__LINE__, 100.0f, v1.size());	

	//Cross product
	v1 = Vector3(3, -3, 1);
	v2 = Vector3(4, 9, 2);
	v1.cross(v2);
	assertEquals(__LINE__, -15.0f, -2.0f, 39.0f, v1);

	//Dot product
	v1 = Vector3(1, 2, 3);
	v2 = Vector3(30, 20, 10);
	assertEquals(__LINE__, 100, v1.dot(v2));


}