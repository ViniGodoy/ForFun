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

#include "..\Renderer\SwapChain.hpp"
#include <time.h>

#include <SDL.h>
#include <iostream>

using namespace fun::render;
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

const int DELAY_BETWEEN_TESTS = 500;

void drawTraces(SwapChain& sw)
{
	sw.backBuffer().drawLine(400,300,Color(0,0,0),500,599,Color(255,255,255));
	sw.backBuffer().drawLine(400,300,Color(0,0,0),300,599,Color(255,255,255));
	sw.backBuffer().drawLine(400,300,Color(0,0,0),500,0,Color(255,255,255));
	sw.backBuffer().drawLine(400,300,Color(0,0,0),300,0,Color(255,255,255));

	sw.backBuffer().drawLine(400,300,Color(0,0,0),0,599,Color(255,255,255));
	sw.backBuffer().drawLine(400,300,Color(0,0,0),799,599,Color(255,255,255));
	sw.backBuffer().drawLine(400,300,Color(0,0,0),0,0,Color(255,255,255));
	sw.backBuffer().drawLine(400,300,Color(0,0,0),799,0,Color(255,255,255));

	sw.backBuffer().drawLine(400,300,Color(0,0,0),0,200,Color(255,255,255));
	sw.backBuffer().drawLine(400,300,Color(0,0,0),799,200,Color(255,255,255));
	sw.backBuffer().drawLine(400,300,Color(0,0,0),0,400,Color(255,255,255));
	sw.backBuffer().drawLine(400,300,Color(0,0,0),799,400,Color(255,255,255));
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
	int r = 50 + rand() % 205;
	int g = 50 + rand() % 205;
	int b = 50 + rand() % 205;

	while (time < 1000) {
		lastX = (lastX + 1) % WIDTH;
		if (lastX == 0)
			lastY = (lastY + 1) % HEIGHT;

		sw.backBuffer().set(lastX, lastY, Color(r, g, b));
		time = SDL_GetTicks() - before;
		points++;
	}
	sw.flip();
	cout << "Number of points in one second: " << points << endl;
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
			Color(px & 0xFF, py & 0xFF, (px+py)&0xFF));
		x += 0.1f;
		y += x;
		lines++;
		time = SDL_GetTicks() - before;
	}
	sw.flip();
	cout << "Number of flat lines in one second: " << lines << endl;
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
			px, py, Color(px & 0xFF, py & 0xFF, (px+py)&0xFF),
			WIDTH-px-1, HEIGHT-py-1, Color(255, 0, 0));
		x += 0.1f;
		y += x;
		lines++;
		time = SDL_GetTicks() - before;
	}
	sw.flip();
	cout << "Number of lines in one second: " << lines << endl;
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
			Color(tone, tone, tone));
		count++;
		time = SDL_GetTicks() - before;
	}
	sw.flip();
	cout << "Number of flat triangles in one second: " << count << endl;
}

void drawTriangles(SwapChain& sw)
{
	long time = 0;
	int count = 0;
	long before = SDL_GetTicks();

	while (time < 1000)
	{
		unsigned char tone = static_cast<unsigned char>(time % 255);
		sw.backBuffer().drawTriangle(
			400,0, Color(tone,0,0),
			799,499, Color(0,tone,0),
			0,599, Color(0,0,tone));
		count++;
		time = SDL_GetTicks() - before;
	}
	sw.flip();
	cout << "Number of triangles in one second: " << count << endl;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	SwapChain sw(WIDTH,HEIGHT, false);

	drawTraces(sw);
	SDL_Delay(DELAY_BETWEEN_TESTS);

	for (int i = 0; i < 5; i++)
	{
		drawPoints(sw);
		SDL_Delay(DELAY_BETWEEN_TESTS);
	}

	for (int i = 0; i < 5; i++)
	{
		drawLines(sw);
		SDL_Delay(DELAY_BETWEEN_TESTS);
	}

	for (int i = 0; i < 5; i++)
	{
		drawFlatLines(sw);
		SDL_Delay(DELAY_BETWEEN_TESTS);
	}

	for (int i = 0; i < 5; i++)
	{
		drawFlatTriangles(sw);
		SDL_Delay(DELAY_BETWEEN_TESTS);
	}

	for (int i = 0; i < 5; i++)
	{
		drawTriangles(sw);
		SDL_Delay(DELAY_BETWEEN_TESTS);
	}

	SDL_Delay(3000);

	return 0;
}