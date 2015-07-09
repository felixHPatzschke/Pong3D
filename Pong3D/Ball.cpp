#include "Ball.h"

#include "Constants.h"


Ball::Ball(void)
{
	s = Vector(0.0, 0.0, 0.0);
	v = Vector(3.0, 5.0, -BALL_Z_SPEED);
}

Ball::~Ball(void)
{
}

void Ball::tick(double dt)
{
	
}
