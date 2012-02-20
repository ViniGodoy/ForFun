/******************************************************************************
*
* COPYRIGHT Vinícius G. Mendonça ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vinícius G.Mendonça prior authorization.
*
* This file was made available on http://www.pontov.com.br and it is free 
* to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autorização 
* a priori de Vinícius G. Mendonça
*
* Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta 
* livre para distribuição seguindo a licença Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/
#include <iostream>
#include "assert.hpp"

void testVector2()
{
	cout << "Testing Vector2 class..." << endl;

	//Constructor test
	Vector2 v1;
	assertEquals(__LINE__, 0.0f, 0.0f, v1);	

	v1 = Vector2(0.5f, 0.3f);
	assertEquals(__LINE__, 0.5f, 0.3f, v1);	

	v1.set(0.5f, 0.3f);
	Vector2 v2(v1);
	assertEquals(__LINE__, 0.5f, 0.3f, v2);

	
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


void testVector3()
{
	cout << "Testing Vector3 class..." << endl;
}

Matrix3 matrix1()
{
	return Matrix3(
		1,2,3,
		4,5,6,
		7,8,9);
}

Matrix3 matrix2()
{
	return Matrix3(
		1,9,2,
		8,3,7,
		4,6,5);	
}

void testMatrix3()
{
	cout << "Testing Matrix3 class..." << endl;

	Matrix3 matrix3d = Matrix3(
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f);
	assertEquals(__LINE__, 
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, matrix3d);

	//Constructors
	Matrix3 matrix = Matrix3(matrix3d);	
	assertEquals(__LINE__, matrix, matrix3d);

	matrix3d = Matrix3();
	assertEquals(__LINE__, 
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, matrix3d);

	
	assertEquals(__LINE__,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 
		Matrix3::newIdentity());

	//Getters and setters
	matrix3d.set(
		9.0f, 8.0f, 7.0f,
		6.0f, 5.0f, 4.0f,
		3.0f, 2.0f, 1.0f);
	assertEquals(__LINE__, 
		9.0f, 8.0f, 7.0f,
		6.0f, 5.0f, 4.0f,
		3.0f, 2.0f, 1.0f, matrix3d);

	matrix3d(0,0) = 10.0f;
	matrix3d(0,1) = 11.0f;
	matrix3d(0,2) = 12.0f;
	matrix3d(1,0) = 13.0f;
	matrix3d(1,1) = 14.0f;
	matrix3d(1,2) = 15.0f;
	matrix3d(2,0) = 16.0f;
	matrix3d(2,1) = 17.0f;
	matrix3d(2,2) = 18.0f;
	assertEquals(__LINE__, 
		10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f,
		16.0f, 17.0f, 18.0f, matrix3d);


	matrix3d = matrix1();
	const Matrix3 m = matrix1();
	assertEquals(__LINE__, 1.0f, m(0,0));
	assertEquals(__LINE__, 2.0f, m(0,1));
	assertEquals(__LINE__, 3.0f, m(0,2));
	assertEquals(__LINE__, 4.0f, m(0,3));
	assertEquals(__LINE__, 5.0f, m(0,4));
	assertEquals(__LINE__, 6.0f, m(0,5));
	assertEquals(__LINE__, 7.0f, m(0,6));
	assertEquals(__LINE__, 8.0f, m(0,7));
	assertEquals(__LINE__, 9.0f, m(0,8));

	//Operators
	matrix3d = matrix1();
	matrix3d += matrix2();
	assertEquals(__LINE__,
		2.0f, 11.0f, 5.0f,
		12.0f, 8.0f, 13.0f,
		11.0f, 14.0f, 14.0f, matrix3d);
	
	matrix3d = matrix1();
	Matrix3 other = matrix3d + matrix2();
	assertEquals(__LINE__, matrix1(), matrix3d);
	assertEquals(__LINE__,
		2.0f, 11.0f, 5.0f,
		12.0f, 8.0f, 13.0f,
		11.0f, 14.0f, 14.0f, other);


	matrix3d = matrix1();
	matrix3d -= matrix2();
	assertEquals(__LINE__,
		0.0f, -7.0f, 1.0f,
		-4.0f, 2.0f, -1.0f,
		3.0f, 2.0f, 4.0f, matrix3d);
	
	matrix3d = matrix1();
	other = matrix3d - matrix2();
	assertEquals(__LINE__, matrix1(), matrix3d);
	assertEquals(__LINE__,
		0.0f, -7.0f, 1.0f,
		-4.0f, 2.0f, -1.0f,
		3.0f, 2.0f, 4.0f, other);


	matrix3d = matrix1();
	matrix3d *= Matrix3(
		9.0f, 8.0f, 7.0f, 
		6.0f, 10.0f, 4.0f, 
		3.0f, 2.0f, 1.0f);

	assertEquals(__LINE__,
		30.0f, 34.0f, 18.0f,
		84.0f, 94.0f, 54.0f,
		138.0f, 154.0f, 90.0f, matrix3d);

	matrix3d = matrix1();
	other = matrix3d * Matrix3(
		9.0f, 8.0f, 7.0f, 
		6.0f, 10.0f, 4.0f, 
		3.0f, 2.0f, 1.0f);

	assertEquals(__LINE__, matrix1(), matrix3d);
	assertEquals(__LINE__,
		30.0f, 34.0f, 18.0f,
		84.0f, 94.0f, 54.0f,
		138.0f, 154.0f, 90.0f, other);


	matrix3d = matrix1();
	matrix3d *= 3;
	assertEquals(__LINE__,
		3.0f, 6.0f, 9.0f,
		12.0f, 15.0f, 18.0f,
		21.0f, 24.0f, 27.0f, matrix3d);

	matrix3d = matrix1();
	other = matrix1() * 3;
	assertEquals(__LINE__,
		3.0f, 6.0f, 9.0f,
		12.0f, 15.0f, 18.0f,
		21.0f, 24.0f, 27.0f, other);

	matrix3d = matrix1();
	other = 2 * matrix1();
	assertEquals(__LINE__,
		2.0f, 4.0f, 6.0f,
		8.0f, 10.0f, 12.0f,
		14.0f, 16.0f, 18.0f, other);


	//Methods
	matrix3d.set(
		5, 0, 1,
       -2, 3, 4,
       0, 2, -1);
	assertEquals(__LINE__, -59.0f, matrix3d.determinant());
	assertTrue(__LINE__, matrix3d.isInvertible());

	matrix3d.set(
		 1, 3, 10,
		-1, 1, 10,
		 0, 2, 10);
	assertEquals(__LINE__, 0.0f, matrix3d.determinant());
	assertTrue(__LINE__, !matrix3d.isInvertible());


	matrix3d.set(
		3, 0, 2,
		9, 1, 7,
		1, 0, 1);
	matrix3d.inverse();
	assertEquals(__LINE__,
		 1.0f, 0.0f, -2.0f,
	    -2.0f, 1.0f, -3.0f,
		-1.0f, 0.0f,  3.0f, matrix3d);

	matrix3d = matrix1();
	matrix3d.transpose();
	assertEquals(__LINE__,
		1.0f, 4.0f, 7.0f,
		2.0f, 5.0f, 8.0f,
		3.0f, 6.0f, 9.0f, matrix3d);


	//Auxiliary functions
	matrix3d = matrix1();
	other = transpose(matrix3d);
	assertEquals(__LINE__, matrix1(), matrix3d);
	assertEquals(__LINE__,
		1.0f, 4.0f, 7.0f,
		2.0f, 5.0f, 8.0f,
		3.0f, 6.0f, 9.0f, other);

	
	matrix3d.set(
		3, 0, 2,
		9, 1, 7,
		1, 0, 1);
	other = inverse(matrix3d);
	assertEquals(__LINE__,
		3, 0, 2,
		9, 1, 7,
		1, 0, 1, matrix3d);
	assertEquals(__LINE__,
		 1.0f, 0.0f, -2.0f,
	    -2.0f, 1.0f, -3.0f,
		-1.0f, 0.0f,  3.0f, other);
}

Matrix4 matrix4Seq()
{
	return Matrix4(
		 1.0f,  2.0f,  3.0f, 4.0f,
		 5.0f,  6.0f,  7.0f, 8.0f,
		 9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f);
}

Matrix4 matrix4DetMinus51()
{
	return Matrix4(
		 2.0f,  0.0f,  1.0f, -2.0f,
		-3.0f,  2.0f,  1.0f,  0.0f,
		 4.0f,  0.0f, -2.0f,  1.0f,
		 5.0f,  3.0f,  2.0f, -1.0f);
}

Matrix4 matrix4WithInverse()
{
	return Matrix4(
		 1.0f,  2.0f, -1.0f,  2.0f,
		 2.0f,  2.0f, -1.0f,  1.0f, 
		-1.0f, -1.0f,  1.0f, -1.0f,
		 2.0f,  1.0f, -1.0f,  2.0f);
}

Matrix4 matrix4Inverse()
{
	return Matrix4(
		 -0.5f,  0.5f, 0.5f,  0.5f,
		  0.5f,  0.5f, 0.5f, -0.5f, 
		  0.5f,  0.5f, 2.5f,  0.5f,
		  0.5f, -0.5f, 0.5f,  0.5f);
}

void testMatrix4()
{
	cout << "Testing Matrix4 class..." << endl;

	assertEquals(__LINE__, 
		1.0f, 2.0f, 3.0f, 4.0f, 
		5.0f, 6.0f, 7.0f, 8.0f, 
		9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f,
		matrix4Seq());

	//Constructors
	Matrix4 matrix = Matrix4(matrix4Seq());	
	assertEquals(__LINE__, matrix4Seq(), matrix);

	matrix = Matrix4();
	assertEquals(__LINE__, 
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 
		matrix);
	
	assertEquals(__LINE__,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		Matrix4::newIdentity());

	//Getters and setters
	matrix.set(
		16.0f, 15.0f, 14.0f, 14.0f,
		12.0f, 11.0f, 10.0f, 9.0f, 
		8.0f, 7.0f, 6.0f, 5.0f, 
		4.0f, 3.0f, 2.0f, 1.0f);

	assertEquals(__LINE__, 
		16.0f, 15.0f, 14.0f, 14.0f,
		12.0f, 11.0f, 10.0f, 9.0f, 
		8.0f, 7.0f, 6.0f, 5.0f, 
		4.0f, 3.0f, 2.0f, 1.0f, 
		matrix);

	matrix(0,0) = 10.0f;
	matrix(0,1) = 11.0f;
	matrix(0,2) = 12.0f;
	matrix(0,3) = 13.0f;
	matrix(1,0) = 14.0f;
	matrix(1,1) = 15.0f;
	matrix(1,2) = 16.0f;
	matrix(1,3) = 17.0f;
	matrix(2,0) = 18.0f;
	matrix(2,1) = 19.0f;
	matrix(2,2) = 20.0f;
	matrix(2,3) = 21.0f;
	matrix(3,0) = 22.0f;
	matrix(3,1) = 23.0f;
	matrix(3,2) = 24.0f;
	matrix(3,3) = 25.0f;

	assertEquals(__LINE__, 
		10.0f, 11.0f, 12.0f, 13.0f, 
		14.0f, 15.0f, 16.0f, 17.0f, 
		18.0f, 19.0f, 20.0f, 21.0f,
		22.0f, 23.0f, 24.0f, 25.0f,
		matrix);

	//Operators
	matrix = matrix4Seq();
	matrix += matrix4DetMinus51();
	assertEquals(__LINE__,
		  3.0f,  2.0f,  4.0f,  2.0f,
		  2.0f,  8.0f,  8.0f,  8.0f,
		 13.0f, 10.0f,  9.0f, 13.0f,
		 18.0f, 17.0f, 17.0f, 15.0f, 
		 matrix);
	
	matrix = matrix4Seq();
	Matrix4 other = matrix + matrix4DetMinus51();
	assertEquals(__LINE__, matrix4Seq(), matrix);
	assertEquals(__LINE__,
		  3.0f,  2.0f,  4.0f,  2.0f,
		  2.0f,  8.0f,  8.0f,  8.0f,
		 13.0f, 10.0f,  9.0f, 13.0f,
		 18.0f, 17.0f, 17.0f, 15.0f, 
		other);


	matrix = matrix4DetMinus51();
	matrix -= matrix4Seq();
	assertEquals(__LINE__,
		 1.0f,  -2.0f,  -2.0f,  -6.0f,
		-8.0f,  -4.0f,  -6.0f,  -8.0f,
		-5.0f, -10.0f, -13.0f, -11.0f,
		-8.0f, -11.0f, -13.0f, -17.0f, 
		matrix);

	
	matrix = matrix4DetMinus51();
	other = matrix - matrix4Seq();
	assertEquals(__LINE__, matrix4DetMinus51(), matrix);
	assertEquals(__LINE__,
		 1.0f,  -2.0f,  -2.0f,  -6.0f,
		-8.0f,  -4.0f,  -6.0f,  -8.0f,
		-5.0f, -10.0f, -13.0f, -11.0f,
		-8.0f, -11.0f, -13.0f, -17.0f, 
		 other);


	matrix = matrix4Seq();
	matrix *= matrix4DetMinus51();

	assertEquals(__LINE__,
		 28.0f, 16.0f,  5.0f,  -3.0f,
		 60.0f, 36.0f, 13.0f, -11.0f,
		 92.0f, 56.0f, 21.0f, -19.0f,
		124.0f, 76.0f, 29.0f, -27.0f,
	matrix);

	matrix = matrix4Seq();
	other = matrix * matrix4DetMinus51();

	assertEquals(__LINE__, matrix4Seq(), matrix);
	assertEquals(__LINE__,
		 28.0f, 16.0f,  5.0f,  -3.0f,
		 60.0f, 36.0f, 13.0f, -11.0f,
		 92.0f, 56.0f, 21.0f, -19.0f,
		124.0f, 76.0f, 29.0f, -27.0f,
		 other);


	matrix = matrix4Seq();
	matrix *= 3;
	assertEquals(__LINE__,
		3.0f, 6.0f, 9.0f, 12.0f, 
		15.0f, 18.0f, 21.0f, 24.0f, 
		27.0f, 30.0f, 33.0f, 36.0f,
		39.0f, 42.0f, 45.0f, 48.0f, 
		matrix);

	matrix = matrix4Seq();
	other = matrix * 3;
	assertEquals(__LINE__, matrix4Seq(), matrix);
	assertEquals(__LINE__,
		3.0f, 6.0f, 9.0f, 12.0f, 
		15.0f, 18.0f, 21.0f, 24.0f, 
		27.0f, 30.0f, 33.0f, 36.0f,
		39.0f, 42.0f, 45.0f, 48.0f, 
		other);

	//Methods
	assertEquals(__LINE__, -51.0f, matrix4DetMinus51().determinant());
	assertTrue(__LINE__, matrix4DetMinus51().isInvertible());

	matrix.set(
		 1, 3, 10, 15,
		 0, 0, 0, 0,
		 0, 2, 10, 11, 
		 1, -3, 10, 18);
	assertEquals(__LINE__, 0.0f, matrix.determinant());
	assertTrue(__LINE__, !matrix.isInvertible());


	matrix = matrix4WithInverse();
	matrix.inverse();
	assertEquals(__LINE__, matrix4Inverse(), matrix);

	matrix = matrix4Seq();
	matrix.transpose();
	assertEquals(__LINE__,
		1.0f, 5.0f, 9.0f, 13.0f,
		2.0f, 6.0f, 10.0f, 14.0f,
		3.0f, 7.0f, 11.0f, 15.0f,
		4.0f, 8.0f, 12.0f, 16.0f,
		matrix);


	//Auxiliary functions
	matrix = matrix4Seq();
	other = transpose(matrix);
	assertEquals(__LINE__, matrix4Seq(), matrix);
	assertEquals(__LINE__,
		1.0f, 5.0f, 9.0f, 13.0f,
		2.0f, 6.0f, 10.0f, 14.0f,
		3.0f, 7.0f, 11.0f, 15.0f,
		4.0f, 8.0f, 12.0f, 16.0f,
		other);
	
	matrix = matrix4WithInverse();
	other = inverse(matrix);
	assertEquals(__LINE__, matrix4WithInverse(), matrix);
	assertEquals(__LINE__, matrix4Inverse(), other);
}

void testAffineTransform()
{
	//Affine Transformation tests
	assertEquals(__LINE__,
		2.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 1.0f, lh::newAffineScale(2));

	assertEquals(__LINE__,
		2.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 1.0f, rh::newAffineScale(2));


	assertEquals(__LINE__,
		2.0f, 0.0f, 0.0f,
		0.0f, 3.0f, 0.0f,
		0.0f, 0.0f, 1.0f, lh::newAffineScale(2,3));

	assertEquals(__LINE__,
		2.0f, 0.0f, 0.0f,
		0.0f, 3.0f, 0.0f,
		0.0f, 0.0f, 1.0f, rh::newAffineScale(2,3));


	float angle = toRadians(30);
	float sina = sin(angle);
	float cosa = cos(angle);

	assertEquals(__LINE__,
		cosa, -sina, 0.0f,
	    sina,  cosa, 0.0f,
		0.0f,  0.0f, 1.0f, lh::newAffineRotation(angle));

	assertEquals(__LINE__,
		cosa,  sina, 0.0f,
	    -sina, cosa, 0.0f,
		0.0f,  0.0f, 1.0f, rh::newAffineRotation(angle));

	assertEquals(__LINE__,
		1.0f, 0.0f, 2.0f,
		0.0f, 1.0f, 3.0f,
		0.0f, 0.0f, 1.0f, rh::newAffineTranslation(2, 3));

	assertEquals(__LINE__,
		1.0f, 0.0f, 2.0f,
		0.0f, 1.0f, 3.0f,
		0.0f, 0.0f, 1.0f, rh::newAffineTranslation(Vector2(2, 3)));

	assertEquals(__LINE__,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		2.0f, 3.0f, 1.0f, lh::newAffineTranslation(2, 3));

	assertEquals(__LINE__,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		2.0f, 3.0f, 1.0f, lh::newAffineTranslation(Vector2(2, 3)));

	Vector2 v(2,3);
	Vector2 rot = rotate(v, 30);
	Matrix3 rotMatrix = lh::newAffineRotation(30);
	assertTrue(__LINE__, rot == lh::transform(rotMatrix, v, 1.0f));

	v.set(2,3);
	rot = rotate(v, -30);
	rotMatrix = rh::newAffineRotation(30);
	assertTrue(__LINE__, rot == rh::transform(rotMatrix, v, 1.0f));
}
int main(int argc, char* argv[])
{	
	testVector2();
	testVector3();	
	testMatrix3();
	testMatrix4();
	testAffineTransform();
	cout << "All tests passed" << endl;
	system("pause");
}