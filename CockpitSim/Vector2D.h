#pragma once

class Vector2D
{
public:
	Vector2D(double x = 0.0, double y = 0.0);
	Vector2D(Vector2D const& lhs);

	double x() const;
	double y() const;

	void x(double x);
	void y(double y);

private:
	double _x;
	double _y;
};

