#include "Vector.h"
//#include "Tensor.h"
#include <cmath>
#include <sstream>

using namespace phs;

Vector::Vector()
{
	comp[0]=0.0;
	comp[1]=0.0;
	comp[2]=0.0;
}

Vector::Vector(const Vector& v)
{
	comp[0]=v.getX();
	comp[1]=v.getY();
	comp[2]=v.getZ();
}

Vector::Vector(double x, double y, double z)
{
	comp[0]=x;
	comp[1]=y;
	comp[2]=z;
}


Vector::~Vector()
{}


inline double Vector::absSqr()const
{
	return (comp[0]*comp[0]+comp[1]*comp[1]+comp[2]*comp[2]);
}

inline double Vector::abs()const
{
	return std::sqrt((comp[0]*comp[0]+comp[1]*comp[1]+comp[2]*comp[2]));
}

Vector Vector::operator=(const Vector& v)
{
	comp[0]=v.getX();
	comp[1]=v.getY();
	comp[2]=v.getZ();
	return *this;
}

void Vector::normalize()
{
	double a = abs();
	comp[0]/=a;
	comp[1]/=a;
	comp[2]/=a;
	//(*this) *= (1.0/abs());
}

void Vector::invert()
{
	comp[0]*=-1;
	comp[1]*=-1;
	comp[2]*=-1;
}

void Vector::operator+=(const Vector& v)
{
	comp[0]+=v.getX();
	comp[1]+=v.getY();
	comp[2]+=v.getZ();
}

void Vector::operator-=(const Vector& v)
{
	comp[0]-=v.getX();
	comp[1]-=v.getY();
	comp[2]-=v.getZ();
}

void Vector::operator*=(const double r)
{
	comp[0]*=r;
	comp[1]*=r;
	comp[2]*=r;
}

void Vector::operator*=(const Tensor& t)
{
	Vector res = Vector(
		(t.get(0,0)*comp[0] + t.get(0,1)*comp[1] + t.get(0,2)*comp[2]),
		(t.get(1,0)*comp[0] + t.get(1,1)*comp[1] + t.get(1,2)*comp[2]),
		(t.get(2,0)*comp[0] + t.get(2,1)*comp[1] + t.get(2,2)*comp[2])
	);
	comp[0] = res.getX();
	comp[1] = res.getY();
	comp[2] = res.getZ();
}


Vector Vector::getNormalized()
{
	return ((*this)*(1.0/abs()));
}

Vector Vector::getInverted()
{
	return ((*this)*-1);
}

Vector Vector::operator+(const Vector& v)
{
	return Vector(comp[0]+v.getX(), comp[1]+v.getY(), comp[2]+v.getZ());
}

Vector Vector::operator-(const Vector& v)
{
	return Vector(comp[0]-v.getX(), comp[1]-v.getY(), comp[2]-v.getZ());
}

Vector Vector::operator*(const double r)
{
	return Vector(comp[0]*r, comp[1]*r, comp[2]*r);
}

double Vector::operator*(const Vector& v)
{
	return ((comp[0]*v.getX())+(comp[1]*v.getY())+(comp[2]*v.getZ()));
}

Vector Vector::operator*(const Tensor& t)
{
	return Vector(
		(t.get(0,0)*comp[0] + t.get(0,1)*comp[1] + t.get(0,2)*comp[2]),
		(t.get(1,0)*comp[0] + t.get(1,1)*comp[1] + t.get(1,2)*comp[2]),
		(t.get(2,0)*comp[0] + t.get(2,1)*comp[1] + t.get(2,2)*comp[2])
	);
}

Vector Vector::cross(const Vector& v)
{
	return Vector(
		(comp[1]*v.getZ())-(comp[2]*v.getY()),
		(comp[2]*v.getX())-(comp[0]*v.getZ()),
		(comp[0]*v.getY())-(comp[1]*v.getX())
	);
}

Vector Vector::getParallelComponent(Vector& v)
{
	return (v.getNormalized()*getParallelComponentValue(v));
}

double Vector::getParallelComponentValue(const Vector& v)
{
	return (*this)*v/(v.abs());
}

Vector Vector::getPerpendicularComponent(Vector& v)
{
	return (*this)-getParallelComponent(v);
}

void Vector::rotate(Vector a, double angle)
{
	double cos = std::cos(angle);
    double sin = std::sin(angle);
	a.normalize();
        
    Tensor transformationMatrix = Tensor(
		a.getX()*a.getX()*(1.0-cos)+cos,			a.getY()*a.getX()*(1.0-cos)-a.getZ()*sin,	a.getZ()*a.getX()*(1.0-cos)+a.getY()*sin,
		a.getX()*a.getY()*(1.0-cos)+a.getZ()*sin,	a.getY()*a.getY()*(1.0-cos)+cos,			a.getZ()*a.getY()*(1.0-cos)-a.getX()*sin,
		a.getX()*a.getZ()*(1.0-cos)-a.getY()*sin,	a.getY()*a.getZ()*(1.0-cos)+a.getX()*sin,	a.getZ()*a.getZ()*(1.0-cos)+cos
	);
	(*this)*=transformationMatrix;
}

void Vector::rotate(Vector a)
{
	rotate(a, a.abs());
}

Vector Vector::getRotation(Vector a, double angle)
{
	double cos = std::cos(angle);
    double sin = std::sin(angle);
	a.normalize();
        
    Tensor transformationMatrix = Tensor(
		a.getX()*a.getX()*(1.0-cos)+cos,			a.getY()*a.getX()*(1.0-cos)-a.getZ()*sin,	a.getZ()*a.getX()*(1.0-cos)+a.getY()*sin,
		a.getX()*a.getY()*(1.0-cos)+a.getZ()*sin,	a.getY()*a.getY()*(1.0-cos)+cos,			a.getZ()*a.getY()*(1.0-cos)-a.getX()*sin,
		a.getX()*a.getZ()*(1.0-cos)-a.getY()*sin,	a.getY()*a.getZ()*(1.0-cos)+a.getX()*sin,	a.getZ()*a.getZ()*(1.0-cos)+cos
	);
	return (*this)*transformationMatrix;
}

Vector Vector::getRotation(Vector a)
{
	return getRotation(a, a.abs());
}

Tensor Vector::getRotationMatrix(double angle)
{
	double cos = std::cos(angle);
    double sin = std::sin(angle);
	Vector a = getNormalized();
        
    return Tensor(
		a.getX()*a.getX()*(1.0-cos)+cos,			a.getY()*a.getX()*(1.0-cos)-a.getZ()*sin,	a.getZ()*a.getX()*(1.0-cos)+a.getY()*sin,
		a.getX()*a.getY()*(1.0-cos)+a.getZ()*sin,	a.getY()*a.getY()*(1.0-cos)+cos,			a.getZ()*a.getY()*(1.0-cos)-a.getX()*sin,
		a.getX()*a.getZ()*(1.0-cos)-a.getY()*sin,	a.getY()*a.getZ()*(1.0-cos)+a.getX()*sin,	a.getZ()*a.getZ()*(1.0-cos)+cos
	);
}

Tensor Vector::getRotationMatrix()
{
	return getRotationMatrix(abs());
}

std::string Vector::debug(std::string msg)
{
	std::stringstream ss;
	ss << msg <<"(x= " << comp[0] << "| y=" << comp[1] << "| z=" << comp[2] << ")";
	return ss.str();
}

bool Vector::operator==(const Vector& v)
{
	return (comp[0]==v.getX() && comp[1]==v.getY() && comp[2]==v.getZ());
}

bool Vector::approaches(const Vector& v, double dq)
{
	return ((*this)-v).absSqr()<=dq;
}

