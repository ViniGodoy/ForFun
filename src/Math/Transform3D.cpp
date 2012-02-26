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
#include "Transform3D.hpp"

using namespace fun::math;

#pragma region Right hand

Vector4 rh::transform3d(const Matrix4& matrix, Vector4& vector)
{	
	return Vector4(
		vector[X] * matrix(0,0) + vector[Y] * matrix(0,1) + vector[Z] * matrix(0,2) + vector[W] * matrix(0,3),
		vector[X] * matrix(1,0) + vector[Y] * matrix(1,1) + vector[Z] * matrix(1,2) + vector[W] * matrix(1,3),
		vector[X] * matrix(2,0) + vector[Y] * matrix(2,1) + vector[Z] * matrix(2,2) + vector[W] * matrix(2,3),
		vector[X] * matrix(3,0) + vector[Y] * matrix(3,1) + vector[Z] * matrix(3,2) + vector[W] * matrix(3,3));
}

Vector3 rh::transform3d(const Matrix4& matrix, Vector3& vector, float w)
{
	return Vector3(
		vector[X] * matrix(0,0) + vector[Y] * matrix(0,1) + vector[Z] * matrix(0,2) + w * matrix(0,3),
		vector[X] * matrix(1,0) + vector[Y] * matrix(1,1) + vector[Z] * matrix(1,2) + w * matrix(1,3),
		vector[X] * matrix(2,0) + vector[Y] * matrix(2,1) + vector[Z] * matrix(2,2) + w * matrix(2,3));
}

Matrix4 rh::newRotationX(float radians)
{
	float cosa = cos(radians);
	float sina = sin(radians);

	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosa, sina, 0.0f,
		0.0f,-sina, cosa, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 rh::newRotationY(float radians)
{
	float cosa = cos(radians);
	float sina = sin(radians);

	return Matrix4(
		cosa, 0.0f,-sina, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sina, 0.0f, cosa, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 rh::newRotationZ(float radians)
{
	float cosa = cos(radians);
	float sina = sin(radians);

	return Matrix4(
		cosa, sina, 0.0f, 0.0f,
	   -sina, cosa, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}


Matrix4 rh::newScale3d(float sx, float sy, float sz)
{
	return Matrix4(
		sx,  0,  0, 0,
		 0, sy,  0, 0,
		 0,  0, sz, 0,
		 0,  0,  0, 1);
}

Matrix4 rh::newTranslation3d(float x, float y, float z)
{
	return Matrix4(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);
}

#pragma endregion

#pragma region Left hand

Vector4 lh::transform3d(const Matrix4& matrix, Vector4& vector)
{
	return Vector4(
		matrix(0,0) * vector[X] + matrix(0,1) * vector[Y] + matrix(0,2) * vector[Z] + matrix(0,3) * vector[W],
		matrix(1,0) * vector[X] + matrix(1,1) * vector[Y] + matrix(1,2) * vector[Z] + matrix(1,3) * vector[W],
		matrix(2,0) * vector[X] + matrix(2,1) * vector[Y] + matrix(2,2) * vector[Z] + matrix(2,3) * vector[W],
		matrix(3,0) * vector[X] + matrix(3,1) * vector[Y] + matrix(3,2) * vector[Z] + matrix(3,3) * vector[W]);
}

Vector3 lh::transform3d(const Matrix4& matrix, Vector3& vector, float w)
{
	return Vector3(
		matrix(0,0) * vector[X] + matrix(0,1) * vector[Y] + matrix(0,2) * vector[Z] + matrix(0,3) * w,
		matrix(1,0) * vector[X] + matrix(1,1) * vector[Y] + matrix(1,2) * vector[Z] + matrix(1,3) * w,
		matrix(2,0) * vector[X] + matrix(2,1) * vector[Y] + matrix(2,2) * vector[Z] + matrix(2,3) * w);
}

Matrix4 lh::newRotationX(float radians)
{
	float cosa = cos(radians);
	float sina = sin(radians);

	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosa,-sina, 0.0f,
		0.0f, sina, cosa, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

}

Matrix4 lh::newRotationY(float radians)
{
	float cosa = cos(radians);
	float sina = sin(radians);

	return Matrix4(
		cosa, 0.0f, sina, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
	   -sina, 0.0f, cosa, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

}

Matrix4 lh::newRotationZ(float radians)
{
	float cosa = cos(radians);
	float sina = sin(radians);

	return Matrix4(
		cosa,-sina, 0.0f, 0.0f,
	    sina, cosa, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}


Matrix4 lh::newTranslation3d(float x, float y, float z)
{
	return Matrix4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1);
}

#pragma endregion