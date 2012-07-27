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
#include "Transform2D.hpp"

using namespace fun::math;

#pragma region Right hand

Vector3 rh::transform2d(const Matrix3& matrix, Vector3& vector)
{
	return Vector3(
		vector.x() * matrix(0,0) + vector.y() * matrix(0,1) + vector.z() * matrix(0,2),
		vector.x() * matrix(1,0) + vector.y() * matrix(1,1) + vector.z() * matrix(1,2),
		vector.x() * matrix(2,0) + vector.y() * matrix(2,1) + vector.z() * matrix(2,2));
}

Vector2 rh::transform2d(const Matrix3& matrix, Vector2& vector, float z)
{
	return Vector2(
		vector.x() * matrix(0,0) + vector.y() * matrix(0,1) + z * matrix(0,2),
		vector.x() * matrix(1,0) + vector.y() * matrix(1,1) + z * matrix(1,2));
}

Matrix3 rh::newRotation2d(float radians)
{
	float sina = sin(radians);
	float cosa = cos(radians);

	return Matrix3(
		 cosa,  sina, 0,
		 -sina, cosa, 0,
		 0,     0,   1);
}

Matrix3 rh::newScale2d(float scalex, float scaley)
{
	return Matrix3(
		scalex,   0,   0,
		  0,   scaley, 0,
		  0,     0,    1);
}

Matrix3 rh::newTranslation2d(float x, float y)
{
	return Matrix3(
		1, 0, x,
		0, 1, y,
		0, 0, 1);
}

#pragma endregion

#pragma region Left hand

Vector3 lh::transform2d(const Matrix3& matrix, Vector3& vector)
{
	return Vector3(
		matrix(0,0) * vector.x() + matrix(0,1) * vector.y() + matrix(0,2) * vector.z(),
		matrix(1,0) * vector.x() + matrix(1,1) * vector.y() + matrix(1,2) * vector.z(),
		matrix(2,0) * vector.x() + matrix(2,1) * vector.y() + matrix(2,2) * vector.z());
}

Vector2 lh::transform2d(const Matrix3& matrix, Vector2& vector, float z)
{
	return Vector2(
		matrix(0,0) * vector.x() + matrix(0,1) * vector.y() + matrix(0,2) * z,
		matrix(1,0) * vector.x() + matrix(1,1) * vector.y() + matrix(1,2) * z);
}

Matrix3 lh::newRotation2d(float radians)
{
	float sina = sin(radians);
	float cosa = cos(radians);

	return Matrix3(
		 cosa, -sina, 0,
		 sina,  cosa, 0,
		 0,     0,   1);
}

Matrix3 lh::newTranslation2d(float x, float y)
{
	return Matrix3(
		1, 0, 0,
		0, 1, 0,
		x, y, 1);

}
#pragma endregion