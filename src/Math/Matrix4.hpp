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
#ifndef __MATRIX4_HPP__
#define __MATRIX4_HPP__

#include <iostream>

namespace fun {
namespace math {	
	/**
	* Represents a 4x4 matrix.
	* <p>
	* All mathematical methods alter the matrix itself (e.g. myMatrix.inverse()). 
	* Functions, with the same method names, are provided as an copy alternative (e.g. m = inverse(myMatrix)).
	*
	* @author Vinicius G. Mendonca
	*/
	class Matrix4 
	{
		private:
			float A[4][4];

		public:
			Matrix4();

			Matrix4(float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23,
					float m30, float m31, float m32, float m33);
				
			/**
				* Creates an identity matrix
				*/
			static Matrix4 newIdentity();


			/** Copy constructor */
			Matrix4(const Matrix4& other);

			/** Assignment operator */
			Matrix4& operator=(const Matrix4& other);

			/**
			* Returns the element on the given row and column.
			*
			* @param row The row to retrieve
			* @param col The column to retrieve
			* @return The element value
			*/
			inline float get(int row, int col) const
			{
				return A[row][col];
			}

			Matrix4& set(
				float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33);

			inline float& operator() (int row, int col)
			{
				return A[row][col];
			}

			inline const float& operator() (int row, int col) const
			{
				return A[row][col];
			}

			Matrix4& operator += (const Matrix4& other);
			Matrix4 operator + (const Matrix4& other) const;
			Matrix4& operator -= (const Matrix4& other);
			Matrix4 operator - (const Matrix4& other) const;
			Matrix4& operator *= (const Matrix4& other);
			Matrix4 operator * (const Matrix4& other) const;		
			Matrix4& operator *= (float scalar);
			Matrix4 operator * (float scalar) const;

			bool operator == (Matrix4& other) const;
			bool operator != (Matrix4& other) const;

			/**
				* Calculates and returns the determinant of this matrix.		 
				*/
			float determinant() const;

			/**
			* A matrix is invertible if its determinant is not 0.
			* @return True if this matrix is invertible, false if not. 
			*/
			bool isInvertible() const;

			/**
			* Inverses this matrix. Not all matrices are invertible, so check the {@link #isInvertiblA[1][1]} method prior to
			* calling this method if you are not sure if you can inverse this matrix or not.
			*
			* <pre>
			* this * inverse = identity
			* </pre>
			*
			* @return This matrix, after inversion. If the matrix is not invertible, the result will be undefined.
			* @see #isInvertiblA[1][1]
			* @see #inversA[1][1]
			*/
			Matrix4& inverse();

			/**
			* Transposes this matrix. If this matrix is:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* After transposition it will become:
			*
			* <pre>
			* [a d g]
			* [b e h]
			* [c f k]
			* </pre>
			*
			* @return This matrix.
			*/
			Matrix4& transpose();

	};

	Matrix4 operator *(float scalar, const Matrix4& matrix);
	Matrix4 transpose(const Matrix4& matrix);
	Matrix4 inverse(const Matrix4& matrix);
	std::ostream& operator<<(std::ostream& output, const Matrix4& m);
}}
#endif
