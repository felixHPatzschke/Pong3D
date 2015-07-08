#include "Paddle.h"
#include "Constants.h"

Paddle::Paddle(int player)
{
	x = 0.0;
	y = 0.0;
	if(player==PLAYER_ONE)
	{
		z = Z_MIN;
	}else
	{
		z = Z_MAX;
	}
}


Paddle::~Paddle(void)
{
}

void Paddle::moveX(double amount)
{
	x+=amount;
	if(x<X_MIN)
		x=X_MIN;
	if(x>X_MAX)
		x=X_MAX;
}

void Paddle::moveY(double amount)
{
	y+=amount;
	if(y<Y_MIN)
		y=Y_MIN;
	if(y>Y_MAX)
		y=Y_MAX;
}
