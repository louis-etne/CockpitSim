#include "Anemometer.h"
#include "Colors.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <cmath>

# define M_PI 3.14159265358979323846  /* pi */


Anemometer::Anemometer(Vector2D const& position)
	: Instrument{ position }
{
}

void Anemometer::set_hand_angle(double angle)
{
	_hand_angle = angle * (M_PI / 180);
}


void Anemometer::draw() const
{
	Frame::draw();
	draw_dial();
}


void Anemometer::draw_dial() const
{
	// Background
	al_draw_filled_circle(
		_center.x()
		, _center.y()
		, (_size / 2) - _dial_border_thickness
		, COLOR_DIAL_BKG
	);

	// Graduations
	draw_graduations();

	// Hand
	draw_hand();

	// Center circle
	al_draw_filled_circle(
		_center.x() // cx
		, _center.y() // cy
		, 8 // radius
		, COLOR_SCREW
	);

	// Dial border
	al_draw_circle(
		_center.x() // cx
		, _center.y() // cy
		, (_size / 2) - _dial_border_thickness // radius
		, COLOR_DIAL_BORDER // color
		, _dial_border_thickness
	);
}


void Anemometer::draw_graduations() const
{
	double radius{ (_size / 2) - _dial_border_thickness };

	for (double i{ 0.0 }; i < M_PI * 2; i += (M_PI * 2) / 32) {
		double x1{ _center.x() + std::cos(i) * radius };
		double y1{ _center.y() + std::sin(i) * radius };
		double x2{ _center.x() + std::cos(i) * (radius - double(10)) };
		double y2{ _center.y() + std::sin(i) * (radius - double(10)) };

		al_draw_line(x1, y1, x2, y2, COLOR_DIAL_GRAD, 5);
	}
}


void Anemometer::draw_hand() const
{
	double offset{ 5 };
	double radius{ (_size / 2) - _dial_border_thickness };
	double rad{ _hand_angle };

	al_draw_line(
		_center.x() - std::sin(-rad) * 20
		, _center.y() - std::cos(-rad) * 20
		, _center.x() + std::sin(-rad) * (radius - offset)
		, _center.y() + std::cos(-rad) * (radius - offset)
		, al_map_rgb(255, 0, 0)
		, 2
	);
}