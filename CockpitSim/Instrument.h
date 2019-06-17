#pragma once

#include "Frame.h"
#include "Vector2D.h"


class Instrument : public Frame
{
public:
	Instrument(Vector2D const& position);
	virtual ~Instrument();

	virtual void draw() const = 0;
};

