#include "assert.hpp"

void assertTrue(int line, bool value)
{
	if (!value) {
		cout << "Assertion failed at line " << line << "! Value was FALSE and should be TRUE." << endl;
		system("pause");
		exit(1);		
	}
}

void assertEquals(int line, float desired, float value, float delta)
{
	if (!equals(desired, value)) {
		cout << "Assertion failed at line " << line << "! Value was " << value << " and should be " << desired << "." << endl;
		system("pause");
		exit(1);		
	}
}

void assertEquals(int line, float x, float y, const Vector2& vector, float delta)
{
	assertEquals(line, x, vector.x, delta);
	assertEquals(line, y, vector.y, delta);	
}

void assertEquals(int line, float x, float y, float z, const Vector3& vector, float delta)
{
	assertEquals(line, x, vector.x, delta);
	assertEquals(line, y, vector.y, delta);	
	assertEquals(line, z, vector.z, delta);	
}

void assertEquals(int line, 
	float a, float b, float c, 
	float d, float e, float f,
	float g, float h, float k, const Matrix3& matrix, 
	float delta)
{
	assertEquals(line+1, a, matrix(0,0), delta);
	assertEquals(line+1, b, matrix(0,1), delta);
	assertEquals(line+1, c, matrix(0,2), delta);
	assertEquals(line+2, d, matrix(1,0), delta);
	assertEquals(line+2, e, matrix(1,1), delta);
	assertEquals(line+2, f, matrix(1,2), delta);
	assertEquals(line+3, g, matrix(2,0), delta);
	assertEquals(line+3, h, matrix(2,1), delta);
	assertEquals(line+3, k, matrix(2,2), delta);	
}

void assertEquals(int line, 
	float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p, 
	const Matrix4& matrix, float delta)
{	
	assertEquals(line+1, a, matrix(0,0), delta);
	assertEquals(line+1, b, matrix(0,1), delta);
	assertEquals(line+1, c, matrix(0,2), delta);
	assertEquals(line+1, d, matrix(0,3), delta);

	assertEquals(line+2, e, matrix(1,0), delta);
	assertEquals(line+2, f, matrix(1,1), delta);
	assertEquals(line+2, g, matrix(1,2), delta);
	assertEquals(line+2, h, matrix(1,3), delta);

	assertEquals(line+3, i, matrix(2,0), delta);
	assertEquals(line+3, j, matrix(2,1), delta);
	assertEquals(line+3, k, matrix(2,2), delta);
	assertEquals(line+3, l, matrix(2,3), delta);

	assertEquals(line+4, m, matrix(3,0), delta);
	assertEquals(line+4, n, matrix(3,1), delta);
	assertEquals(line+4, o, matrix(3,2), delta);
	assertEquals(line+4, p, matrix(3,3), delta);
}

void assertEquals(int line, const Matrix3& desired, const Matrix3& other, float delta)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			assertEquals(line, desired(i,j), other(i,j), delta);
}

void assertEquals(int line, const Matrix4& desired, const Matrix4& other, float delta)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			assertEquals(line, desired(i,j), other(i,j), delta);
}