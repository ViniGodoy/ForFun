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

/* Vinícius Godoy de Mendonça */
#if !defined(__VECTOR2_HPP__)
#define __VECTOR2_HPP__

#include <iostream>
#include "MathUtil.hpp"

namespace fun {
namespace math {
	/**
		This class represents a 2 coordinate space mathematical vector.
		All operations expected for a vector, like sum, subtraction, product,
		dot product and normalization are provided.

		Also, a set of useful functions are also provided, to more complex operations
		like reflex, truncation, distance. Functions also provide a non-mutable version
		of methods.
	*/
	class Vector2
	{
		float v[2];

		public:			
			/** Builds a NULL vector */
			Vector2();
			/** Builds a vector based in it's x and y components */
			explicit Vector2(float aX, float anY);

			/** Builds a vector based in a two dimensional array */
			explicit Vector2(float xy[2]);

			/** Builds a vector based in it's size (magnitude) and angle 
			with x axis (counter-clockwise) */
			static Vector2 newBySizeAngle(float size, float radians);

			/** Gets the x coordinate */
			inline float x() const { return v[0]; }

			/** Gets the y coordinate */
			inline float y() const { return v[1]; }

			/** Sets x coordinate */
			inline void setX(float x) { v[0] = x; }

			/** Sets y coordinate */
			inline void setY(float y) { v[1] = y; }

			/** Changes the x and y values */
			Vector2& set(float x, float y);

			/** Changes the x and y values */
			Vector2& set(const float xy[2]);

			/** Retrieves the size of this vector squared */
			float sizeSqr() const;

			/** Retrieves this vector magnitude */
			float size() const;

			/** Returns the relative angle of the vector in relation to the x
			* axis, in a counter-clockwise rotation. That is, 90 degrees is
			* a vector pointing up and 0 degrees is a vector pointing right. 
			*/
			float angle() const;

			/** Rotates this vector in counter-clockwise direction */
			Vector2& rotate(float radians);

			/** Sets this vector size to 1. */
			Vector2& normalize();

			/** Sets this vector size */
			Vector2& resize(float size);

			/** Adds this vector to another vector */
			Vector2& operator += (const Vector2& other);

			/** Subtracts this vector from another vector */
			Vector2& operator -= (const Vector2& other);

			/** Multiplies the magnitude of this vector to a constant */
			Vector2& operator *= (float c);

			/** Divides this vector magnitude by a constant*/
			Vector2& operator /= (float c);

			/** Negates this vector.
			* Same as rotating the vector in 180º but much faster. */
			Vector2 operator -(void) const;
			Vector2 operator +(const Vector2& other) const;
			Vector2 operator -(const Vector2& other) const;

			Vector2 operator *(float c) const;
			Vector2 operator /(float c) const;

			inline const float& operator[] (int index) const { return v[index]; }
			inline float& operator[] (int index) { return v[index]; }

			bool operator ==(const Vector2& other) const;
			bool operator !=(const Vector2& other) const;			
			
			/**
			* Returns the dot product between this vector and the other one.
			*/
			float dot(const Vector2& other) const;

			/**
			* Return the relative angle between 2 vectors.
			* For normalized vectors, prefer the dot product instead.
			*/
			float relativeAngleBetween(const Vector2 other) const;

			/**
			* Returns true if it's the zero vector (size == 0)
			*/
			bool isZero() const;

			/**
			* Returns true if it's a unit vector (size == 1)
			*/
			inline bool isUnit() const { return equals(size(), 1); }

			/**
			 * Return his vector dimension, 2
			 */
			inline int dim() const { return 2; }

			/**
			 * Swaps the contents of both vectors
			 */
			void swap(Vector2& other);
	};

	Vector2 operator*(float scalar, const Vector2& vector);

	/**
	* @return the squared distance between two vectors
	* @see distance
	*/
	inline float distanceSqr(const Vector2& p1, const Vector2& p2)
	{
		return (p1 - p2).sizeSqr();
	}

	/**
	* @return the distance between two vectors
	* @see distanceSqr
	*/
	inline float distance(const Vector2& p1, const Vector2& p2)
	{
		return (p1 - p2).size();
	}
	
	/**
	* Test if two vectors are orthogonal to each other.
	* Two vector are orthogonal if the angle between than is 90º or if any 
	* them is the zero vector.
	* @return True if they are orthogonal.
	*/
	inline bool areOrthogonal(const Vector2& a, const Vector2& b)
	{
		return equals(a.dot(b), 0);
	}

	/**
	* @return the counter-clockwise perpenticular copy of vector of v. 
	*/
	inline Vector2 perp(const Vector2& v)
	{
		return Vector2(-v.y(), v.x());
	}

	/**
	* @return the dot product between the perpendicular of a and the vector b.
	* @see perp(const Vector2&)
	*/
	inline float perpDot(const Vector2& a, const Vector2& b)
	{
		return perp(a).dot(b);
	}

	/**
	* Returns a clockwise direction rotated copy of v.
	* @param v The vector to rotate
	* @param radians The angle, in radians.
	* @return A rotated copy of v.
	*/
	inline Vector2 rotate(const Vector2& v, float radians)
	{
		return Vector2(v).rotate(radians);
	}

	/**
	* @return a resized copy of v.
	*/
	inline Vector2 resize(const Vector2& v, float size)
	{
		return Vector2(v).resize(size);
	}

	/**
	* @param v A vector
	* @param size Maximum size of the returning vector
	* 
	* @return If the size if v is greater than size, returns
	* a resized version of v with the specified size. Otherwise
	* just return a copy of v.
	*/
	inline Vector2 truncate(const math::Vector2& v, float size)
	{					
		return (v.sizeSqr() > size * size) ? resize(v, size) : v;
	}

	/**
	* @return a normalized copy of the given vector
	*/
	inline Vector2 normalize(const Vector2& v) 
	{ 
		return Vector2(v).normalize(); 
	}

	/**
	* @param ray The ray to reflect
	* @param normal Surface normal
	* @return The reflection vector
	*/
	inline Vector2 reflect(const Vector2& ray, const Vector2& normal) 
	{
		return ray - 2 * ray.dot(normal) * normal;
	}

	std::ostream& operator<<(std::ostream& output, const Vector2& p);
}}

namespace std
{
	template<>
	inline void swap<fun::math::Vector2>(fun::math::Vector2& one, fun::math::Vector2& two)
	{
		one.swap(two);
	}
}
#endif