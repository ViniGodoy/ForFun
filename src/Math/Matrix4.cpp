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
#include "Matrix4.hpp"

#include <cmath>
#include <algorithm>

using namespace fun::math;

Matrix4::Matrix4()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			A[i][j] = 0;
}

Matrix4::Matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	set(m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33);
}
				
Matrix4 Matrix4::newIdentity()
{
	return Matrix4(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1);
}

/** Copy constructor */
Matrix4::Matrix4(const Matrix4& other)
{
	memcpy(A, other.A, sizeof(other.A));
}

Matrix4& Matrix4::set(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	A[0][0] = m00;
	A[0][1] = m01;
	A[0][2] = m02;
	A[0][3] = m03;

	A[1][0] = m10;
	A[1][1] = m11;
	A[1][2] = m12;
	A[1][3] = m13;

	A[2][0] = m20;
	A[2][1] = m21;
	A[2][2] = m22;
	A[2][3] = m23;

	A[3][0] = m30;
	A[3][1] = m31;
	A[3][2] = m32;
	A[3][3] = m33;

	return *this;
}

/** Assignment operator */
Matrix4& Matrix4::operator=(const Matrix4& other)
{
	memcpy(A, other.A, sizeof(A));
	return *this;
}
	
Matrix4& Matrix4::operator += (const Matrix4& other)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			A[i][j] += other(i,j);

	return *this;
}

Matrix4 Matrix4::operator + (const Matrix4& other) const
{
	return Matrix4(*this) += other;
}

Matrix4& Matrix4::operator -= (const Matrix4& other)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			A[i][j] -= other(i,j);

	return *this;
}

Matrix4 Matrix4::operator - (const Matrix4& other) const
{
	return Matrix4(*this) -= other;
}

Matrix4& Matrix4::operator *= (const Matrix4& other)
{
	return *this = (*this * other);
}

Matrix4 Matrix4::operator * (const Matrix4& other) const
{
	Matrix4 C;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				C(i,j) += A[i][k] * other(k,j);

	return C;
}

Matrix4 fun::math::operator *(float scalar, const Matrix4& matrix)
{
	return matrix * scalar;
}

Matrix4& Matrix4::operator *= (float scalar)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			A[i][j] *= scalar;

	return *this;
}

Matrix4 Matrix4::operator * (float scalar) const
{
	return Matrix4(*this) *= scalar;
}

bool Matrix4::operator == (Matrix4& other) const
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (A[i][j] != other(i,j))
				return false;
	return true;
}

bool Matrix4::operator != (Matrix4& other) const
{
	return !(*this == other);
}


float Matrix4::determinant() const
{
	return A[0][0]*(A[1][1]*(A[2][2]*A[3][3]-A[2][3]*A[3][2]) + A[1][2]*(A[2][3]*A[3][1]-A[2][1]*A[3][3]) + A[1][3]*(A[2][1]*A[3][2]-A[2][2]*A[3][1]))
		 - A[0][1]*(A[1][0]*(A[2][2]*A[3][3]-A[2][3]*A[3][2]) + A[1][2]*(A[2][3]*A[3][0]-A[2][0]*A[3][3]) + A[1][3]*(A[2][0]*A[3][2]-A[2][2]*A[3][0]))
		 + A[0][2]*(A[1][0]*(A[2][1]*A[3][3]-A[2][3]*A[3][1]) + A[1][1]*(A[2][3]*A[3][0]-A[2][0]*A[3][3]) + A[1][3]*(A[2][0]*A[3][1]-A[2][1]*A[3][0]))
		 - A[0][3]*(A[1][0]*(A[2][1]*A[3][2]-A[2][2]*A[3][1]) + A[1][1]*(A[2][2]*A[3][0]-A[2][0]*A[3][2]) + A[1][2]*(A[2][0]*A[3][1]-A[2][1]*A[3][0])); 
}

bool Matrix4::isInvertible() const
{
	return determinant() != 0;
}

Matrix4& Matrix4::inverse()
{	
	return (*this = math::inverse(*this));
}

Matrix4& Matrix4::transpose()
{
	std::swap(A[0][1], A[1][0]);
	std::swap(A[0][2], A[2][0]);
	std::swap(A[0][3], A[3][0]);

	std::swap(A[1][2], A[2][1]);
	std::swap(A[1][3], A[3][1]);

	std::swap(A[2][3], A[3][2]);
	return *this;
}

Matrix4 fun::math::inverse(const Matrix4& m)
{
	Matrix4 inv;

	//Calculate the classical adjoint of m --> adj(m)
    inv(0,0) =	m(1,1) * m(2,2) * m(3,3) - 
				m(1,1) * m(2,3) * m(3,2) - 
				m(2,1) * m(1,2) * m(3,3) + 
				m(2,1) * m(1,3) * m(3,2) +
				m(3,1) * m(1,2) * m(2,3) - 
				m(3,1) * m(1,3) * m(2,2);

    inv(0,1) = -m(0,1) * m(2,2) * m(3,3) + 
				m(0,1) * m(2,3) * m(3,2) + 
				m(2,1) * m(0,2) * m(3,3) - 
				m(2,1) * m(0,3) * m(3,2) - 
				m(3,1) * m(0,2) * m(2,3) + 
				m(3,1) * m(0,3) * m(2,2);

	inv(0,2) =	m(0,1) * m(1,2) * m(3,3) - 
				m(0,1) * m(1,3) * m(3,2) - 
				m(1,1) * m(0,2) * m(3,3) + 
				m(1,1) * m(0,3) * m(3,2) + 
				m(3,1) * m(0,2) * m(1,3) - 
				m(3,1) * m(0,3) * m(1,2);

	inv(0,3) = -m(0,1) * m(1,2) * m(2,3) + 
				m(0,1) * m(1,3) * m(2,2) + 
				m(1,1) * m(0,2) * m(2,3) - 
				m(1,1) * m(0,3) * m(2,2) - 
				m(2,1) * m(0,2) * m(1,3) + 
				m(2,1) * m(0,3) * m(1,2);

    inv(1,0) = -m(1,0) * m(2,2) * m(3,3) + 
				m(1,0) * m(2,3) * m(3,2) + 
				m(2,0) * m(1,2) * m(3,3) - 
				m(2,0) * m(1,3) * m(3,2) - 
				m(3,0) * m(1,2) * m(2,3) + 
				m(3,0) * m(1,3) * m(2,2);

	inv(1,1) =	m(0,0) * m(2,2) * m(3,3) - 
				m(0,0) * m(2,3) * m(3,2) - 
				m(2,0) * m(0,2) * m(3,3) + 
				m(2,0) * m(0,3) * m(3,2) + 
				m(3,0) * m(0,2) * m(2,3) - 
				m(3,0) * m(0,3) * m(2,2);

    inv(1,2) = -m(0,0)  * m(1,2) * m(3,3) + 
				m(0,0)  * m(1,3) * m(3,2) + 
				m(1,0)  * m(0,2) * m(3,3) - 
				m(1,0)  * m(0,3) * m(3,2) - 
				m(3,0) * m(0,2) * m(1,3) + 
				m(3,0) * m(0,3) * m(1,2);

    inv(1,3) =	m(0,0) * m(1,2) * m(2,3) - 
				m(0,0) * m(1,3) * m(2,2) - 
				m(1,0) * m(0,2) * m(2,3) + 
				m(1,0) * m(0,3) * m(2,2) + 
				m(2,0) * m(0,2) * m(1,3) - 
				m(2,0) * m(0,3) * m(1,2);

    inv(2,0) =	m(1,0) * m(2,1) * m(3,3) - 
				m(1,0) * m(2,3) * m(3,1) - 
				m(2,0) * m(1,1) * m(3,3) + 
				m(2,0) * m(1,3) * m(3,1) + 
				m(3,0) * m(1,1) * m(2,3) - 
				m(3,0) * m(1,3) * m(2,1);

	inv(2,1) = -m(0,0) * m(2,1) * m(3,3) + 
				m(0,0) * m(2,3) * m(3,1) + 
				m(2,0) * m(0,1) * m(3,3) - 
				m(2,0) * m(0,3) * m(3,1) - 
				m(3,0) * m(0,1) * m(2,3) + 
				m(3,0) * m(0,3) * m(2,1);

	inv(2,2) =	m(0,0)  * m(1,1) * m(3,3) - 
				m(0,0)  * m(1,3) * m(3,1) - 
				m(1,0)  * m(0,1) * m(3,3) + 
				m(1,0)  * m(0,3) * m(3,1) + 
				m(3,0) * m(0,1) * m(1,3) - 
				m(3,0) * m(0,3) * m(1,1);

    inv(2,3) = -m(0,0) * m(1,1) * m(2,3) + 
				m(0,0) * m(1,3) * m(2,1) + 
				m(1,0) * m(0,1) * m(2,3) - 
				m(1,0) * m(0,3) * m(2,1) - 
				m(2,0) * m(0,1) * m(1,3) + 
				m(2,0) * m(0,3) * m(1,1);

    inv(3,0) = -m(1,0) * m(2,1) * m(3,2) + 
				m(1,0) * m(2,2) * m(3,1) +
				m(2,0) * m(1,1) * m(3,2) - 
				m(2,0) * m(1,2) * m(3,1) - 
				m(3,0) * m(1,1) * m(2,2) + 
				m(3,0) * m(1,2) * m(2,1);

    inv(3,1) =	m(0,0) * m(2,1) * m(3,2) - 
				m(0,0) * m(2,2) * m(3,1) - 
				m(2,0) * m(0,1) * m(3,2) + 
				m(2,0) * m(0,2) * m(3,1) + 
				m(3,0) * m(0,1) * m(2,2) - 
				m(3,0) * m(0,2) * m(2,1);

    inv(3,2) = -m(0,0) * m(1,1) * m(3,2) + 
				m(0,0) * m(1,2) * m(3,1) + 
				m(1,0) * m(0,1) * m(3,2) - 
				m(1,0) * m(0,2) * m(3,1) - 
				m(3,0) * m(0,1) * m(1,2) + 
				m(3,0) * m(0,2) * m(1,1);

    inv(3,3) =	m(0,0) * m(1,1) * m(2,2) - 
				m(0,0) * m(1,2) * m(2,1) - 
				m(1,0) * m(0,1) * m(2,2) + 
				m(1,0) * m(0,2) * m(2,1) + 
				m(2,0) * m(0,1) * m(1,2) - 
				m(2,0) * m(0,2) * m(1,1);

	//Calculate the determinant of m --> det(m)
	//Avoid calling determinant() since some values are already precalculated in the adjoint
    float det = m(0,0) * inv(0,0) + m(0,1) * inv(1,0) + m(0,2) * inv(2,0) + m(0,3) * inv(3,0);

	//Calculate the inverse (that is equals to adj(M) / det(M))
    det = 1.0f / det;
    for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			inv(i,j) = inv(i,j) * det;

    return inv;
}

Matrix4 fun::math::transpose(const Matrix4& matrix)
{
	Matrix4 other;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			other(i, j) = matrix(j, i);

	return other;
}

std::ostream& fun::math::operator<<(std::ostream& output, const Matrix4& m)
{
	output << "((" << m(0,0) << "," << m(0,1) << "," << m(0,2) << "," << m(0,3)<< "), "
			<< "(" << m(1,0) << "," << m(1,1) << "," << m(1,2) << "," << m(1,3)<< "), "
			<< "(" << m(2,0) << "," << m(2,1) << "," << m(2,2) << "," << m(2,3)<< "), "
			<< "(" << m(3,0) << "," << m(3,1) << "," << m(3,2) << "," << m(3,3)<< "))";
	return output;	
}