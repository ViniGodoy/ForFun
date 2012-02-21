#include "Matrix3Test.hpp"

#include "assert.hpp"
#include <Math/AffineTransform.hpp>
#include <Math/Matrix3.hpp>

Matrix3 matrix1();
Matrix3 matrix2();

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