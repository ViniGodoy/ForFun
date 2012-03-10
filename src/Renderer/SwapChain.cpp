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

PixelBuffer& SwapChain::backBuffer()
{
	return *buffer;
}

void SwapChain::flip()
{
	SDL_Flip(buffer->surface);
}

SwapChain::~SwapChain()
{
	delete buffer;
	SDL_Quit();
}