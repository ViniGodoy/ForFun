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
#if !defined(__TRANSFORM_2D_HPP__)
#define __TRANSFORM_2D_HPP__

#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Matrix3.hpp"

namespace fun {
namespace math {
	namespace rh {
		Vector3 transform2d(const Matrix3 matrix, Vector3& vector);
		Vector2 transform2d(const Matrix3 matrix, Vector2& vector, float z=1.0f);

		/**
		* Creates a 2D right hand counter-clockwise rotation affine 
		* transformation
		*/
		Matrix3 newRotation2d(float radians);


		/**
		* Creates a 2D right hand scale affine transformation
		*/
		Matrix3 newScale2d(float scalex, float scaley);

		/**
		* Creates a 2D right hand scale affine transformation
		*/
		inline Matrix3 newScale2d(float scale) 
		{
			return newScale2d(scale, scale);
		}

		/**
		* Creates a 2D right hand scale affine transformation
		*/
		Matrix3 newTranslation2d(float x, float y);

		inline Matrix3 newTranslation2d(const Vector2& pos)
		{
			return newTranslation2d(pos[X], pos[Y]);
		}
	}

	namespace lh
	{
		Vector3 transform2d(const Matrix3 matrix, Vector3& vector);
		Vector2 transform2d(const Matrix3 matrix, Vector2& vector, float z=1.0f);

		/**
		* Creates a 2D left hand clockwise rotation affine transformation
		*/
		Matrix3 newRotation2d(float radians);

		/**
		* Creates a 2D left hand scale affine transformation
		*/
		inline Matrix3 newScale2d(float scalex, float scaley)
		{
			return rh::newScale2d(scalex, scaley);
		}

		/**
		* Creates a 2D left hand scale affine transformation
		*/
		inline Matrix3 newScale2d(float scale)
		{
			return rh::newScale2d(scale, scale);
		}

		/**
		* Creates a 2D left hand scale affine transformation
		*/
		Matrix3 newTranslation2d(float x, float y);

		inline Matrix3 newTranslation2d(const Vector2& pos)
		{
			return lh::newTranslation2d(pos[X], pos[Y]);
		}
	}
}}
#endif