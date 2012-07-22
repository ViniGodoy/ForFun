#include "Color.hpp"

using namespace fun::math;
using namespace fun::render;

/**
* Creates a color from the given vector.
*/
Color::Color(const Vector4& color)
	: r(static_cast<unsigned char>(color[R] * 255)),
	  g(static_cast<unsigned char>(color[G] * 255)),
	  b(static_cast<unsigned char>(color[B] * 255)),
	  a(static_cast<unsigned char>(color[A] * 255))
{
}

/**
* Creates a vector from the given color.
*/
Vector4 Color::toVector() const
{
	return Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
