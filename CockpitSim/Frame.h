#pragma once

#include <allegro5/allegro.h>

#include "Vector2D.h"


class Frame
{
public:
	Frame(Vector2D const& position);

	Vector2D get_position() const;
	void set_position(Vector2D const& position);

	double get_size() const;
	void set_size(double size);

	void draw() const;

protected:
	Vector2D _position;
	Vector2D _center;
	double _size{ 300 };
	double _dial_border_thickness{ 2 };

private:
	void draw_frame() const;
	void draw_screws() const;
	void draw_screw(Vector2D const& position) const;
};

