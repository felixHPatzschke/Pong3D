#include "Ball.h"

#include "Constants.h"


Ball::Ball(void)
{
	s = Vector(0.0, 0.0, 0.0);
	v = Vector(3.0, 5.0, -20.0);
}

Ball::~Ball(void)
{
}

void Ball::tick(double dt)
{
	s+=(v*dt);
	
	if(s.getX()<=X_MIN | s.getX()>=X_MAX)
	{
		v.setX(-1.0*v.getX());
	}
	if(s.getY()<=Y_MIN | s.getY()>=Y_MAX)
	{
		v.setY(-1.0*v.getY());
	}
	if(s.getZ()<=Z_MIN | s.getZ()>=Z_MAX)
	{
		v.setZ(-1.0*v.getZ());
	}
}
