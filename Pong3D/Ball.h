#pragma once

#include "Vector.h"

using namespace phs;

class Ball
{
public:
	Vector s, v;
	
	Ball(void);
	virtual ~Ball(void);

	void tick(double);
};

