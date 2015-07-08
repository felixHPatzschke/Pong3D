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
