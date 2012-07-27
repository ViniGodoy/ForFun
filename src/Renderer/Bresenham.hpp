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

#pragma once

#include <vector>

namespace fun {
namespace render {
	struct Point
	{
		int x;
		int y;

		Point() : x(0), y(0) {}
		Point(int x0, int y0) : x(x0), y(y0) {}

		void set(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
	};

	bool bresenham(int x0, int y0, int x1, int y1, std::vector<Point>& points);
}
}