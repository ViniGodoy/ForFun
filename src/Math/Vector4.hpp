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

			/** Gets the w coordinate */
			inline float w() const { return v[3]; }

			/** Gets the alpha color component */
			inline float a() const { return v[3]; }

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

			/** Sets w coordinate */
			inline void setW(float w) { v[3] = w; }

			/** Sets the alpha color component */
			inline void setA(float a) { v[3] = a; }

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
			* Same as rotating the vector in 180º but much faster. */
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

			/**
			 * Swaps the contents of both vectors
			 */
			void swap(Vector4& other);
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
		* Two vector are orthogonal if the angle between than is 90º or if any 
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

	/** 
    * Guarantee that all color components will be in 0-1 range.
    */
	Vector4 saturate(const Vector4& color);
}}

namespace std
{
	template<>
	inline void swap<fun::math::Vector4>(fun::math::Vector4& one, fun::math::Vector4& two)
	{
		one.swap(two);
	}
}
#endif