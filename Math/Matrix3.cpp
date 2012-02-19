/******************************************************************************
*
* COPYRIGHT Vinícius G. Mendonça ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vinícius G.Mendonça prior authorization.
*
* This file was made available on https://github.com/ViniGodoy/ForFun and it 
* is free to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autorização 
* a priori de Vinícius G. Mendonça
*
* Este arquivo foi disponibilizado no site https://github.com/ViniGodoy/ForFun 
* e esta livre para distribuição seguindo a licença Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/
#include "Matrix3.hpp"

#include <cmath>
#include <algorithm>

using namespace s3d::math;

/**
* Represents a 3x3 matrix.
* <p>
* All mathematical operator methods comes with two signatures. The first one creates a copy of the matrix, prior to the
* operation. The second one, suffixed with "Me", applies the operation the calling matrix.
* <p>
* This class also provides convenient access methods to retrieve or set the matrix elements as:
*
* <pre>
* [a b c]
* [d e f]
* [g h k]
* </pre>
*
* These methods are named {@link #a()}, {@link #b()}, {@link #c()}, {@link #d()}, {@link #e()},
* {@link #f()}, {@link #g()}, {@link #h()} and {@link #k()}.
* <p>
* In other to use this matrix as an Affine Transformation, take a look at the static functions defined in 
* AffineTransform.h
*
* @author Vinicius G. Mendonca
*/
Matrix3::Matrix3()
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			A[i][j] = 0;
}

Matrix3::Matrix3(
	float a, float b, float c, 
	float d, float e, float f, 
	float g, float h, float k)
{
	set(a, b, c,
		d, e, f,
		g, h, k);
}
				
Matrix3 Matrix3::newIdentity()
{
	return Matrix3(
		1,0,0,
		0,1,0,
		0,0,1);
}

/** Copy constructor */
Matrix3::Matrix3(const Matrix3& other)
{
	memcpy(A, (void*)(other.A), sizeof(other.A));
}

Matrix3& Matrix3::set(
	float a, float b, float c,
	float d, float e, float f,
	float g, float h, float k)
{
	A[0][0] = a;
	A[0][1] = b;
	A[0][2] = c;

	A[1][0] = d;
	A[1][1] = e;
	A[1][2] = f;

	A[2][0] = g;
	A[2][1] = h;
	A[2][2] = k;

	return *this;
}

/** Assignment operator */
Matrix3& Matrix3::operator=(const Matrix3& other)
{
	return set(other.a(), other.b(), other.c(),
			   other.d(), other.e(), other.f(),
			   other.g(), other.h(), other.k());
}
	
Matrix3& Matrix3::operator += (const Matrix3& other)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			A[i][j] += other.A[i][j];

	return *this;
}

Matrix3 Matrix3::operator + (const Matrix3& other) const
{
	return Matrix3(*this) += other;
}

Matrix3& Matrix3::operator -= (const Matrix3& other)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			A[i][j] -= other.A[i][j];

	return *this;
}

Matrix3 Matrix3::operator - (const Matrix3& other) const
{
	return Matrix3(*this) -= other;
}

Matrix3& Matrix3::operator *= (const Matrix3& other)
{
	return *this = (*this * other);
}

Matrix3 Matrix3::operator * (const Matrix3& other) const
{
	Matrix3 C;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				C.A[i][j] += A[i][k] * other.A[k][j];

	return C;
}

Matrix3 s3d::math::operator *(float scalar, const Matrix3& matrix)
{
	return matrix * scalar;
}

Matrix3& Matrix3::operator *= (float scalar)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			A[i][j] *= scalar;

	return *this;
}

Matrix3 Matrix3::operator * (float scalar) const
{
	return Matrix3(*this) *= scalar;
}

bool Matrix3::operator == (Matrix3& other) const
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (A[i][j] != other.A[i][j])
				return false;
	return true;
}

bool Matrix3::operator != (Matrix3& other) const
{
	return !(*this == other);
}


float Matrix3::determinant() const
{
	return a() * (e() * k() - f() * h()) +
           b() * (f() * g() - k() * d()) +
           c() * (d() * h() - e() * g());
}

bool Matrix3::isInvertible() const
{
	return determinant() != 0;
}

Matrix3& Matrix3::inverse()
{	
	return (*this = math::inverse(*this));
}

Matrix3& Matrix3::transpose()
{
	return (*this = math::transpose(*this));
}

Matrix3 s3d::math::inverse(const Matrix3& A)
{
    return Matrix3 (
		A.e() * A.k() - A.f() * A.h(), 
		A.c() * A.h() - A.b() * A.k(),
		A.b() * A.f() - A.c() * A.e(),

		A.f() * A.g() - A.d() * A.k(),
		A.a() * A.k() - A.c() * A.g(),
		A.c() * A.d() - A.a() * A.f(),

		A.d() * A.h() - A.e() * A.g(),
		A.b() * A.g() - A.a() * A.h(),
		A.a() * A.e() - A.b() * A.d());
}

Matrix3 s3d::math::transpose(const Matrix3& matrix)
{
	Matrix3 other;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			other(i, j) = matrix(j, i);

	return other;	
}
