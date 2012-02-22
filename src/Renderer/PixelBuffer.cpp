#include "PixelBuffer.hpp"
#include "SDL.h"

using namespace fun::render;

PixelBuffer::PixelBuffer(SDL_Surface* _surface)
	: surface(_surface)
{	
}

PixelBuffer::PixelBuffer(int w, int h)
{	
	SDL_PixelFormat *vf = SDL_GetVideoSurface()->format;	
	surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 
		vf->Rmask, vf->Gmask, vf->Bmask, 0);
}

PixelBuffer::PixelBuffer(const PixelBuffer& other)
{
	surface = SDL_ConvertSurface(other.surface, other.surface->format, other.surface->flags);
}

PixelBuffer& PixelBuffer::operator =(const PixelBuffer& other)
{
	if (this == &other) return *this;
	SDL_FreeSurface(surface);
	surface = SDL_ConvertSurface(other.surface, other.surface->format, other.surface->flags);
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

PixelBuffer::~PixelBuffer()
{	
	if (surface != SDL_GetVideoSurface())
		SDL_FreeSurface(surface);
}
