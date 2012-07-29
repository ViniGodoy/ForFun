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
#if !defined(__VECTOR3_HPP__)
#define __VECTOR3_HPP__

#include <iostream>

#include "MathUtil.hpp"

namespace fun {
namespace math {
    /**
        This class represents a 3 coordinate space mathematical vector.
        All operations expected for a vector, like sum, subtraction, product,
        cross product, dot product and normalization are provided.

		Also, a set of useful functions are also provided, to more complex operations
		like reflex, truncation, distance. 
    */
    class Vector3
    {
		private:
			float v[3];

			Vector3& rotateTwoAxis(int a0, int a1, float radians);
		public:
			/** Creates a new null vector 3D */
			explicit Vector3();

			/** Create a new vector 3D based on the given values.
			@param _x x coordinate
			@param _y y coordinate
			@param _z z coordinate
			*/
			explicit Vector3(float _x, float _y, float _z = 1.0f);

			/**
				Creates a new Vector3 from the given array. The coordinates
				will be mapped as following. Index 0 as x, index 1 as y and
				index 2 as z
				@param xyz An array containing the x, y, z coordinates
			*/
			explicit Vector3(float xyz[3]);

			/** Gets the x coordinate */
			inline float x() const { return v[0]; }			

			/** Gets the red color component */
			inline float r() const { return v[0]; }			

			/** Gets the y coordinate */
			inline float y() const { return v[1]; }

			/** Gets the green color component */
			inline float g() const { return v[1]; }			

			/** Gets the z coordinate */
			inline float z() const { return v[2]; }

			/** Gets the blue color component */
			inline float b() const { return v[2]; }

			/** Sets the x coordinate */
			inline void setX(float x) { v[0] = x; }

			/** Sets the red color component */
			inline void setR(float r) { v[0] = r; }

			/** Sets the y coordinate */
			inline void setY(float y) { v[1] = y; }

			/** Sets the green color component */
			inline void setG(float g) { v[1] = g; }

			/** Sets z coordinate */
			inline void setZ(float z) { v[2] = z; }

			/** Sets the blue color component */
			inline void setB(float b) { v[2] = b; }


			/**
				Sets the x, y and z coordinates in one single operation.

				@param _x The x coordinate
				@param _y The y coordinate
				@param _z The z coordinate
				@return This own vector is returned, for invocation chaning.
			*/
			Vector3& set(float _x, float _y, float _z);

			/**
				Sets the x, y and z coordinates in one single operation. The
				coordinates will be mapped as following. Array index 0 as x,
				index 1 as y and index 2 as z

				@param xyz An array containing the x, y, z coordinates
				@return This own vector is returned, for invocation chaning.
			*/
			Vector3& set(const float xyz[3]);

			/**
				Allows write access to the vector coordinates as if was
				an array containing the x in index 0, y in index 1
				and z in index 2. No bounds check are made, so be careful.
				@param index The coordinate index. As descrived above.
			*/
			inline float& operator [](int index) { return v[index]; }

			/**
				Allows read access to the vector coordinates as if was
				an array containing the x in index 0, y in index 1
				and z in index 2. No bounds check are made, so be careful.
				@param k The coordinate index. As descrived above.
			*/
			inline const float& operator [](int index) const { return v[index]; }

			/** Assignment operator. z will be assigned to 0. */
			Vector3& operator +=(const Vector3& other);

			/** Subtracts this Vector3 from the given vector */
			Vector3& operator -=(const Vector3& other);

			/** Multiplies this vector by the given scalar constant. */
			Vector3& operator *=(float c);

			/** Multiplies each element of this vector by each corresponding 
			element in the other vector.*/
			Vector3& operator *=(const Vector3& other);

			/** Divides this vector by the given vector */
			Vector3& operator /=(float c);

			/** Creates a new Vector that is the negation of this one. */
			Vector3 operator -(void) const;

			/** Creates a new vector with the sum of this and the given one.*/
			Vector3 operator +(const Vector3& other) const;

			/** Creates a new vector with the subtraction of this and the given
				one.*/
			Vector3 operator -(const Vector3& other) const;

			/** Creates a new vector with the product of this vector and the given
				scalar constant.*/
			Vector3 operator *(float c) const;

			/** Creates a new vector with the division of this vector and the given
				scalar constant.*/
			Vector3 operator /(float c) const;

			/** Creates a new vector with the product of this vector and the given one.*/
			Vector3 operator *(const Vector3& other) const;

			/** Test if two vectors are equal */
			bool operator ==(const Vector3& other) const;

			/** Test if two vectors are different */
			bool operator !=(const Vector3& other) const;
				
			/** @return the size (magnitude) of this vector squared */
			float sizeSqr() const;

			/** @return the size (magnitude) of this vector */
			float size() const;

			/** Changes this vector size */
			Vector3& resize(float size);

			/** Apply a cross product in this vector with the given vector.
				@param other The vector that will be used in the cross product.
				@return This own vector, modified by the cross product,
						for invocation chaning.
			*/
			Vector3& cross(const Vector3& other);

			/**
				Applies the dot product of this vector and the other one.
				@return The dot product.
			*/
			float dot(const Vector3& other) const;

			/**
				Creates a new vector that is a normalized version of this one.            
			*/
			Vector3& normalize();

			/**
				Rotates this vector around the x axis.
				@return This own vector is returned, for invocation chaning.
			*/
			
			inline Vector3& rotateX(float radians) { return rotateTwoAxis(1, 2, radians); }

			/**
				Rotates this vector around the y axis.
				@return This own vector is returned, for invocation chaning.
			*/
			inline Vector3& rotateY(float radians) { return rotateTwoAxis(2, 0, radians); }

			/**
				Rotates this vector around the z axis.
				@return This own vector is returned, for invocation chaning.
			*/
			inline Vector3& rotateZ(float radians) { return rotateTwoAxis(0, 1, radians); }

			/**
				Rotates this vector around the given axis.
				@return This own vector is returned, for invocation chaning.
			*/
			Vector3& rotateAxis(float radians, const Vector3& axis);

			/**
			* Returns true if it's the zero vector (size == 0)
			*/
			bool isZero() const;

			/**
			* Returns true if it's a unit vector (size == 1)
			*/
			inline bool isUnit() const { return equals(size(), 1); }

			/**
			 * Return his vector dimension, 3
			 */
			inline int dim() const { return 3; }

			/**
			 * Swaps the contents of both vectors
			 */
			void swap(Vector3& other);
		};

		Vector3 operator*(float scalar, const Vector3& vector);

		inline float distanceSqr(const Vector3& p1, const Vector3& p2)
		{
			return (p1 - p2).sizeSqr();
		}

		inline float distance(const Vector3& p1, const Vector3& p2)
		{
			return (p1 - p2).size();
		}

		/**
		 * Test if two vectors are orthogonal to each other.
		 * Two vector are orthogonal if the angle between than is 90º or if any 
		 * them is the zero vector.
		 * @return True if they are orthogonal.
		 */
		inline bool areOrthogonal(const Vector3& a, const Vector3& b)
		{
			return equals(a.dot(b), 0);
		}

		inline Vector3 rotateX(const Vector3& v, float radians)
		{
			return Vector3(v).rotateX(radians);
		}

		inline Vector3 rotateY(const Vector3& v, float radians)
		{
			return Vector3(v).rotateY(radians);
		}

		inline Vector3 rotateZ(const Vector3& v, float radians)
		{
			return Vector3(v).rotateZ(radians);
		}

		inline Vector3 cross(Vector3 v1, Vector3 v2)
		{
			return Vector3(v1).cross(v2);
		}

		inline Vector3& rotateAxis(const Vector3& v, float radians, const Vector3& axis)
		{
			return Vector3(v).rotateAxis(radians, axis);
		}

		inline Vector3 resize(const Vector3& v, float size)
		{
			return Vector3(v).resize(size);
		}

		inline math::Vector3 truncate(const math::Vector3& v, float size)
		{					
			return (v.sizeSqr() > size * size) ? resize(v, size) : v;
		}

		inline Vector3 normalize(const Vector3& v) 
		{ 
			return Vector3(v).normalize(); 
		}

		inline Vector3 reflect(const Vector3& ray, const Vector3& normal) 
		{
			return ray - 2 * ray.dot(normal) * normal;
		}

		std::ostream& operator<<(std::ostream& output, const Vector3& p);

		/** 
		* Guarantee that all color components will be in 0-1 range.
		*/
		Vector3 saturate(const Vector3& color);

		Vector3 barycenter2d(int x0, int y0, int x1, int y1, int x2, int y2, int px, int py);
}}

namespace std
{
	template<>
	inline void swap<fun::math::Vector3>(fun::math::Vector3& one, fun::math::Vector3& two)
	{
		one.swap(two);
	}
}
#endif // Vector3_H_INCLUDED
