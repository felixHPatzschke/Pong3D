#include "Paddle.h"
#include "Constants.h"

Paddle::Paddle(int player)
{
	double x,y,z;
	x = 0.0;
	y = 0.0;
	if(player==PLAYER_ONE)
	{
		z = Z_MIN;
	}else
	{
		z = Z_MAX;
	}
	s = Vector(x,y,z);
}


Paddle::~Paddle(void)
{
}

void Paddle::moveX(double amount)
{
	double x = s.getX()+amount;
	if(x<X_MIN)
		x=X_MIN;
	if(x>X_MAX)
		x=X_MAX;
	s.setX(x);
}

void Paddle::moveY(double amount)
{
	double y = s.getY()+amount;
	if(y<Y_MIN)
		y=Y_MIN;
	if(y>Y_MAX)
		y=Y_MAX;
	s.setY(y);
}
