#include <Renderer\SwapChain.hpp>
#include <SDL.h>

using namespace fun::render;

int main(int argc, char* argv[])
{
	SwapChain sw(800,600, false);
	sw.swap();
	SDL_Delay(10000);
	return 1;
}