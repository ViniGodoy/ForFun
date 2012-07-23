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
#include "../Math/Vector4.hpp"

#include "SDL.h"
#include "Bresenham.hpp"
#include "../Math/Vector3.hpp"

#include <algorithm>

using namespace fun::render;
using namespace fun::math;


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

void PixelBuffer::drawLine(
	int x0, int y0, Color color0,
	int x1, int y1, Color color1)
{
	std::vector<Point> points;

	if (bresenham(x0, y0, x1, y1, points))
		std::swap(color0, color1);

	if (color0.value == color1.value)
		for (unsigned i = 0; i < points.size(); ++i)
			(*this)(points[i].x, points[i].y) = colorToUnsigned(color0);
	else
	{
		Vector4 colorStep =
			(color1.toVector() - color0.toVector()) / static_cast<float>(points.size());
		Vector4 color = color0.toVector();

		for (unsigned i = 0; i < points.size(); ++i)
		{
			set(points[i].x, points[i].y, Color(color));
			color += colorStep;
		}
	}
}

void updateMinMax(const std::vector<Point>& points, int* min, int* max)
{
	for (unsigned i = 0; i < points.size(); ++i)
	{
		Point p = points[i];
		if (p.x < min[p.y]) min[p.y] = p.x;
		if (p.x > max[p.y]) max[p.y] = p.x;
	}
}

int min(int a, int b, int c)
{
	int m = a < b ? a : b;
	return m < c ? m : c;
}

int max(int a, int b, int c)
{
	int m = a > b ? a : b;
	return m > c ? m : c;
}

void calculateEdges(int x0, int y0,
	int x1, int y1,
	int x2, int y2,
	int& miny,
	int& maxy,
	int** edgeMin,
	int** edgeMax)
{
	miny = min(y0, y1, y2);
	maxy = max(y0, y1, y2);

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

/**
* Draws a flat triangle
*/
void PixelBuffer::drawTriangle(int x0, int y0,
	int x1, int y1,
	int x2, int y2,
	Color color)
{
	int miny, maxy;
	int* minx, *maxx;
	calculateEdges(x0, y0, x1, y1, x2, y2, miny, maxy, &minx, &maxx);

	for (int y = miny; y <= maxy; ++y)
		for (int x = minx[y]; x <= maxx[y]; ++x)
			set(x, y, color);

	delete [] minx;
	delete [] maxx;
}

Vector3 baricentric(
	int x0, int y0,
	int x1, int y1,
	int x2, int y2,
	int px, int py)
{
	int y0y2 = y0 - y2;
	int x1x2 = x1 - x2;
	int y1y2 = y1 - y2;
	int x2x0 = x2 - x0;

	float areaDenom = 1.0f / (y0y2*x1x2+y1y2*x2x0);

	Vector3 b;
	b[0] = ((py - y2)*x1x2 + y1y2*(x2 - px)) * areaDenom;
	b[1] = ((py - y0)*x2x0 + (-y0y2)*(x0 - px)) * areaDenom;
	b[2] = 1.0f - b[0] - b[1];
	return b;
}

/**
	* Draws a triangle
	*/
void PixelBuffer::drawTriangle(
	int x0, int y0, Color color0,
	int x1, int y1, Color color1,
	int x2, int y2, Color color2)
{
	int miny, maxy;
	int* minx, *maxx;
	Vector4 c0 = color0.toVector();
	Vector4 c1 = color1.toVector();
	Vector4 c2 = color2.toVector();

	calculateEdges(x0, y0, x1, y1, x2, y2, miny, maxy, &minx, &maxx);
	for (int y = miny; y <= maxy; ++y)
		for (int x = minx[y]; x <= maxx[y]; ++x)
		{
			Vector3 b = baricentric(x0, y0, x1, y1, x2, y2, x, y);
			Vector4 c = b[X] * c0 + b[Y] * c1 + b[Z] * c2;
			set(x, y, Color(c));
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
