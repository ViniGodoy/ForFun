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

Matrix4 rh::newLookAt(const Vector3& position, const Vector3& target, const Vector3& up)
{
	Vector3 zaxis = (position - target).normalize();
	Vector3 xaxis = cross(up, zaxis).normalize();
	Vector3 yaxis = cross(zaxis, xaxis);

	float dx = -xaxis.dot(position);
	float dy = -yaxis.dot(position);
	float dz = -zaxis.dot(position);

	return Matrix4(
		xaxis[X], yaxis[X], zaxis[X], 0,
		xaxis[Y], yaxis[Y], zaxis[Y], 0,
		xaxis[Z], yaxis[Z], zaxis[Z], 0,
		      dx,       dy,       dz, 1);
}

Matrix4 rh::newOrthogonal(float w, float h, float near, float far)
{
	float size = far - near;

	return Matrix4(
		2.0f / w,		0.0f,		   0.0f,	0.0f,
			0.0f,	2.0f / h,		   0.0f,	0.0f,
			0.0f,		0.0f,  -1.0f / size,	0.0f,
			0.0f,		0.0f,	near / size,	1.0f);
}

Matrix4 rh::newFovPerspective(float fovy, float aspect, float near, float far)
{
	float h = 1.0f / tan(fovy / 2.0f);
	float w = h * aspect;

	float size = near - far;

	return Matrix4(
		w,		0.0f,			 0.0f,		 0.0f,
	 0.0f,		   h,			 0.0f,		 0.0f,
	 0.0f,		0.0f,		 far/size,		-1.0f,
	 0.0f,		0.0f,	near*far/size,		 0.0f);
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

Matrix4 lh::newLookAt(const Vector3& position, const Vector3& target, const Vector3& up)
{
	Vector3 zaxis = (target - position).normalize();
	Vector3 xaxis = cross(up, zaxis).normalize();
	Vector3 yaxis = cross(zaxis, xaxis);

	float dx = -xaxis.dot(position);
	float dy = -yaxis.dot(position);
	float dz = -zaxis.dot(position);

	return Matrix4(
		xaxis[X], yaxis[X], zaxis[X], 0,
		xaxis[Y], yaxis[Y], zaxis[Y], 0,
		xaxis[Z], yaxis[Z], zaxis[Z], 0,
		      dx,       dy,       dz, 1);
}

Matrix4 lh::newOrthogonal(float w, float h, float near, float far)
{
	float size = far - near;

	return Matrix4(
		2.0f / w,		0.0f,		   0.0f,	0.0f,
			0.0f,	2.0f / h,		   0.0f,	0.0f,
			0.0f,		0.0f,   1.0f / size,	0.0f,
			0.0f,		0.0f,  -near / size,	1.0f);
}


Matrix4 lh::newFovPerspective(float fovy, float aspect, float near, float far)
{
	float h = 1.0f / tan(fovy / 2.0f);
	float w = h * aspect;

	float size = far - near;

	return Matrix4(
		w,		0.0f,			  0.0f,		0.0f,
	 0.0f,		   h,			  0.0f,		0.0f,
	 0.0f,		0.0f,		  far/size,		1.0f,
	 0.0f,		0.0f,	-near*far/size,		0.0f);
}
#pragma endregion