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

#include <Renderer\SwapChain.hpp>
#include <SDL.h>

using namespace fun::render;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* argv[])
{
	SwapChain sw(WIDTH,HEIGHT, false);
	float hcolor = 255.0f / HEIGHT;
	float wcolor = 255.0f / WIDTH;
	for (unsigned i = 0; i < WIDTH; i++)
		sw.backBuffer().drawLine(i, 0, i, HEIGHT-1, Color(0,0, wcolor*i));
	sw.swap();
	SDL_Delay(1000);

	for (unsigned i = 0; i < HEIGHT; i++)
		sw.backBuffer().drawLine(0, i, WIDTH-1, i, Color(hcolor*i,0,0));
	sw.swap();

	SDL_Delay(1000);
	return 1;
}