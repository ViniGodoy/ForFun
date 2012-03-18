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

#include "PixelBuffer.hpp"
#include "../Math/Vector4.hpp"

#include "SDL.h"
#include <algorithm>

using namespace fun::render;
using namespace fun::math;

/**
* Creates a color from the given vector.
*/
Color::Color(const Vector4& color)
	: r(static_cast<unsigned char>(saturate(color[R]) * 255)),
	  g(static_cast<unsigned char>(saturate(color[G]) * 255)),
	  b(static_cast<unsigned char>(saturate(color[B]) * 255)),
	  a(static_cast<unsigned char>(saturate(color[A]) * 255))
{
}

/**
* Creates a vector from the given color.
*/
Vector4 Color::toVector() const
{
	return Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

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

void PixelBuffer::drawHorizontalLine(unsigned x, unsigned y,
	unsigned deltaX, unsigned deltaY, int xDir,
	const Color& color0, const Color& color1)
{
	float x1 = static_cast<float>(x);
	float dx = static_cast<float>(deltaX);

	Vector4 c0 = color0.toVector();
	Vector4 c1 = color1.toVector();
	Vector4 colorDiff = c1 - c0;

	int deltaYx2 = static_cast<int>(deltaY * 2);
	int deltaYx2MinusDeltaXx2 = deltaYx2 - static_cast<int>(deltaX * 2);
	int errorTerm = deltaYx2 - static_cast<int>(deltaX);

	(*this)(x, y) = colorToUnsigned(color0);

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

		Vector4 color = c0 + (colorDiff * (x - x1) / dx);
		(*this)(x, y) = colorToUnsigned(Color(color));
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

void PixelBuffer::drawVerticalLine(unsigned x, unsigned y, unsigned deltaX, unsigned deltaY, int xDir,
	const Color& color0, const Color& color1)
{
	float y1 = static_cast<float>(y);
	float dy = static_cast<float>(deltaY);

	Vector4 c0 = color0.toVector();
	Vector4 c1 = color1.toVector();
	Vector4 colorDiff = c1 - c0;

	int deltaXx2 = static_cast<int>(deltaX * 2);
	int deltaXx2MinusDeltaYx2 = deltaXx2 - static_cast<int>(deltaY * 2);
	int errorTerm = deltaXx2 - static_cast<int>(deltaY);

	(*this)(x, y) = colorToUnsigned(color0);
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

		Vector4 color = c0 + (colorDiff * (y - y1) / dy);
		(*this)(x, y) = colorToUnsigned(Color(color));
	}
}

void PixelBuffer::drawLine(
	int x0, int y0, Color color0,
	int x1, int y1, Color color1)
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

	if (deltaX > deltaY)
		if (color0.value == color1.value)
			drawHorizontalLine(x0, y0, deltaX, deltaY, xDir, colorToUnsigned(color0));
		else
			drawHorizontalLine(x0, y0, deltaX, deltaY, xDir, color0, color1);
	else
		if (color0.value == color1.value)
			drawVerticalLine(x0, y0, deltaX, deltaY, xDir, colorToUnsigned(color0));
		else
			drawVerticalLine(x0, y0, deltaX, deltaY, xDir, color0, color1);
}

/**
	* Draws a flat triangle
	*/
void PixelBuffer::drawTriangle(int x0, int y0,
	int x1, int y1,
	int x2, int y2,
	Color color)
{
}

/**
	* Draws a triangle
	*/
void PixelBuffer::drawTriangle(
	int x0, int y0, Color color0,
	int x1, int y1, Color color1,
	int x2, int y2, Color color2)
{
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
