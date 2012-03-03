#if !defined(__ASSERT_HPP__)
#define __ASSERT_HPP__

#include <iostream>
#include <string>

#include "math/Vector2.hpp"
#include "math/Vector3.hpp"
#include "math/Vector4.hpp"

#include "math/Matrix3.hpp"
#include "math/Matrix4.hpp"

using namespace fun::math;
using namespace std;
using namespace fun::math;
using namespace std;

void reportMissing(const std::string& what);
void reportTesting(const std::string& what);

void assertTrue(int line, bool value);
void assertIntEquals(int line, int desired, int value);
void assertEquals(int line, float desired, float value, float delta=FLOAT_DELTA);
void assertEquals(int line, float x, float y, const Vector2& vector, float delta=FLOAT_DELTA);
void assertEquals(int line, float x, float y, float z, const Vector3& vector, float delta=FLOAT_DELTA);
void assertEquals(int line, float x, float y, float z, float w, const Vector4& vector, float delta=FLOAT_DELTA);

void assertEquals(int line, 
	float a, float b, float c, 
	float d, float e, float f,
	float g, float h, float k, const Matrix3& matrix, 
	float delta=FLOAT_DELTA);

void assertEquals(int line, 
	float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p, 
	const Matrix4& matrix, float delta=FLOAT_DELTA);

void assertEquals(int line, const Matrix3& desired, const Matrix3& other, float delta=FLOAT_DELTA);
void assertEquals(int line, const Matrix4& desired, const Matrix4& other, float delta=FLOAT_DELTA);

#endif