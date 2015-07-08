#include "Tensor.h"

#include <sstream>

using namespace phs;

Tensor::Tensor()
{
	comp[0][0]=0.0;
	comp[0][1]=0.0;
	comp[0][2]=0.0;
	comp[1][0]=0.0;
	comp[1][1]=0.0;
	comp[1][2]=0.0;
	comp[2][0]=0.0;
	comp[2][1]=0.0;
	comp[2][2]=0.0;
}

Tensor::Tensor(const Tensor& t)
{
	comp[0][0]=t.get(0,0);
	comp[0][1]=t.get(0,1);
	comp[0][2]=t.get(0,2);
	comp[1][0]=t.get(1,0);
	comp[1][1]=t.get(1,1);
	comp[1][2]=t.get(1,2);
	comp[2][0]=t.get(2,0);
	comp[2][1]=t.get(2,1);
	comp[2][2]=t.get(2,2);
}

Tensor::Tensor(double xa, double xb, double xc, double ya, double yb, double yc, double za, double zb, double zc)
{
	comp[0][0]=xa;
	comp[0][1]=xb;
	comp[0][2]=xc;
	comp[1][0]=ya;
	comp[1][1]=yb;
	comp[1][2]=yc;
	comp[2][0]=za;
	comp[2][1]=zb;
	comp[2][2]=zc;
}


Tensor::~Tensor()
{}


Tensor Tensor::operator=(const Tensor& t)
{
	comp[0][0] = t.get(0,0);
	comp[0][1] = t.get(0,1);
	comp[0][2] = t.get(0,2);
	comp[1][0] = t.get(1,0);
	comp[1][1] = t.get(1,1);
	comp[1][2] = t.get(1,2);
	comp[2][0] = t.get(2,0);
	comp[2][1] = t.get(2,1);
	comp[2][2] = t.get(2,2);
	return (*this);
}


Tensor Tensor::operator*(const double r)
{
	return Tensor(
		r*comp[0][0], r*comp[0][1], r*comp[0][2], 
		r*comp[1][0], r*comp[1][1], r*comp[1][2], 
		r*comp[2][0], r*comp[2][1], r*comp[2][2]
	);
}

void Tensor::operator*=(const double r)
{
	comp[0][0] *= r;
	comp[0][1] *= r;
	comp[0][2] *= r;
	comp[1][0] *= r;
	comp[1][1] *= r;
	comp[1][2] *= r;
	comp[2][0] *= r;
	comp[2][1] *= r;
	comp[2][2] *= r;
}


void Tensor::transpose()
{
	double fnord;
	
	fnord = comp[1][0];
	comp[1][0] = comp[0][1];
	comp[0][1] = fnord;

	fnord = comp[2][0];
	comp[2][0] = comp[0][2];
	comp[0][2] = fnord;

	fnord = comp[2][1];
	comp[2][1] = comp[1][2];
	comp[1][2] = fnord;
}

void Tensor::invert()
{
	comp[0][0]*=-1;
	comp[0][1]*=-1;
	comp[0][2]*=-1;
	comp[1][0]*=-1;
	comp[1][1]*=-1;
	comp[1][2]*=-1;
	comp[2][0]*=-1;
	comp[2][1]*=-1;
	comp[2][2]*=-1;
}

Tensor Tensor::getTransposition()
{
	return Tensor(
		comp[0][0], comp[1][0], comp[2][0],
		comp[0][1], comp[1][1], comp[2][1],
		comp[0][2], comp[1][2], comp[2][2]
	);
}

Tensor Tensor::getInversion()
{
	return Tensor(
		-comp[0][0], -comp[0][1], -comp[0][2], 
		-comp[1][0], -comp[1][1], -comp[1][2], 
		-comp[2][0], -comp[2][1], -comp[2][2]
	);
}


std::string Tensor::debug(std::string msg)
{
	std::stringstream ss;
	ss << msg << '\n';
	ss << "/  " << comp[0][0] << " | " << comp[0][1] << " | " << comp[0][2] << "  \\" << '\n';
	ss << "|  " << comp[1][0] << " | " << comp[1][1] << " | " << comp[1][2] << "  |" << '\n';
	ss << "\\  " << comp[2][0] << " | " << comp[2][1] << " | " << comp[2][2] << "  /" << '\n';
	return ss.str();
}