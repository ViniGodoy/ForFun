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

#if !defined(__COLOR_HPP__)
#define __COLOR_HPP__

#include "../Math/Vector4.hpp"

namespace fun {
namespace render {
	/**
	 * Represents an ARGB color value.
	 */
	union Color
	{
		struct 
		{	
			unsigned char a;
			unsigned char r;
			unsigned char g;
			unsigned char b;						
		};
		unsigned char argb[4];
		unsigned value;

		/**
		 * Default constructor. 
		 * Creates a black pixel (r=g=b=0, a=255).
		 */
		Color() : r(0), g(0), b(0), a(255) {}

		/**
		 * Creates a color with the given color.
		 *
		 * @param _value The color value in ARGB byte order.
		 */
		explicit Color(unsigned _value) : value(_value) {}

		/**
		 * Creates a color with the given color components. The constructor
		 * parameter order is RGBA for convenience, but the created color
		 * value will still be in ARGB byte order.
		 *
		 * @param _r Red color component.
		 * @param _g Green color component.
		 * @param _b Blue color component.
		 * @param _a Alpha color component (defaults to 255).
		 */
		Color(unsigned char _r, unsigned char _g, unsigned char _b, 
			unsigned char _a=255) : r(_r), g(_g), b(_b), a(_a) {}

		/**
		 * Creates a color with the given color.
		 *
		 * @param _value The color value in ARGB byte order.
		 */
		Color(unsigned char _argb[4]) 
		{
			for (int i = 0; i < 4; i++) argb[i] = _argb[i];			
		}

		/**
		 * Creates a color from the given vector.
		 */
		explicit Color(const math::Vector4& color);

		/**
		 * Creates a vector from the given color.
		 */
		math::Vector4 toVector() const;
	};
}
}
#endif