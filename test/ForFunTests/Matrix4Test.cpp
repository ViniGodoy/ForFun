#include <Math/Matrix4.hpp>
#include "assert.hpp"
#include "Matrix4Test.hpp"

Matrix4 matrix4Seq();
Matrix4 matrix4DetMinus51();
Matrix4 matrix4WithInverse();
Matrix4 matrix4Inverse();

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