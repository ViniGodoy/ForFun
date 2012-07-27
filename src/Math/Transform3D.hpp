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
#if !defined(__TRANSFORM_3D_HPP__)
#define __TRANSFORM_3D_HPP__

#include "Vector4.hpp"
#include "Vector3.hpp"
#include "Matrix4.hpp"

namespace fun {
namespace math {
	namespace rh {
		Vector4 transform3d(const Matrix4& matrix, const Vector4& vector);
		Vector3 transform3d(const Matrix4& matrix, const Vector3& vector, float w=1.0f);

		/**
		* Creates a right hand counter-clockwise rotation affine transformation
		* over the x axis
		*/
		Matrix4 newRotationX(float radians);

		/**
		* Creates a right hand counter-clockwise rotation affine transformation 
		* over the y axis
		*/
		Matrix4 newRotationY(float radians);

		/**
		* Creates a right hand counter-clockwise rotation affine transformation 
		* over the z axis
		*/
		Matrix4 newRotationZ(float radians);


		/**
		* Creates a right hand scale affine transformation
		*/
		Matrix4 newScale3d(float scalex, float scaley, float scalez);

		/**
		* Creates a right hand scale affine transformation
		*/
		inline Matrix4 newScale3d(float scale) 
		{
			return newScale3d(scale, scale, scale);
		}

		/**
		* Creates a right hand translation affine transformation
		*/
		Matrix4 newTranslation3d(float x, float y, float z);

		inline Matrix4 newTranslation3d(const Vector3& pos)
		{
			return newTranslation3d(pos.x(), pos.y(), pos.z());
		}

		/**
		 * Creates a new look at matrix.
		 */
		Matrix4 newLookAt(const Vector3& position, const Vector3& target, const Vector3& up);		

		/**
		 * Creates an orthogonal projection matrix
		 */
		Matrix4 newOrthogonal(float w, float h, float near, float far);

		/**
		 * Creates a right-handed perspective projection matrix based on a field of view (FOV).
		 */
		Matrix4 newFovPerspective(float fovy, float aspect, float near, float far);
	}

	namespace lh
	{
		Vector4 transform3d(const Matrix4& matrix, const Vector4& vector);
		Vector3 transform3d(const Matrix4& matrix, const Vector3& vector, float w=1.0f);

		/**
		* Creates a left hand counter-clockwise rotation affine transformation
		* over the x axis
		*/
		Matrix4 newRotationX(float radians);

		/**
		* Creates a left hand counter-clockwise rotation affine transformation 
		* over the y axis
		*/
		Matrix4 newRotationY(float radians);

		/**
		* Creates a left hand counter-clockwise rotation affine transformation 
		* over the z axis
		*/
		Matrix4 newRotationZ(float radians);


		/**
		* Creates a left hand scale affine transformation
		*/
		inline Matrix4 newScale3d(float scalex, float scaley, float scalez)
		{
			return rh::newScale3d(scalex, scaley, scalez);
		}

		/**
		* Creates a left hand scale affine transformation
		*/
		inline Matrix4 newScale3d(float scale)
		{
			return rh::newScale3d(scale, scale, scale);
		}

		/**
		* Creates a left hand scale affine transformation
		*/
		Matrix4 newTranslation3d(float x, float y, float z);

		inline Matrix4 newTranslation3d(const Vector3& pos)
		{
			return lh::newTranslation3d(pos.x(), pos.y(), pos.z());
		}

		/**
		 * Creates a new look at matrix.
		 */
		Matrix4 newLookAt(const Vector3& position, const Vector3& target, const Vector3& up);

		/**
		* Creates an orthogonal projection matrix
		*/
		Matrix4 newOrthogonal(float w, float h, float near, float far);

		/**
		* Creates a right-handed perspective projection matrix based on a field of view (FOV).
		*/
		Matrix4 newFovPerspective(float fovy, float aspect, float near, float far);
	}
}}
#endif