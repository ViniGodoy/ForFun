#pragma once

#include <vector>

namespace fun {
namespace render {
	struct Point
	{
		struct YOrder
		{
			bool operator() (const Point& p1, const Point& p2) 
			{
				if (p1.y < p2.y)
					return true;
				if (p1.y > p2.y)
					return false;

				return p1.x < p2.x;
			}
		};

		int x;
		int y;

		void set(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
	};

	bool bresenham(int x0, int y0, int x1, int y1, std::vector<Point>& points);
}
}