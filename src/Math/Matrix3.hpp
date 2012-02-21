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
#if !defined(__MATRIX3_HPP__)
#define __MATRIX3_HPP__

#include <iostream>

namespace fun {
namespace math {	
	/**
	* Represents a 3x3 matrix.
	* <p>
	* All mathematical methods alter the matrix itself (e.g. myMatrix.inverse()). 
	* Functions, with the same method names, are provided as an copy alternative (e.g. m = inverse(myMatrix)).
	*
	* @author Vinicius G. Mendonca
	*/
	class Matrix3 
	{
		private:
			float A[3][3];

		public:
			Matrix3();

			Matrix3(float a, float b, float c, 
					float d, float e, float f, 
					float g, float h, float k);			
				
			/**
				* Creates an identity matrix
				*/
			static Matrix3 newIdentity();


			/** Copy constructor */
			Matrix3(const Matrix3& other);

			/** Assignment operator */
			Matrix3& operator=(const Matrix3& other);

			Matrix3& set(
				float a, float b, float c,
				float d, float e, float f,
				float g, float h, float k);

			inline float& operator() (int row, int col)
			{
				return A[row][col];
			}

			inline const float& operator() (int row, int col) const
			{
				return A[row][col];
			}

			Matrix3& operator += (const Matrix3& other);
			Matrix3 operator + (const Matrix3& other) const;
			Matrix3& operator -= (const Matrix3& other);
			Matrix3 operator - (const Matrix3& other) const;
			Matrix3& operator *= (const Matrix3& other);
			Matrix3 operator * (const Matrix3& other) const;		
			Matrix3& operator *= (float scalar);
			Matrix3 operator * (float scalar) const;

			bool operator == (Matrix3& other) const;
			bool operator != (Matrix3& other) const;

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
			Matrix3& inverse();

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
			Matrix3& transpose();

	};

	Matrix3 operator *(float scalar, const Matrix3& matrix);

	Matrix3 transpose(const Matrix3& matrix);
	Matrix3 inverse(const Matrix3& matrix);
	std::ostream& operator<<(std::ostream& output, const Matrix3& m);
}}
#endif
