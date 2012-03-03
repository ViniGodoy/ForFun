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

#if !defined(__PixelBuffer_HPP__)
#define __PixelBuffer_HPP__

struct SDL_Surface;

namespace fun {
namespace render {
	class SwapChain;

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

	};

	/**
	 * Represents a buffer of pixels.
	 */
	class PixelBuffer
	{
		private:
			SDL_Surface* surface;
			PixelBuffer(SDL_Surface* _surface);

			void drawVerticalLine(unsigned x0, unsigned y0, 
				unsigned deltaX, unsigned deltaY, int xDir, unsigned color);

			void drawHorizontalLine(unsigned x0, unsigned y0, 
				unsigned deltaX, unsigned deltaY, int xDir, unsigned color);

			void setDirect(int x, int y, unsigned color);
			
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
			const unsigned int& PixelBuffer::operator() (int x, int y) const;

			/**
			 * Direct access a given pixel. The color value is in specific 
			 * pixel buffer format.  
			 * Does not blend colors, even if alpha != 0.
			 */
			unsigned int& PixelBuffer::operator() (int x, int y);

			/**
			 * Converts the given color to the internal unsigned representation
			 */
			unsigned colorToUnsigned(const Color& color) const;

			/**
			 * Converts the given value to a color, considering the color 
			 * ordering of this buffer.
			 */
			Color unsignedToColor(const unsigned& pixelColor) const;

			/**
			 * Sets the value of the given pixel to the given color.
			 * Does not blend colors, even if alpha != 0.
			 */
			inline void set(int x, int y, const Color& color) 
			{
				(*this)(x, y) = colorToUnsigned(color);
			}

			/**
			 * Retrieves the color of a given pixel.
			 */
			inline Color get(int x, int y) const 
			{ 
				return unsignedToColor((*this)(x,y)); 
			}

			/**
			 * Draws a line.
			 */
			void drawLine(int x0, int y0, int x1, int y1, const Color& color);

			/**
			 * Returns this buffer width.
			 */
			const int& width() const;

			/**
			 * Returns this buffer height.
			 */
			const int& height() const;

			/**
			 * Releases this buffer.
			 */
			~PixelBuffer();
	};
}}

#endif