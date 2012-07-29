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

#include "../Renderer/SwapChain.hpp"
#include "../Renderer/Color.hpp"

#include <SDL.h>
#include <iostream>

using namespace fun::render;
using namespace fun::math;
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

const int DELAY_BETWEEN_TESTS = 1;

void drawTraces(SwapChain& sw)
{
	sw.backBuffer().drawLine(400,300,BLACK,500,599,WHITE);
	sw.backBuffer().drawLine(400,300,BLACK,300,599,WHITE);
	sw.backBuffer().drawLine(400,300,BLACK,500,0,WHITE);
	sw.backBuffer().drawLine(400,300,BLACK,300,0,WHITE);

	sw.backBuffer().drawLine(400,300,BLACK,0,599,WHITE);
	sw.backBuffer().drawLine(400,300,BLACK,799,599,WHITE);
	sw.backBuffer().drawLine(400,300,BLACK,0,0,WHITE);
	sw.backBuffer().drawLine(400,300,BLACK,799,0,WHITE);

	sw.backBuffer().drawLine(400,300,BLACK,0,200,WHITE);
	sw.backBuffer().drawLine(400,300,BLACK,799,200,WHITE);
	sw.backBuffer().drawLine(400,300,BLACK,0,400,WHITE);
	sw.backBuffer().drawLine(400,300,BLACK,799,400,WHITE);
	sw.flip();
}
void drawPoints(SwapChain& sw)
{
	long time = 0;
	unsigned long points = 0;

	int x[] = {400, 0, 799};
	int y[] = {0, 599, 599};

	int lastX = x[0];
	int lastY = y[0];

	long before = SDL_GetTicks();
	int color = rand() % 8;

	while (time < 1000) {
		lastX = (lastX + 1) % WIDTH;
		if (lastX == 0)
			lastY = (lastY + 1) % HEIGHT;

		sw.backBuffer().set(lastX, lastY, PURE_COLORS[color]);
		time = SDL_GetTicks() - before;
		points++;
	}
	sw.flip();
	cout << "Points per second: " << points << endl;
}

void drawFlatLines(SwapChain& sw)
{
	long time = 0;
	int lines = 0;
	long before = SDL_GetTicks();
	float x = static_cast<float>(rand() % WIDTH);
	float y = static_cast<float>(rand() % HEIGHT);

	while (time < 1000)
	{
		int px = static_cast<unsigned>(x) % WIDTH;
		int py = static_cast<unsigned>(y) % HEIGHT;
		sw.backBuffer().drawLine(px, py, WIDTH-px-1, HEIGHT-py-1,
			PURE_COLORS[((py+px)%7)+1]);
		x += 0.1f;
		y += x;
		lines++;
		time = SDL_GetTicks() - before;
	}
	sw.flip();
	cout << "Flat lines per second: " << lines << endl;
}

void drawLines(SwapChain& sw)
{
	long time = 0;
	int lines = 0;
	long before = SDL_GetTicks();
	float x = static_cast<float>(rand() % WIDTH);
	float y = static_cast<float>(rand() % HEIGHT);

	while (time < 1000)
	{
		int px = static_cast<unsigned>(x) % WIDTH;
		int py = static_cast<unsigned>(y) % HEIGHT;
		sw.backBuffer().drawLine(
			px, py, PURE_COLORS[((py+px)%7)+1],
			WIDTH-px-1, HEIGHT-py-1, PURE_COLORS[(px%7)+1]);
		x += 0.1f;
		y += x;
		lines++;
		time = SDL_GetTicks() - before;
	}
	sw.flip();
	cout << "Lines per second: " << lines << endl;
}

void drawFlatTriangles(SwapChain& sw)
{
	long time = 0;
	int count = 0;
	long before = SDL_GetTicks();

	while (time < 1000)
	{
		unsigned char tone = static_cast<unsigned char>(time % 255);
		sw.backBuffer().drawTriangle(
			400,0,
			799,599,
			0,499,
			Vector4(0.5, 0.5, 0.5));
		count++;
		time = SDL_GetTicks() - before;
	}
	sw.flip();
	cout << "Flat triangles per second: " << count << endl;
}

void drawTriangles(SwapChain& sw)
{
	long time = 0;
	int count = 0;
	long before = SDL_GetTicks();
	while (time < 1000)
	{
		sw.backBuffer().drawTriangle(
			400,0, BLUE,
			799,499, GREEN,
			0,599, RED);
		count++;
		time = SDL_GetTicks() - before;
	}
	sw.flip();
	cout << "Triangles per second: " << count << endl;
}

int main(int argc, char* argv[])
{
	srand(12345U);
	SwapChain sw(WIDTH,HEIGHT, false);

	drawTraces(sw);

	for (int i = 0; i < 5; i++)
		drawTriangles(sw);

	for (int i = 0; i < 5; i++)
		drawFlatTriangles(sw);

	for (int i = 0; i < 5; i++)
		drawFlatLines(sw);

	for (int i = 0; i < 5; i++)
		drawLines(sw);

	for (int i = 0; i < 5; i++)
		drawPoints(sw);

	SDL_Delay(3000);

	return 0;
}