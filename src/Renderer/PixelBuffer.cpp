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

#include "PixelBuffer.hpp"
#include "SDL.h"
#include <algorithm>

using namespace fun::render;

PixelBuffer::PixelBuffer(SDL_Surface* _surface)
	: surface(_surface)
{
}

PixelBuffer::PixelBuffer(int w, int h)
{
	SDL_PixelFormat *vf = SDL_GetVideoInfo()->vfmt;
	surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
		0xFF0000, 0xFF00, 0xFF, 0xFF000000);
}

PixelBuffer::PixelBuffer(const PixelBuffer& other)
{
	surface = SDL_ConvertSurface(other.surface, other.surface->format, other.surface->flags);
}

PixelBuffer& PixelBuffer::operator =(const PixelBuffer& other)
{
	if (this == &other) return *this;
	if (surface == SDL_GetVideoSurface())
		SDL_BlitSurface(other.surface, NULL, surface, NULL);
	else
	{
		SDL_FreeSurface(surface);
		surface = SDL_ConvertSurface(other.surface, other.surface->format, other.surface->flags);
	}
	return *this;
}

const unsigned int& PixelBuffer::operator() (int x, int y) const
{
	return ((Uint32*)surface->pixels)[(y * surface->w) + x];
}

unsigned int& PixelBuffer::operator() (int x, int y)
{
	return ((Uint32*)surface->pixels)[(y * surface->w) + x];
}

unsigned PixelBuffer::colorToUnsigned(const Color& color) const
{
	unsigned finalColor = (color.a >> surface->format->Aloss) << surface->format->Ashift;
	finalColor |= (color.r >> surface->format->Rloss) << surface->format->Rshift;
	finalColor |= (color.g >> surface->format->Gloss) << surface->format->Gshift;
	finalColor |= (color.b >> surface->format->Bloss) << surface->format->Bshift;
	return finalColor;
}

Color PixelBuffer::unsignedToColor(const unsigned& pixelColor) const
{
	Color color(0U);
	unsigned int temp = 0;
	unsigned int pixel = *((Uint32*)surface->pixels);

	SDL_PixelFormat* fmt = surface->format;

	/* Get Red component */
	temp = pixelColor & fmt->Rmask;  /* Isolate red component */
	temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
	color.r = static_cast<unsigned char>(temp);

	/* Get Green component */
	temp = pixelColor & fmt->Gmask;  /* Isolate red component */
	temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
	color.g = static_cast<unsigned char>(temp);

	/* Get Blue component */
	temp = pixelColor & fmt->Bmask;  /* Isolate red component */
	temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
	color.b = static_cast<unsigned char>(temp);

	/* Get Alpha component */
	temp = pixelColor & fmt->Amask;  /* Isolate red component */
	temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
	temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
	color.a = static_cast<unsigned char>(temp);
	return color;
}

void PixelBuffer::drawHorizontalLine(unsigned x, unsigned y, unsigned deltaX, unsigned deltaY, int xDir, unsigned color)
{
	int deltaYx2 = static_cast<int>(deltaY * 2);
	int deltaYx2MinusDeltaXx2 = deltaYx2 - static_cast<int>(deltaX * 2);
	int errorTerm = deltaYx2 - static_cast<int>(deltaX);

	(*this)(x, y) = color;
	while (deltaX--)
	{
		if (errorTerm < 0)
			errorTerm += deltaYx2;
		else
		{
			y++;
			errorTerm += deltaYx2MinusDeltaXx2;
		}

		x += xDir;
		(*this)(x, y) = color;
	}
}

void PixelBuffer::drawVerticalLine(unsigned x, unsigned y, unsigned deltaX, unsigned deltaY, int xDir, unsigned color)
{
	int deltaXx2 = static_cast<int>(deltaX * 2);
	int deltaXx2MinusDeltaYx2 = deltaXx2 - static_cast<int>(deltaY * 2);
	int errorTerm = deltaXx2 - static_cast<int>(deltaY);

	(*this)(x, y) = color;
	while (deltaY--)
	{
		if (errorTerm < 0)
			errorTerm += deltaXx2;
		else
		{
			x += xDir;
			errorTerm += deltaXx2MinusDeltaYx2;
		}

		y++;
		(*this)(x, y) = color;
	}
}

void PixelBuffer::drawLine(int x0, int y0, int x1, int y1, const Color& color)
{
	//Make sure y is positive
	if (y0 > y1)
	{
		std::swap(y0, y1);
		std::swap(x0, x1);
	}

	//Calculate deltas, x direction and color
	int deltaX = abs(x1 - x0);
	int deltaY = y1 - y0;
	int xDir = x1 > x0 ? 1 : -1;
	unsigned pixelColor = colorToUnsigned(color);

	if (deltaX > deltaY)
		drawHorizontalLine(x0, y0, deltaX, deltaY, xDir, pixelColor);
	else
		drawVerticalLine(x0, y0, deltaX, deltaY, xDir, pixelColor);
}

const int& PixelBuffer::width() const
{
	return surface->w;
}

const int& PixelBuffer::height() const
{
	return surface->h;
}

PixelBuffer::~PixelBuffer()
{
	if (surface != SDL_GetVideoSurface())
		SDL_FreeSurface(surface);
}
