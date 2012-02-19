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

using namespace fun::math;

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
	memcpy(A, other.A, sizeof(other.A));
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
	memcpy(A, other.A, sizeof(A));
	return *this;
}
	
Matrix3& Matrix3::operator += (const Matrix3& other)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			A[i][j] += other(i,j);

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
			A[i][j] -= other(i,j);

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
				C(i,j) += A[i][k] * other(k,j);

	return C;
}

Matrix3 fun::math::operator *(float scalar, const Matrix3& matrix)
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
			if (A[i][j] != other(i,j))
				return false;
	return true;
}

bool Matrix3::operator != (Matrix3& other) const
{
	return !(*this == other);
}


float Matrix3::determinant() const
{
	return A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]) +
           A[0][1] * (A[1][2] * A[2][0] - A[2][2] * A[1][0]) +
           A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
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
	std::swap(A[0][1], A[1][0]);
	std::swap(A[0][2], A[2][0]);
	std::swap(A[1][2], A[2][1]);
	return *this;
}

Matrix3 fun::math::inverse(const Matrix3& m)
{
    return Matrix3 (
		m(1,1) * m(2,2) - m(1,2) * m(2,1), 
		m(0,2) * m(2,1) - m(0,1) * m(2,2),
		m(0,1) * m(1,2) - m(0,2) * m(1,1),

		m(1,2) * m(2,0) - m(1,0) * m(2,2),
		m(0,0) * m(2,2) - m(0,2) * m(2,0),
		m(0,2) * m(1,0) - m(0,0) * m(1,2),

		m(1,0) * m(2,1) - m(1,1) * m(2,0),
		m(0,1) * m(2,0) - m(0,0) * m(2,1),
		m(0,0) * m(1,1) - m(0,1) * m(1,0));
}

Matrix3 fun::math::transpose(const Matrix3& matrix)
{
	Matrix3 other;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			other(i, j) = matrix(j, i);

	return other;	
}

std::ostream& fun::math::operator<<(std::ostream& output, const Matrix3& m)
{
	output << "((" << m(0,0) << "," << m(0,1) << "," << m(0,2) << "), "
			<< "(" << m(1,0) << "," << m(1,1) << "," << m(1,2) << "), "
			<< "(" << m(2,0) << "," << m(2,1) << "," << m(2,2) << "))";
	return output;	
}