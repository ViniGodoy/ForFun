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
#ifndef __AFFINE_TRANSFORM_HPP__
#define __AFFINE_TRANSFORM_HPP__

#include "Vector2.hpp"
#include "Matrix3.hpp"

namespace s3d {
namespace math {
	namespace rh {
		Vector2 transform(const Matrix3 matrix, Vector2& vector, float z=1.0f);

		/**
		* Creates a 2D right hand counter-clockwise rotation affine 
		* transformation
		*/
		Matrix3 newAffineRotation(float radians);


		/**
		* Creates a 2D right hand scale affine transformation
		*/
		Matrix3 newAffineScale(float scalex, float scaley);

		/**
		* Creates a 2D right hand scale affine transformation
		*/
		inline Matrix3 newAffineScale(float scale) 
		{
			return newAffineScale(scale, scale);
		}

		/**
		* Creates a 2D right hand scale affine transformation
		*/
		Matrix3 newAffineTranslation(float x, float y);

		inline Matrix3 newAffineTranslation(const Vector2& pos)
		{
			return newAffineTranslation(pos.x, pos.y);
		}
	}

	namespace lh
	{
		Vector2 transform(const Matrix3 matrix, Vector2& vector, float z=1.0f);

		/**
		* Creates a 2D left hand clockwise rotation affine transformation
		*/
		inline Matrix3 newAffineRotation(float radians)
		{
			return rh::newAffineRotation(radians);
		}

		/**
		* Creates a 2D left hand scale affine transformation
		*/
		inline Matrix3 newAffineScale(float scalex, float scaley)
		{
			return rh::newAffineScale(scalex, scaley);
		}

		/**
		* Creates a 2D left hand scale affine transformation
		*/
		inline Matrix3 newAffineScale(float scale)
		{
			return rh::newAffineScale(scale, scale);
		}

		/**
		* Creates a 2D left hand scale affine transformation
		*/
		Matrix3 newAffineTranslation(float x, float y);

		inline Matrix3 newAffineTranslation(const Vector2& pos)
		{
			return lh::newAffineTranslation(pos.x, pos.y);
		}
	}
}}
#endif