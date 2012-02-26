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

#include "Vector4.hpp"

using namespace fun::math;

Vector4::Vector4() 
{
	for (int i = 0; i < dim(); ++i)
		v[i] = 0.0f;
}

Vector4::Vector4(float _x, float _y, float _z, float _w) 
{
	v[X] = _x;
	v[Y] = _y;
	v[Z] = _z;
	v[W] = _w;
}

Vector4::Vector4(float xyz[4])
{
	memcpy(v, xyz, sizeof(v));
}

Vector4& Vector4::set(float _x, float _y, float _z, float _w)
{
	v[X] = _x;
	v[Y] = _y;
	v[Z] = _z;
	v[W] = _w;
    return *this;
}

Vector4& Vector4::set(const float xyz[4])
{
	memcpy(v, xyz, sizeof(v));
    return *this;
}

Vector4& Vector4::operator +=(const Vector4& other)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] += other[i];
    return *this;
}

Vector4& Vector4::operator -=(const Vector4& other)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] -= other[i];
    return *this;
}

Vector4& Vector4::operator *=(float c)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] *= c;
    return *this;
}

Vector4& Vector4::operator *=(const Vector4& other)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] *= other[i];
    return *this;
}

Vector4& Vector4::operator /=(float c)
{
    return *this *= (1.0f / c);
}

Vector4 Vector4::operator -(void) const
{
    return (Vector4(-v[X], -v[Y], -v[Z]));
}

Vector4 Vector4::operator +(const Vector4& other) const
{
    return Vector4(*this) += other;
}

Vector4 Vector4::operator -(const Vector4& other) const
{
    return Vector4(*this) -= other;
}

Vector4 Vector4::operator *(float c) const
{
    return Vector4(*this) *= c;
}

Vector4 fun::math::operator * (float scalar, const Vector4& vector)
{
	return vector * scalar;
}

Vector4 Vector4::operator /(float t) const
{
    return Vector4(*this) /= t;
}

Vector4 Vector4::operator *(const Vector4& other)
{
    return Vector4(*this) *= other;
}

bool Vector4::operator ==(const Vector4& other) const
{
	for (int i = 0; i < dim(); ++i)
		if (!equals(v[i], other[i]))
			return false;
	return true;
}

bool Vector4::operator !=(const Vector4& other) const
{
    return !(*this == other);
}

float Vector4::sizeSqr() const
{
	float sizeSqrResult = 0;
	for (int i = 0; i < dim(); ++i)
		sizeSqrResult += v[i] * v[i];
	return sizeSqrResult;
}

float Vector4::size() const
{
    return sqrtf(sizeSqr());
}

float Vector4::dot(const Vector4& other) const
{
	float dotResult = 0.0f;
	for (int i = 0; i < dim(); ++i)
		dotResult += v[i] * other[i];
	return dotResult;
}

bool Vector4::isZero() const
{
	for (int i = 0; i < dim(); ++i)
		if (!equals(v[i], 0))
			return false;
	return true;
}

Vector4& Vector4::resize(float size)
{
	return normalize() *= size;
}

Vector4& Vector4::normalize()
{
	float s = sizeSqr();
	return (s == 0) ? *this : (*this /= sqrtf(s));
}

std::ostream& fun::math::operator<<(std::ostream& output, const Vector4& p)
{
	return output << "(" << p[X] << "," << p[Y] << "," << p[Z] << "," << p[W] << ")";	
}