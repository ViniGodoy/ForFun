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
#include "Bresenham.hpp"

#include "../Math/Vector3.hpp"
#include "../Math/Vector4.hpp"

#include <SDL.h>
#include <algorithm>

using namespace fun::render;
using namespace fun::math;


//-----------------------------------------------------------------------------
//Auxiliary functions
//-----------------------------------------------------------------------------
void updateMinMax(const std::vector<Point>& points, int* min, int* max)
{
	for (unsigned i = 0; i < points.size(); ++i)
	{
		Point p = points[i];
		if (p.x < min[p.y]) min[p.y] = p.x;
		if (p.x > max[p.y]) max[p.y] = p.x;
	}
}

void calculateEdges(int x0, int y0,
	int x1, int y1,
	int x2, int y2,
	int& miny,
	int& maxy,
	int** edgeMin,
	int** edgeMax)
{
	miny = minimum(y0, y1, y2);
	maxy = maximum(y0, y1, y2);

	int* minx = new int[maxy+1];
	int* maxx = new int[maxy+1];
	for (int i = miny; i <= maxy; ++i) minx[i] = std::numeric_limits<int>::max();
	for (int i = miny; i <= maxy; ++i) maxx[i] = std::numeric_limits<int>::min();

	std::vector<Point> tmp;

	bresenham(x0, y0, x1, y1, tmp);
	updateMinMax(tmp, minx, maxx);

	bresenham(x1, y1, x2, y2, tmp);
	updateMinMax(tmp, minx, maxx);

	bresenham(x2, y2, x0, y0, tmp);
	updateMinMax(tmp, minx, maxx);
	*edgeMin = minx;
	*edgeMax = maxx;
}

//-----------------------------------------------------------------------------
// PixelBuffer class
//-----------------------------------------------------------------------------
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

const Vector4 PixelBuffer::operator() (int x, int y) const
{
	unsigned pixelColor = ((Uint32*)surface->pixels)[(y * surface->w) + x];
	float factor = 1 / 255.0f;

	unsigned int temp = 0;

	SDL_PixelFormat* fmt = surface->format;

	/* Get Red component */
	temp = pixelColor & fmt->Rmask;  /* Isolate red component */
	temp >>= fmt->Rshift;			 /* Shift it down to 8-bit */
	temp <<= fmt->Rloss;			 /* Expand to a full 8-bit number */
	float r = temp * factor;

	/* Get Green component */
	temp = pixelColor & fmt->Gmask;  /* Isolate red component */
	temp >>= fmt->Gshift;			 /* Shift it down to 8-bit */
	temp <<= fmt->Gloss;			 /* Expand to a full 8-bit number */
	float g = temp * factor;

	/* Get Blue component */
	temp = pixelColor & fmt->Bmask;  /* Isolate red component */
	temp >>= fmt->Bshift;			 /* Shift it down to 8-bit */
	temp <<= fmt->Bloss;			 /* Expand to a full 8-bit number */
	float b = temp * factor;

	/* Get Alpha component */
	temp = pixelColor & fmt->Amask;  /* Isolate red component */
	temp >>= fmt->Ashift;			 /* Shift it down to 8-bit */
	temp <<= fmt->Aloss;		     /* Expand to a full 8-bit number */
	float a = temp * factor;
	return Vector4(r, g, b, a);
}

unsigned PixelBuffer::colorToUnsigned(const Vector4& color)
{
	int r = roundToInt(color.r() * 255);
	int g = roundToInt(color.g() * 255);
	int b = roundToInt(color.b() * 255);
	int a = roundToInt(color.a() * 255);

	unsigned finalColor = ((a >>= surface->format->Aloss) <<= surface->format->Ashift);
	finalColor |= ((r >>= surface->format->Rloss) <<= surface->format->Rshift);
	finalColor |= ((g >>= surface->format->Gloss) <<= surface->format->Gshift);
	finalColor |= ((b >>= surface->format->Bloss) <<= surface->format->Bshift);
	return finalColor;
}

PixelBuffer& PixelBuffer::set(int x, int y, const Vector4& color)
{
	return set(x, y, colorToUnsigned(color));
}

PixelBuffer& PixelBuffer::set(int x, int y, unsigned color)
{
	((Uint32*)surface->pixels)[(y * surface->w) + x] = color;
	return (*this);
}

void PixelBuffer::drawLine(
	int x0, int y0, const Vector4& c0,
	int x1, int y1, const Vector4& c1)
{
	Vector4 color0(c0);
	Vector4 color1(c1);

	std::vector<Point> points;

	if (bresenham(x0, y0, x1, y1, points))
		std::swap(color0, color1);

	//Flat line
	if (color0 == color1)
	{
		unsigned color = colorToUnsigned(color0);
		for (unsigned i = 0; i < points.size(); ++i)
			set(points[i].x, points[i].y, color);
		return;
	}

	//Shaded line
	Vector4 colorStep = (color1 - color0) / static_cast<float>(points.size());
	Vector4 color(color0);

	for (unsigned i = 0; i < points.size(); ++i)
	{
		set(points[i].x, points[i].y, color);
		color += colorStep;
	}
}

/**
* Draws a flat triangle
*/
void PixelBuffer::drawTriangle(int x0, int y0,
	int x1, int y1,
	int x2, int y2,
	const Vector4& color)
{
	int miny, maxy;
	int* minx, *maxx;
	calculateEdges(x0, y0, x1, y1, x2, y2, miny, maxy, &minx, &maxx);
	unsigned c = colorToUnsigned(color);
	for (int y = miny; y <= maxy; ++y)
		for (int x = minx[y]; x <= maxx[y]; ++x)
			set(x, y, c);

	delete [] minx;
	delete [] maxx;
}



/**
	* Draws a triangle
	*/
void PixelBuffer::drawTriangle(
	int x0, int y0, const Vector4& color0,
	int x1, int y1, const Vector4& color1,
	int x2, int y2, const Vector4& color2)
{
	int miny, maxy;
	int* minx, *maxx;

	calculateEdges(x0, y0, x1, y1, x2, y2, miny, maxy, &minx, &maxx);
	for (int y = miny; y <= maxy; ++y)
	{
		Vector3 b = barycenter2d(x0, y0, x1, y1, x2, y2, minx[y], y);
		Vector4 minColor = color0 * b.x() + color1 * b.y() + color2 * b.z();

		b = barycenter2d(x0, y0, x1, y1, x2, y2, maxx[y], y);
		Vector4 maxColor = color0 * b.x() + color1 * b.y() + color2 * b.z();

		Vector4 factor = (maxColor - minColor) / (maxx[y] - minx[y]);

		for (int x = minx[y]; x <= maxx[y]; ++x)
		{
			set(x, y, minColor);
			minColor += factor;
		}
	}

	delete [] minx;
	delete [] maxx;
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
