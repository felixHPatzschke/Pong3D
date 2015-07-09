#pragma once

#include "Vector.h"

using namespace phs;

class Paddle
{
public:
	Vector s;

	Paddle(int);
	virtual ~Paddle();

	void moveX(double);
	void moveY(double);
};

