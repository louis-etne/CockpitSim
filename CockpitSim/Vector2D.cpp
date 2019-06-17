#include "Vector2D.h"

Vector2D::Vector2D(double x, double y)
	: _x{ x }
	, _y{ y }
{
}

Vector2D::Vector2D(Vector2D const& lhs)
	: Vector2D{ lhs.x(), lhs.y() }
{
}

double Vector2D::x() const
{
	return _x;
}

double Vector2D::y() const
{
	return _y;
}

void Vector2D::x(double x)
{
	_x = x;
}

void Vector2D::y(double y)
{
	_y = y;
}
