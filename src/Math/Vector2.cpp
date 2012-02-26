/******************************************************************************
*
* COPYRIGHT Vin�cius G. Mendon�a ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vin�cius G.Mendon�a prior authorization.
*
* This file was made available on https://github.com/ViniGodoy/ForFun and it 
* is free to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autoriza��o 
* a priori de Vin�cius G. Mendon�a
*
* Este arquivo foi disponibilizado no site https://github.com/ViniGodoy/ForFun 
* e esta livre para distribui��o seguindo a licen�a Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/

#include "Vector2.hpp"
#include "MathUtil.hpp"

#include <stdexcept>
#include <sstream>

using namespace fun::math;

Vector2::Vector2()
{	
	for (int i = 0; i < dim(); ++i)
		v[i] = 0.0f;
}

Vector2::Vector2(float _x, float _y)
{
	v[X] = _x;
	v[Y] = _y;
}

Vector2::Vector2(float xy[2]) 
{
	memcpy(v, xy, sizeof(v));
}

Vector2 Vector2::newBySizeAngle(float size, float radians)
{
    return Vector2(cos(radians) * size, sin(radians) * size);
}

Vector2& Vector2::set(float _x, float _y)
{	
	v[X] = _x;
	v[Y] = _y;
	return *this;
}

Vector2& Vector2::set(const float xy[2])
{
	memcpy(v, xy, sizeof(v));
    return *this;
}

float Vector2::sizeSqr() const
{
	float sizeSqr = 0;
	for (int i = 0; i < dim(); ++i)
		sizeSqr += v[i] * v[i];
	return sizeSqr;
}

float Vector2::size() const
{
	return sqrtf(sizeSqr());
}

float Vector2::angle() const
{
	return atan2f(v[Y],v[X]);
}

Vector2& Vector2::rotate(float radians) 
{
	float s = sin(radians);
    float c = cos(radians);

    float newX = v[X] * c - v[Y] * s;
    float newY = v[X] * s + v[Y] * c;

    v[X] = newX;
    v[Y] = newY;

    return *this;
}

Vector2& Vector2::normalize()
{
	float s = sizeSqr();
	return (s == 0) ? *this : (*this /= sqrtf(s));
}

Vector2& Vector2::resize(float size)
{
	return normalize() *= size;
}

Vector2& Vector2::operator += (const Vector2& other)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] += other[i];
    return *this;
}

Vector2& Vector2::operator -= (const Vector2& other)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] -= other[i];
	return *this;
}

Vector2& Vector2::operator *= (float c)
{
	for (int i = 0; i < dim(); ++i) 
		v[i] *= c;
	return *this;
}

Vector2& Vector2::operator /= (float c)
{	
    return *this *= (1.0f / c);
}

Vector2 Vector2::operator -(void) const
{
	return Vector2(-v[X], -v[Y]);
}

Vector2 Vector2::operator +(const Vector2& other) const
{
	return Vector2(*this) += other;
}

Vector2 Vector2::operator -(const Vector2& other) const
{
	return Vector2(*this) -= other;
}

Vector2 Vector2::operator *(float c) const
{
	return Vector2(*this) *= c;
}

Vector2 fun::math::operator*(float scalar, const Vector2& vector)
{
	return vector * scalar;
}

Vector2 Vector2::operator /(float c) const
{
	return Vector2(*this) /= c;
}

bool Vector2::operator ==(const Vector2& other) const
{
	for (int i = 0; i < dim(); ++i)
		if (!equals(v[i], other[i]))
			return false;
	return true;	
}

bool Vector2::operator !=(const Vector2& other) const
{
	return !(*this == other);
}

float Vector2::dot(const Vector2& other) const
{
	float dotResult = 0.0f;
	for (int i = 0; i < dim(); ++i)
		dotResult += v[i] * other[i];    
	return dotResult;
}

float Vector2::relativeAngleBetween(const Vector2 v2) const
{
	return angle() - v2.angle();
}

bool Vector2::isZero() const
{
	for (int i = 0; i < dim(); ++i)
		if (!equals(v[i], 0))
			return false;
	return true;
}

std::ostream& fun::math::operator<<(std::ostream& output, const Vector2& p)
{
	return output << "(" << p[X] << "," << p[Y] << ")";
}
