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
#include "AffineTransform.hpp"

using namespace fun::math;

#pragma region Right hand

Vector2 rh::transform(const Matrix3 matrix, Vector2& vector, float z)
{
	return Vector2(
		vector.x * matrix.a() + vector.y * matrix.b() + z * matrix.c(),
		vector.x * matrix.d() + vector.y * matrix.e() + z * matrix.f());
}

Matrix3 rh::newAffineRotation(float radians)
{
	float sina = sin(radians);
	float cosa = cos(radians);

	return Matrix3(
		 cosa, -sina, 0,
		 sina,  cosa, 0,
		 0,     0,   1);
}

Matrix3 rh::newAffineScale(float scalex, float scaley)
{
	return Matrix3(
		scalex,   0,   0,
		  0,   scaley, 0,
		  0,     0,    1);
}

Matrix3 rh::newAffineTranslation(float x, float y)
{
	return Matrix3(
		1, 0, x,
		0, 1, y,
		0, 0, 1);
}

#pragma endregion

#pragma region Left hand

Vector2 lh::transform(const Matrix3 matrix, Vector2& vector, float z)
{
	return Vector2(
		matrix.a() * vector.x + matrix.d() * vector.y + matrix.g() * z,
		matrix.b() * vector.x + matrix.e() * vector.y + matrix.h() * z);
}

Matrix3 lh::newAffineTranslation(float x, float y)
{
	return Matrix3(
		1, 0, 0,
		0, 1, 0,
		x, y, 1);

}
#pragma endregion