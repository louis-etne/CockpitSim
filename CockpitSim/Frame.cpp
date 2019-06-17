#include "Frame.h"
#include "Colors.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


Frame::Frame(Vector2D const& position)
	: _position{ position }
{
	_center = Vector2D{ _position.x() + (_size / 2), _position.y() + (_size / 2) };
}


Vector2D Frame::get_position() const
{
	return _position;
}


void Frame::set_position(Vector2D const& position)
{
	_position = position;
}


double Frame::get_size() const
{
	return _size;
}


void Frame::set_size(double size)
{
	_size = size;
}


void Frame::draw() const
{
	draw_frame();
	draw_screws();
}


void Frame::draw_frame() const
{
	double round{ 15 };

	// Background
	al_draw_filled_rounded_rectangle(
		_position.x(), _position.y(), // x1, y1
		_position.x() + _size, _position.y() + _size, // x2, y2
		round, round, // rx, ry
		COLOR_FRAME_BKG
	);

	// Background border
	al_draw_rounded_rectangle(
		_position.x(), _position.y(), // x1, y1
		_position.x() + _size, _position.y() + _size, // x2, y2
		round, round,
		COLOR_APP_BKG,
		0
	);
}


void Frame::draw_screws() const
{
	const double offset{ 10 };

	// Top left
	draw_screw(Vector2D{ _position.x() + offset, _position.y() + offset });

	// Top right
	draw_screw(Vector2D{ _position.x() + _size - offset, _position.y() + offset });

	// Bottom left
	draw_screw(Vector2D{ _position.x() + offset, _position.y() + _size - offset });

	// Bottom right
	draw_screw(Vector2D{ _position.x() + _size - offset, _position.y() + _size - offset });
}


void Frame::draw_screw(Vector2D const& position) const
{
	al_draw_filled_circle(position.x(), position.y(), 5, COLOR_SCREW);
}

