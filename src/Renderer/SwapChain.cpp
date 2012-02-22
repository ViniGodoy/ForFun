#include "SwapChain.hpp"
#include "SDL.h"

using namespace fun::render;

SwapChain::SwapChain(int w, int h, bool fullscreen)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	int flags = SDL_SWSURFACE;

	if (fullscreen) flags |= SDL_FULLSCREEN;
	SDL_Surface* video = SDL_SetVideoMode(w, h, 32, flags);	
	if (video == NULL)
		exit(1); //TODO: Replace by exception
	buffer = new PixelBuffer(video);
}

PixelBuffer& SwapChain::getBuffer()
{
	return *buffer;
}

void SwapChain::swap()
{	
	SDL_Flip(buffer->surface);
}

SwapChain::~SwapChain()
{
	delete buffer;
	SDL_Quit();
}