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