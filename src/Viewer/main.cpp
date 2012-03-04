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

#include <Renderer\SwapChain.hpp>
#include <SDL.h>
#include <iostream>

using namespace fun::render;
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* argv[])
{
	SwapChain sw(WIDTH,HEIGHT, false);
	long before = SDL_GetTicks();
	long time = 0;
	float x = 0;
	float y = 0;
	int lines = 0;
	while (time < 1000)
	{
		int px = static_cast<unsigned>(x) % WIDTH;
		int py = static_cast<unsigned>(y) % HEIGHT;
		sw.backBuffer().drawLine(px, py, WIDTH-px-1, HEIGHT-py-1, Color(px & 0xFF, py & 0xFF, (px+py)&0xFF));		
		x += 0.01;
		y += x;
		lines++;
		time = SDL_GetTicks() - before;
	}
	sw.swap();
	SDL_Delay(3000);
	cout << "Number of lines drawn in one second:" << lines;
	return 0;
}