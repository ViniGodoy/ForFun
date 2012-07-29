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
#if !defined(__MATHUTIL_HPP__)
#define __MATHUTIL_HPP__

#include <cmath>

namespace fun {
namespace math {
	//Exponent and mantissa constants
	//See complete explanation in http://stereopsis.com/sree/fpu2006.html
	#if _FUN_BIG_ENDIAN_
		static const int IEXP = 0;
		static const int IMAN = 1;
	#else
		static const int IEXP = 1;
		static const int IMAN = 0;
	#endif 

	static const double DOUBLE_MAGIC = double(6755399441055744.0); 		//2^52 * 1.5,  uses limited precisicion to floor
	static const double DOUBLE_MAGIC_DELTA = (1.5e-8);					//almost .5f = .5f + 1e^(number of exp bit)
	static const double DOUBLE_MAGIC_ROUND	= (.5f-DOUBLE_MAGIC_DELTA);	//almost .5f = .5f - 1e^(number of exp bit)

	//Other useful constants
	static const double PI = 3.14159265358979323846;
	static const double E = 2.7182818284590452354;
	static const double ONE_DEGREE = 180.0 / PI;    
	static const float FLOAT_DELTA = 0.00001f;
	static const float DOUBLE_DELTA =  0.00000000000001f;

	inline double toDegrees(double angrad)
	{
		return angrad * ONE_DEGREE;
	}

	inline float toDegrees(float angrad)
	{
		return static_cast<float>(angrad * ONE_DEGREE);
	}

	inline float toDegrees(int angrad)
	{
		return toDegrees(static_cast<float>(angrad));
	}

	inline double toRadians(double angdeg)
	{
		return angdeg / ONE_DEGREE;
	}

	inline float toRadians(float angdeg)
	{
		return static_cast<float>(angdeg / ONE_DEGREE);
	}

	inline float toRadians(int angdeg)
	{
		return toRadians(static_cast<float>(angdeg));
	}

	/**
	* Compare if two floats are equals within the given delta tolerance.
	* 
	* @param f1 A float
	* @param f2 Another float
	* @param delta The delta tolerance.
	* @return True if they are equal, false if not.
	*/
	inline static bool equals(float f1, float f2, float delta=FLOAT_DELTA) {    
		return abs(f1 - f2) <= delta;
	}

	/**
	* Compare if two floats are equals within the given delta tolerance.
	* 
	* @param f1 A float
	* @param f2 Another float
	* @param delta The delta tolerance.
	* @return True if they are equal, false if not.
	*/
	inline static bool equals(double f1, double f2, double delta=DOUBLE_DELTA) {
		return abs(f1 - f2) <= delta;
	}

	/**
	* If the value is bigger than 1, returns 1. 
	* If smaller than 0, returns 0.
	*
	* Otherwise returns the value itself.
	*/
	inline float saturate(float value)
	{
		return value > 1.0f ? 1.0f : (value < 0 ? 0 : value);
	}

	/**
	* If the value is bigger than 255, returns 255. 
	* If smaller than 0, returns 0.
	*
	* Otherwise returns the value itself.
	*/
	inline int saturate(int value)
	{
		return value > 255 ? 255 : (value < 0 ? 0 : value);
	}

	/**
	* If the value is bigger than 255, returns 255. 
	*
	* Otherwise returns the value itself.
	*/
	inline unsigned saturate(unsigned value)
	{
		return value > 255 ? 255 : value;
	}

	/**
	 * Round and conversion to int operation.
	 * Float optimizations can be disabled by defining 
	 * _FUN_DISABLE_FLOAT_OPTIMIZATION_ directive.
	 *
	 * See complete explanation in http://stereopsis.com/sree/fpu2006.html
	 */
	inline int roundToInt(double value, double dmr=DOUBLE_MAGIC)
	{
		#ifndef _FUN_DISABLE_FLOAT_OPTIMIZATION_
			value += dmr;
			return ((int*)&value)[IMAN];			
		#else
			return int32(floor(val+.5));
		#endif
	}

	/**
	 * Optimized floor and conversion to int operation
	 * Float optimizations can be disabled by defining 
	 * _FUN_DISABLE_FLOAT_OPTIMIZATION_ directive.
	 *
	 * See complete explanation in http://stereopsis.com/sree/fpu2006.html
	 */
	inline int floorToInt(double value, double dme=DOUBLE_MAGIC_ROUND)
	{
		#ifndef _FUN_DISABLE_FLOAT_OPTIMIZATION_
			return roundToInt(value - dme);
		#else
			return floor(val);
		#endif
	}

	/**
	 * Optimized ceil and conversion to int operation
	 * Float optimizations can be disabled by defining 
	 * _FUN_DISABLE_FLOAT_OPTIMIZATION_ directive.
	 *
	 * See complete explanation in http://stereopsis.com/sree/fpu2006.html
	 */
	inline int ceilToInt(double value, double dme=DOUBLE_MAGIC_ROUND)
	{
		#ifndef _FUN_DISABLE_FLOAT_OPTIMIZATION_
			return roundToInt(value + dme);
		#else
			return ceil(val);
		#endif
	}

	/**
	* Optimized cast operation
	* See complete explanation in http://stereopsis.com/sree/fpu2006.html
	*/
	inline int castToInt(double value, double dme)
	{
		#ifndef _FUN_DISABLE_FLOAT_OPTIMIZATION_
			return value<0 ? roundToInt(value-dme) : roundToInt(value+dme);
		#else
			return static_cast<int>(val);
		#endif
	}

	/**
	 * Calculates the minimum value
	 */
	template <typename T>
	inline T minimum(T a, T b, T c)
	{
		return a < b ? 
			((a < c) ? a : c) :
			((b < c) ? b : c);		
	}

	/**
	 * Calculates the maximum value
	 */
	template <typename T>
	T maximum(T a, T b, T c)
	{
		return a > b ? 
			((a > c) ? a : c) :
			((b > c) ? b : c);		
	}

}}
#endif // MATHUTIL_H_INCLUDED
