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

#include <stdexcept>
#include <sstream>

#include "Vector3.hpp"
#include "MathUtil.hpp"

using namespace fun::math;

Vector3::Vector3() 
{
	for (int i = 0; i < dim(); ++i)
		v[i] = 0.0f;
}

Vector3::Vector3(float _x, float _y, float _z) 
{
	v[X] = _x;
	v[Y] = _y;
	v[Z] = _z;
}

Vector3::Vector3(float xyz[3])
{
	memcpy(v, xyz, sizeof(v));
}

Vector3& Vector3::set(float _x, float _y, float _z)
{
	v[X] = _x;
	v[Y] = _y;
	v[Z] = _z;
    return *this;
}

Vector3& Vector3::set(const float xyz[3])
{
	memcpy(v, xyz, sizeof(v));
    return *this;
}

Vector3& Vector3::operator +=(const Vector3& other)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] += other[i];
    return *this;
}

Vector3& Vector3::operator -=(const Vector3& other)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] -= other[i];
    return *this;
}

Vector3& Vector3::operator *=(float c)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] *= c;
    return *this;
}

Vector3& Vector3::operator *=(const Vector3& other)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] *= other[i];
    return *this;
}

Vector3& Vector3::operator /=(float c)
{
    return *this *= (1.0f / c);
}

Vector3 Vector3::operator -(void) const
{
    return (Vector3(-v[X], -v[Y], -v[Z]));
}

Vector3 Vector3::operator +(const Vector3& other) const
{
    return Vector3(*this) += other;
}

Vector3 Vector3::operator -(const Vector3& other) const
{
    return Vector3(*this) -= other;
}

Vector3 Vector3::operator *(float c) const
{
    return Vector3(*this) *= c;
}

Vector3 fun::math::operator * (float scalar, const Vector3& vector)
{
	return vector * scalar;
}

Vector3 Vector3::operator /(float t) const
{
    return Vector3(*this) /= t;
}

Vector3 Vector3::operator *(const Vector3& other) const
{
    return Vector3(*this) *= other;
}

bool Vector3::operator ==(const Vector3& other) const
{
	for (int i = 0; i < dim(); ++i)
		if (!equals(v[i], other[i]))
			return false;
	return true;
}

bool Vector3::operator !=(const Vector3& other) const
{
    return !(*this == other);
}

float Vector3::sizeSqr() const
{
	float sizeSqrResult = 0;
	for (int i = 0; i < dim(); ++i)
		sizeSqrResult += v[i] * v[i];
	return sizeSqrResult;
}

float Vector3::size() const
{
    return sqrtf(sizeSqr());
}

float Vector3::dot(const Vector3& other) const
{
	float dotResult = 0.0f;
	for (int i = 0; i < dim(); ++i)
		dotResult += v[i] * other[i];
	return dotResult;
}

bool Vector3::isZero() const
{
	for (int i = 0; i < dim(); ++i)
		if (!equals(v[i], 0))
			return false;
	return true;
}

Vector3& Vector3::cross(const Vector3& other)
{
    float newX, newY;

    newX = v[Y] * other[Z] - v[Z] * other[Y];
    newY = v[Z] * other[X] - v[X] * other[Z];
    v[Z] = v[X] * other[Y] - v[Y] * other[X];

    v[X] = newX;
    v[Y] = newY;

    return *this;
}

Vector3& Vector3::resize(float size)
{
	return normalize() *= size;
}

Vector3& Vector3::normalize()
{
	float s = sizeSqr();
	return (s == 0) ? *this : (*this /= sqrtf(s));
}

Vector3& Vector3::rotateTwoAxis(int a0, int a1, float radians)
{
    float s = sinf(radians);
    float c = cosf(radians);

    float ny = c * v[a0] - s * v[a1];
    float nz = c * v[a1] + s * v[a0];

    v[a0] = ny;
    v[a1] = nz;

    return (*this);
}

Vector3& Vector3::rotateAxis(float angle, const Vector3& axis)
{
    float s = sinf(angle);
    float c = cosf(angle);
    float k = 1.0F - c;

    float nx = v[X] * (c + k * axis[X] * axis[X]) +
               v[Y] * (k * axis[X] * axis[Y] - s * axis[Z]) +
               v[Z] * (k * axis[X] * axis[Z] + s * axis[Y]);

    float ny = v[X] * (k * axis[X] * axis[Y] + s * axis[Z]) +
               v[Y] * (c + k * axis[Y] * axis[Y]) +
               v[Z] * (k * axis[Y] * axis[Z] - s * axis[X]);

    float nz = v[X] * (k * axis[X] * axis[Z] - s * axis[Y]) +
               v[Y] * (k * axis[Y] * axis[Z] + s * axis[X]) +
               v[Z] * (c + k * axis[Z] * axis[Z]);

    v[X] = nx;
    v[Y] = ny;
    v[Z] = nz;

    return *this;
}

std::ostream& fun::math::operator<<(std::ostream& output, const Vector3& p)
{
	return output << "(" << p[X] << "," << p[Y] << "," << p[Z] << ")";	
}