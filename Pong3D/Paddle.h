#pragma once
class Paddle
{
public:
	double x,y,z;

	Paddle(int);
	virtual ~Paddle();

	void moveX(double);
	void moveY(double);
};

