#pragma once

#include "Instrument.h"
#include "Vector2D.h"


class Anemometer : public Instrument
{
public:
	Anemometer(Vector2D const& position);

	void set_hand_angle(double angle);
	void draw() const;

protected:
	double _hand_angle{ 0.0 };

private:
	void draw_dial() const;
	void draw_graduations() const;
	void draw_hand() const;
};

