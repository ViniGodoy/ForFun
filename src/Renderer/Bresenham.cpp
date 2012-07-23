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

#include "Bresenham.hpp"

namespace fun {
namespace render {
	void bresenhamHorizontal(int x, int y, int deltaX, int deltaY, int xDir, std::vector<Point>& points)
	{
		points.resize(deltaX+1);

		int deltaYx2 = static_cast<int>(deltaY * 2);
		int deltaYx2MinusDeltaXx2 = deltaYx2 - static_cast<int>(deltaX * 2);
		int errorTerm = deltaYx2 - static_cast<int>(deltaX);
		points[0].set(x, y);

		int i = 1;
		while (deltaX--)
		{
			if (errorTerm < 0)
				errorTerm += deltaYx2;
			else
			{
				y++;
				errorTerm += deltaYx2MinusDeltaXx2;
			}

			x += xDir;
			points[i++].set(x,y);
		}
	}

	void bresenhamVertical(int x, int y, int deltaX, int deltaY, int xDir, std::vector<Point>& points)
	{
		points.resize(deltaY+1);

		int deltaXx2 = static_cast<int>(deltaX * 2);
		int deltaXx2MinusDeltaYx2 = deltaXx2 - static_cast<int>(deltaY * 2);
		int errorTerm = deltaXx2 - static_cast<int>(deltaY);

		points[0].set(x,y);

		int i = 1;
		while (deltaY--)
		{
			if (errorTerm < 0)
				errorTerm += deltaXx2;
			else
			{
				x += xDir;
				errorTerm += deltaXx2MinusDeltaYx2;
			}

			y++;
			points[i++].set(x,y);
		}
	}

	bool bresenham(int x0, int y0, int x1, int y1, std::vector<Point>& points)
	{
		bool reversed = false;
		//Make sure y is positive
		if (y0 > y1)
		{
			std::swap(y0, y1);
			std::swap(x0, x1);
			reversed = true;
		}

		//Calculate deltas, x direction and color
		int deltaX = abs(x1 - x0);
		int deltaY = y1 - y0;
		int xDir = x1 > x0 ? 1 : -1;

		if (deltaX > deltaY)
			bresenhamHorizontal(x0, y0, deltaX, deltaY, xDir, points);
		else
			bresenhamVertical(x0, y0, deltaX, deltaY, xDir, points);

		return reversed;
	}
}
}