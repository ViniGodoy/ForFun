#include "Vector2Test.hpp"

#include "assert.hpp"
#include <Math/Vector2.hpp>

void testVector2()
{
	cout << "Testing Vector2 class..." << endl;

	//Constructor test
	Vector2 v1;
	assertEquals(__LINE__, 0.0f, 0.0f, v1);	

	v1 = Vector2(0.5f, 0.3f);
	assertEquals(__LINE__, 0.5f, 0.3f, v1);	

	float values[] = {0.3f, 0.5f};
	v1 = Vector2(values);
	assertEquals(__LINE__, 0.3f, 0.5f, v1);		
	Vector2 v2(v1);
	assertEquals(__LINE__, 0.3f, 0.5f, v2);

	
	v1 = Vector2::newBySizeAngle(5, toRadians(30.0f));
    assertEquals(__LINE__, 5.0f, v1.size());
    assertEquals(__LINE__, toRadians(30.0f), v1.angle());

	//Guarantee that all functions are counter-clockwise
	assertEquals(__LINE__, toRadians(90.0f), Vector2(0,1).angle());
	assertEquals(__LINE__, toRadians(0.0f), Vector2(1,0).angle());
	assertEquals(__LINE__, toRadians(90.0f), Vector2(1,0).rotate(toRadians(90)).angle());
	assertEquals(__LINE__, toRadians(90.0f), perp(Vector2(1,0)).angle());
	
	float xy[2] = {0.5f, 0.3f};
	v1 = Vector2(xy);
	assertEquals(__LINE__, 0.5f, 0.3f, v1);	

	//Getters and setters test
	v1.set(0.3f, 0.5f);
	assertEquals(__LINE__, 0.3f, 0.5f, v1);		

	v1.set(xy);
	assertEquals(__LINE__, 0.5f, 0.3f, v1);	

	v1.set(Vector2(0.3f, 0.5f));
	assertEquals(__LINE__, 0.3f, 0.5f, v1);		

	v1.set(0.3f, 0.5f);
	assertEquals(__LINE__, 0.3f, v1[0]);
	assertEquals(__LINE__, 0.5f, v1[1]);

	//Vector2 functions
	v1.set(3.0f, 4.0f);
	assertEquals(__LINE__, 25.0f, v1.sizeSqr());
	assertEquals(__LINE__, 5.0f, v1.size());
	
	v1.set(3.0f, 4.0f);
	v1.resize(10.0f);
	assertEquals(__LINE__, 100.0f, v1.sizeSqr());
	assertEquals(__LINE__, 6.0f, 8.0, v1);		

	v1.set(0.0f, 0.0f);
	v1.resize(10);
	assertEquals(__LINE__, 0.0f, v1.sizeSqr());

	v1.set(0.0f, 0.0f);
	assertTrue(__LINE__, v1.isZero());

	v1.set(1.0f, 1.0f);
	assertTrue(__LINE__, !v1.isZero());

	v1 = Vector2::newBySizeAngle(1, toRadians(30.0f));
	assertTrue(__LINE__, v1.isUnit());
	
	v1.set(5.0f, 0.0f);
	assertTrue(__LINE__, !v1.isUnit());

	v1 = Vector2::newBySizeAngle(2, toRadians(26));
	assertEquals(__LINE__, toRadians(26), v1.angle());

	v1 = Vector2(5.0f, 0.0f);
	v1.rotate(0.5236f);
	assertEquals(__LINE__, 0.5236f, v1.angle());
	assertEquals(__LINE__, 5.0f, v1.size());

	v1 = Vector2(5.0f, 5.0f);
	float angle = v1.angle();
	v1.normalize();
	assertTrue(__LINE__, v1.isUnit());
	assertEquals(__LINE__, angle, v1.angle());

	v1 = Vector2::newBySizeAngle(3, toRadians(10));
	v2 = Vector2(1,0).rotate(toRadians(40));
	assertEquals(__LINE__, toRadians(30), v2.relativeAngleBetween(v1));

	v1 = Vector2::newBySizeAngle(1, toRadians(10));
	v2 = Vector2::newBySizeAngle(1, toRadians(40));

    float dot = v1.dot(v2);
    assertEquals(__LINE__, cosf(toRadians(30.0f)), dot);

	//Operators
	v1.set(5.0f, 10.0f);
	v2.set(0,0);
	v2 = v1;
	assertEquals(__LINE__, 5.0f, 10.0f, v1);
	assertEquals(__LINE__, 5.0f, 10.0f, v2);

	v1.set(5.0f, 10.0f);
	v1 += Vector2(1, -1);
	assertEquals(__LINE__, 6.0f, 9.0f, v1);

	v1.set(5.0f, 10.0f);
	v2 = v1 + Vector2(1, -1);
	assertEquals(__LINE__, 5.0f, 10.0f, v1);
	assertEquals(__LINE__, 6.0f, 9.0f, v2);


	v1.set(5.0f, 10.0f);
	v1 -= Vector2(1, -1);
	assertEquals(__LINE__, 4.0f, 11.0f, v1);

	v1.set(5.0f, 10.0f);
	v2 = v1 - Vector2(1, -1);
	assertEquals(__LINE__, 5.0f, 10.0f, v1);
	assertEquals(__LINE__, 4.0f, 11.0f, v2);


	v1.set(5.0f, 10.0f);
	v1 *= 2;
	assertEquals(__LINE__, 10.0f, 20.0f, v1);

	v1.set(5.0f, 10.0f);
	v2 = v1 * 2;
	assertEquals(__LINE__, 5.0f, 10.0f, v1);
	assertEquals(__LINE__, 10.0f, 20.0f, v2);

	v1.set(10.0f, 5.0f);
	v2 = 2 * v1;
	assertEquals(__LINE__, 10.0f, 5.0f, v1);
	assertEquals(__LINE__, 20.0f, 10.0f, v2);


	v1.set(5.0f, 10.0f);
	v1 /= 2;
	assertEquals(__LINE__, 2.5f, 5.0f, v1);

	v1.set(5.0f, 10.0f);
	v2 = v1 / 2;
	assertEquals(__LINE__, 5.0f, 10.0f, v1);
	assertEquals(__LINE__, 2.5f, 5.0f, v2);


	v1.set(5.0f, 10.0f);
	v2 = -v1;
	assertEquals(__LINE__, 5.0f, 10.0f, v1);
	assertEquals(__LINE__, -5.0f, -10.0f, v2);


	assertTrue(__LINE__, Vector2(1,5) == Vector2(1,5));
	assertTrue(__LINE__, !(Vector2(1,5) == Vector2(5,5)));
	assertTrue(__LINE__, !(Vector2(1,5) == Vector2(1,1)));

	assertTrue(__LINE__, Vector2(1,5) != Vector2(5,5));
	assertTrue(__LINE__, Vector2(1,5) != Vector2(1,1));
	assertTrue(__LINE__, !(Vector2(1,5) != Vector2(1,5)));

	//Auxiliary functions
	v1.set(10.0f, 10.0f);
	v2.set(7.0f, 6.0f);
	assertEquals(__LINE__, 25, distanceSqr(v1, v2));
	assertEquals(__LINE__, 5, fun::math::distance(v1, v2));


	v1.set(5.0f, 4.0f);
	v2 = perp(v1);
	assertEquals(__LINE__, 5.0f, 4.0f, v1);
	assertEquals(__LINE__, -4.0f, 5.0f, v2);


	v1 = Vector2(5.0f, 0.0f);
	v2 = rotate(v1, 0.5236f);
	assertEquals(__LINE__, 5.0f, 0.0f, v1);
	assertEquals(__LINE__, 0.5236f, v2.angle());
	assertEquals(__LINE__, 5.0f, v2.size());


	v1.set(3.0f, 4.0f);
	v2 = resize(v1, 10.0f);
	assertEquals(__LINE__, 3.0f, 4.0f, v1);
	assertEquals(__LINE__, 100.0f, v2.sizeSqr());
	assertEquals(__LINE__, 6.0f, 8.0, v2);		

	v1.set(0.0f, 0.0f);
	v2 = resize(v1, 10);
	assertEquals(__LINE__, 0.0f, v1.sizeSqr());
	assertEquals(__LINE__, 0.0f, v2.sizeSqr());


	v1.set(1,1).resize(10);	
	v2 = truncate(v1, 5);
	assertEquals(__LINE__, 10.0f, v1.size());
	assertEquals(__LINE__, 5.0f, v2.size());
	assertEquals(__LINE__, v1.angle(), v2.angle());

	v1.set(1,1).resize(10);		
	v2 = truncate(v1, 15);
	assertTrue(__LINE__, v1 == v2);


	v1 = Vector2(5.0f, 5.0f);
	v2 = normalize(v1);
	assertTrue(__LINE__, !v1.isUnit());
	assertTrue(__LINE__, v2.isUnit());
	assertEquals(__LINE__, v1.angle(), v2.angle());


	v1.set(1.0f, -1.0f);
	v2 = reflect(v1, Vector2(0,1));
	assertEquals(__LINE__, 1.0f, -1.0f, v1);
	assertEquals(__LINE__, 1.0f, 1.0f, v2);


	v1 = Vector2(5.0f, 0.0f);
	assertTrue(__LINE__, areOrthogonal(v1, Vector2(0.0f, 3.0f)));
	assertTrue(__LINE__, areOrthogonal(v1, Vector2(0.0f, -3.0f)));
	assertTrue(__LINE__, !areOrthogonal(v1, Vector2(3.0f, 4.0f)));
}