#pragma once


class Airplane
{
public:
	Airplane();

	double get_speed() const;

private:
	double _speed{ 0.0 };
};

