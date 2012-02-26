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
#if !defined(__VECTOR4_HPP__)
#define __VECTOR4_HPP__

#include <iostream>
#include "MathUtil.hpp"

namespace fun {
namespace math {
	/**
		This class represents a 4 coordinate space mathematical vector.
		All operations expected for a vector, like sum, subtraction, product,
		dot product and normalization are provided.
	*/
	class Vector4
	{
		private:
			float v[4];
		public:
			/** Builds a NULL vector */
			Vector4();
			/** Builds a vector based in it's x and y components */
			explicit Vector4(float aX, float anY, float anZ, float anW=1.0f);

			/** Builds a vector based in a two dimensional array */
			explicit Vector4(float xy[4]);

			/** Builds a vector based in it's size (magnitude) and angle 
			with x axis (counter-clockwise) */
			static Vector4 newBySizeAngle(float size, float radians);

			/** Changes the x and y values */
			Vector4& set(float x, float y, float z, float w);

			/** Changes the x and y values */
			Vector4& set(const Vector4& other);

			/** Changes the x and y values */
			Vector4& set(const float xy[4]);

			/** Retrieves the size of this vector squared */
			float sizeSqr() const;

			/** Retrieves this vector magnitude */
			float size() const;

			/** Sets this vector size */
			Vector4& resize(float size);

			/** Sets this vector size to 1. */
			Vector4& normalize();

			/** Adds this vector to another vector */
			Vector4& operator += (const Vector4& other);

			/** Subtracts this vector from another vector */
			Vector4& operator -= (const Vector4& other);

			/** Multiplies the magnitude of this vector to a constant */
			Vector4& operator *= (float c);

			/** Multiplies each element of this vector by it's corresponding element in the other */
			Vector4& operator *= (const Vector4& other);

			/** Divides this vector magnitude by a constant*/
			Vector4& operator /= (float c);

			/** Negates this vector.
			* Same as rotating the vector in 180� but much faster. */
			Vector4 operator -(void) const;
			Vector4 operator +(const Vector4& other) const;
			Vector4 operator -(const Vector4& other) const;

			Vector4 operator *(float c) const;
			Vector4 operator *(const Vector4& other);
			Vector4 operator /(float c) const;

			inline const float& operator[] (int index) const { return v[index]; }
			inline float& operator[] (int index) { return v[index]; }

			bool operator ==(const Vector4& other) const;
			bool operator !=(const Vector4& other) const;			
			
			/**
			* Returns the dot product between this vector and the other one.
			*/
			float dot(const Vector4& other) const;

			/**
			* Returns true if it's the zero vector (size == 0)
			*/
			bool isZero() const;

			/**
			* Returns true if it's a unit vector (size == 1)
			*/
			inline bool isUnit() const { return equals(size(), 1); }

			/**
			 * Return his vector dimension, 4
			 */
			inline int dim() const { return 4; }
	};

	Vector4 operator*(float scalar, const Vector4& vector);

	/**
		* @return the squared distance between two vectors
		* @see distance
		*/
	inline float distanceSqr(const Vector4& p1, const Vector4& p2)
	{
		return (p1 - p2).sizeSqr();
	}

	/**
		* @return the distance between two vectors
		* @see distanceSqr
		*/
	inline float distance(const Vector4& p1, const Vector4& p2)
	{
		return (p1 - p2).size();
	}
	
	/**
		* Test if two vectors are orthogonal to each other.
		* Two vector are orthogonal if the angle between than is 90� or if any 
		* them is the zero vector.
		* @return True if they are orthogonal.
		*/
	inline bool areOrthogonal(const Vector4& a, const Vector4& b)
	{
		return equals(a.dot(b), 0);
	}

	/**
	* @return a resized copy of v.
	*/
	inline Vector4 resize(const Vector4& v, float size)
	{
		return Vector4(v).resize(size);
	}

	/**
	* @param v A vector
	* @param size Maximum size of the returning vector
	* 
	* @return If the size if v is greater than size, returns
	* a resized version of v with the specified size. Otherwise
	* just return a copy of v.
	*/
	inline Vector4 truncate(const math::Vector4& v, float size)
	{					
		return (v.sizeSqr() > size * size) ? resize(v, size) : v;
	}

	/**
	* @return a normalized copy of the given vector
	*/
	inline Vector4 normalize(const Vector4& v) 
	{ 
		return Vector4(v).normalize(); 
	}

	std::ostream& operator<<(std::ostream& output, const Vector4& p);
}}
#endif