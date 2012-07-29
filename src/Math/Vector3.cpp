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

Vector3::Vector3(float x, float y, float z)
{
	set(x,y,z);
}

Vector3::Vector3(float xyz[3])
{
	memcpy(v, xyz, sizeof(v));
}

Vector3& Vector3::set(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
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
    return (Vector3(-x(), -y(), -z()));
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
	return set(
		y() * other.z() - z() * other.y(),
		z() * other.x() - x() * other.z(),
		x() * other.y() - y() * other.x()
	);
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

    float nx = x() * (c + k * axis.x() * axis.x()) +
               y() * (k * axis.x() * axis.y() - s * axis.z()) +
               z() * (k * axis.x() * axis.z() + s * axis.y());

    float ny = x() * (k * axis.x() * axis.y() + s * axis.z()) +
               y() * (c + k * axis.y() * axis.y()) +
               z() * (k * axis.y() * axis.z() - s * axis.x());

    float nz = x() * (k * axis.x() * axis.z() - s * axis.y()) +
               y() * (k * axis.y() * axis.z() + s * axis.x()) +
               z() * (c + k * axis.z() * axis.z());

    return set(nx, ny, nz);
}

void Vector3::swap(Vector3& other)
{
	for (int i = 0; i < dim(); ++i)
		std::swap(v[i], other.v[i]);
}

std::ostream& fun::math::operator<<(std::ostream& output, const Vector3& p)
{
	return output << "(" << p.x() << "," << p.y() << "," << p.z() << ")";
}

Vector3 fun::math::saturate(const Vector3& color)
{
	Vector3 v;
	for (int i = 0; i < color.dim(); ++i)
		v[i] = saturate(color[i]);
	return v;
}

Vector3 fun::math::barycenter2d(int x0, int y0, int x1, int y1, int x2, int y2, int px, int py)
{
	int y0y2 = y0 - y2;
	int x1x2 = x1 - x2;
	int y1y2 = y1 - y2;
	int x2x0 = x2 - x0;

	float areaDenom = 1.0f / (y0y2*x1x2+y1y2*x2x0);

	Vector3 b;
	b[0] = ((py - y2)*x1x2 + y1y2*(x2 - px)) * areaDenom;
	b[1] = ((py - y0)*x2x0 + (-y0y2)*(x0 - px)) * areaDenom;
	b[2] = 1.0f - b[0] - b[1];
	return b;
}
