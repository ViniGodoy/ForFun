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
#include <algorithm>
#include "../Math/Vector4.hpp"

#if !defined(__PIXELBUFFER_HPP__)
#define __PIXELBUFFER_HPP__

struct SDL_Surface;

namespace fun {
namespace render {
	class SwapChain;
	
	/**
	 * Represents a buffer of pixels.
	 */
	class PixelBuffer
	{
		private:
			SDL_Surface* surface;
			PixelBuffer(SDL_Surface* _surface);			
			unsigned colorToUnsigned(const math::Vector4& color);
			PixelBuffer& set(int x, int y, unsigned color);
		
		public:		
			friend class SwapChain;

			/**
			 * Creates a new ARGB Pixel Buffer with the given width and height 
			 */
			PixelBuffer(int w, int h);

			/**
			 * Copy constructor.
			 * @param other The pixel buffer to copy
			 */
			PixelBuffer(const PixelBuffer& other);

			/**
			 * Assigment operator.
			 * Assigning over the video pixel buffer will only blit the other,
			 * buffer, otherwise the buffer gets copied.
			 */
			PixelBuffer& operator =(const PixelBuffer& other);
			
			/**
			 * Direct access a given pixel. The color value is in specific 
			 * pixel buffer format. 
			 */
			const math::Vector4 operator() (int x, int y) const;

			/**
			 * Sets the value of the given pixel to the given color.
			 * Does not blend colors, even if alpha != 0.
			 */
			PixelBuffer& set(int x, int y, const math::Vector4& color);

			/**
			 * Retrieves the color of a given pixel.
			 */
			inline math::Vector4 get(int x, int y) const 
			{ 
				return (*this)(x,y); 
			}

			/**
			 * Draws a flat line.
			 */
			inline void drawLine(int x0, int y0, 
				int x1, int y1, const fun::math::Vector4& color)
			{
				drawLine(x0, y0, color, x1, y1, color);
			}

			/**
			 * Draws a line.
			 */
			void drawLine(
				int x0, int y0, const fun::math::Vector4& color0,
				int x1, int y1, const fun::math::Vector4& color1);

			/**
			 * Draws a flat triangle
			 */
			void drawTriangle(int x0, int y0,
				int x1, int y1,
				int x2, int y2, 
				const math::Vector4& color);

			/**
			 * Draws a triangle
			 */
			void drawTriangle(
				int x0, int y0, const fun::math::Vector4& color0,
				int x1, int y1, const fun::math::Vector4& color1,
				int x2, int y2, const fun::math::Vector4& color2);

			/**
			 * Returns this buffer width.
			 */
			const int& width() const;

			/**
			 * Returns this buffer height.
			 */
			const int& height() const;

			inline void swap(PixelBuffer& other) 
			{				
				std::swap(surface, other.surface);
			}

			/**
			 * Releases this buffer.
			 */
			~PixelBuffer();
	};
}}

namespace std
{
	template<>
	inline void swap<fun::render::PixelBuffer>(fun::render::PixelBuffer& one, fun::render::PixelBuffer& two)
	{
		one.swap(two);
	}
}
#endif
