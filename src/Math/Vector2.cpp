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

#include "Vector2.hpp"
#include "MathUtil.hpp"

#include <stdexcept>
#include <sstream>

using namespace fun::math;

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{
}

Vector2::Vector2(float xy[2]) : x(xy[0]), y(xy[1])
{
}

Vector2 Vector2::newBySizeAngle(float size, float radians)
{
    return Vector2(cos(radians) * size,
                    sin(radians) * size);
}

Vector2& Vector2::set(float _x, float _y)
{
	x = _x;
	y = _y;
	return *this;
}

Vector2& Vector2::set(const float xy[2])
{
    x = xy[0];
    y = xy[1];
    return *this;
}

Vector2& Vector2::set(const Vector2& other)
{
    if (&other == this)
        return *this;

    x = other.x;
    y = other.y;
    return *this;
}

float Vector2::sizeSqr() const
{
	return x * x + y * y;
}

float Vector2::size() const
{
	return sqrtf(sizeSqr());
}

float Vector2::angle() const
{
	return atan2f(y,x);
}

Vector2& Vector2::rotate(float radians) 
{
	float s = sin(radians);
    float c = cos(radians);

    float newX = x * c - y * s;
    float newY = x * s + y * c;

    x = newX;
    y = newY;

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

const float& Vector2::operator[] (int index) const
{
    if (index == 0)
        return x;
    if (index == 1)
        return y;

    std::stringstream ss;
    ss << "Index out of bounds: " << index << " size: 2";
    throw std::out_of_range(ss.str());
}

float& Vector2::operator[] (int index)
{
    if (index == 0)
        return x;
    if (index == 1)
        return y;

    std::stringstream ss;
    ss << "Index out of bounds: " << index << " size: 2";
    throw std::out_of_range(ss.str());
}

Vector2& Vector2::operator += (const Vector2& other)
{
	x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator -= (const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2& Vector2::operator *= (float c)
{
	x *= c;
	y *= c;
	return *this;
}

Vector2& Vector2::operator /= (float c)
{
	x /= c;
    y /= c;
    return *this;
}

Vector2 Vector2::operator -(void) const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator +(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator -(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator *(float c) const
{
	return Vector2(x*c, y*c);
}

Vector2 fun::math::operator*(float scalar, const Vector2& vector)
{
	return vector * scalar;
}

Vector2 Vector2::operator /(float c) const
{
	return Vector2(x/c, y/c);
}

bool Vector2::operator ==(const Vector2& other) const
{
	return equals(x, other.x) && equals(y, other.y);	
}

bool Vector2::operator !=(const Vector2& other) const
{
	return !(*this == other);	
}

float Vector2::dot(const Vector2& other) const
{
    return x * other.x + y * other.y;
}

float Vector2::relativeAngleBetween(const Vector2 v2) const
{
	return angle() - v2.angle();
}

std::ostream& fun::math::operator<<(std::ostream& output, const Vector2& p)
{
	output << "(" << p.x << "," << p.y << ")";
	return output;
}
