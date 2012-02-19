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
#ifndef __MATRIX3_H__
#define __MATRIX3_H__

namespace s3d {
namespace math {	
	class Vector3;

	/**
	* Represents a 3x3 matrix.
	* <p>
	* All mathematical methods alter the matrix itself (e.g. myMatrix.inverse()). 
	* Functions, with the same method names, are provided as an copy alternative (e.g. transpose(myMatrix)).
	* <p>
	* This class also provides convenient access methods to retrieve or set the matrix elements as:
	*
	* <pre>
	* [a b c]
	* [d e f]
	* [g h k]
	* </pre>
	*
	* These methods are named {@link #a()}, {@link #b()}, {@link #c()}, {@link #d()}, {@link #e()},
	* {@link #f()}, {@link #g()}, {@link #h()} and {@link #k()}.
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

			/**
			* Change the value of the element in the given row and column
			*
			* @param row The row
			* @param col The column
			* @param value The value to set.
			* @return This matrix.
			*/
			inline Matrix3& set(int row, int col, float value)
			{
				A[row][col] = value;
				return *this;
			}

			Matrix3& set(
				float a, float b, float c,
				float d, float e, float f,
				float g, float h, float k);
			/**
			* Returns the "a" element in the following mapping:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* @return the A[0][0] element.
			*/
			inline float a() const { return A[0][0]; }
			/**
			* Returns the "b" element in the following mapping:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* @return the A[0][1] element.
			*/
			inline float b() const { return A[0][1]; }

			/**
			* Returns the "c" element in the following mapping:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* @return the A[0][2] element.
			*/
			inline float c() const { return A[0][2]; }

			/**
			* Returns the "d" element in the following mapping:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* @return the A[1][0] element.
			*/
			inline float d() const { return A[1][0]; }

			/**
			* Returns the "e" element in the following mapping:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* @return the A[1][1] element.
			*/
			inline float e() const { return A[1][1]; }

			/**
			* Returns the "e" element in the following mapping:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* @return the A[1][1] element.
			*/
			inline float f() const { return A[1][2]; }

			/**
			* Returns the "g" element in the following mapping:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* @return the A[2][0] element.
			*/
			inline float g() const { return A[2][0]; }

			/**
			* Returns the "h" element in the following mapping:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* @return the A[2][1] element.
			*/
			inline float h() const { return A[2][1]; }

	
			/**
			* Returns the "k" element in the following mapping:
			*
			* <pre>
			* [a b c]
			* [d e f]
			* [g h k]
			* </pre>
			*
			* @return the A[2][2] element.
			*/
			inline float k() const { return A[2][2]; }

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
			* Inverses this matrix. Not all matrices are invertible, so check the {@link #isInvertible()} method prior to
			* calling this method if you are not sure if you can inverse this matrix or not.
			*
			* <pre>
			* this * inverse = identity
			* </pre>
			*
			* @return This matrix, after inversion. If the matrix is not invertible, the result will be undefined.
			* @see #isInvertible()
			* @see #inverse()
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
}}
#endif
