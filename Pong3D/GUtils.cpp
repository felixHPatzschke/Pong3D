#include "GUtils.h"

#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>
#include "Constants.h"

using namespace phs;

Camera::Camera(double ex, double ey, double ez, double cx, double cy, double cz, double ux, double uy, double uz, double f)
{
	eye = Vector(ex,ey,ez);
	center = Vector(cx,cy,cz);
	up = Vector(ux,uy,uz);
	fov = f;
}

Camera::Camera()
{
	eye = Vector(3.0, 5.0, 1.0);
	center = Vector(0.0, 0.0, 0.0);
	up = Vector(0.0, 0.0, 1.0);
	fov = 30;
}

Camera::~Camera(void)
{}

void Camera::orthogonalize()
{
	up = up.getPerpendicularComponent(eye);
	up.normalize();
}

void Camera::rotateZBound(double x, double y, double z)
{
	Vector e_z(0,0,1);
	e_z = up.getParallelComponent(e_z);

	x*=-0.02;
	y*=0.02;
	z*=0.02;

	if(x!=0)
	{
		eye.rotate(e_z, x);
		up.rotate(e_z, x);
	}
	if(y!=0)
	{
		Vector axis = eye.cross(up);
		eye.rotate(axis, y);
		up.rotate(axis, y);
	}
	if(z!=0)
	{
		up.rotate(eye, z);
	}
}

void Camera::rotateFree(double x, double y, double z)
{
	orthogonalize();
	x*=-0.02;
	y*=0.02;
	z*=0.02;

	if(x!=0)
	{
		eye.rotate(up, x);
	}
	if(y!=0)
	{
		Vector axis = eye.cross(up);
		eye.rotate(axis, y);
		up.rotate(axis, y);
	}
	if(z!=0)
	{
		up.rotate(eye, z);
	}
}

void Camera::translateFlat(double x, double y, double z)
{
	x*=-0.02;
	y*=0.02;
	z*=0.02;
	Vector e_z = Vector(0,0,1);
	Vector fwd = eye.getPerpendicularComponent(e_z)*-1.0;
	fwd.normalize();
	Vector right = fwd.cross(e_z);
	center += (right*x + fwd*y + e_z*z);
}

void Camera::translateParallel(double x, double y, double z)
{
	x*=-0.02;
	y*=0.02;
	z*=0.02;
	orthogonalize();
	Vector fwd = eye.getNormalized().getInverted();
	Vector right = fwd.cross(up);
	center += (right*x + up*y + fwd*z);
}

void glVector3d(GLUquadric* gluquad, Vector& o, Vector& p, unsigned int slices)
{
	glPushMatrix();
		glTranslated(o.getX(), o.getY(), o.getZ());
		Vector axis = p.cross(Vector(0,0,1));
		double angle = std::acos(p.getZ()/p.abs());
		glRotated(180.0, 0.0, 0.0, 1.0);
		glRotated(angle*180/PI, axis.getX(), axis.getY(), axis.getZ());
		
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(0,0,p.abs()*0.85);
		glEnd();
		glTranslated(0.0, 0.0, p.abs()*0.85);
		::gluCylinder(gluquad, p.abs()*0.05, 0, p.abs()*0.15, slices, 1);
		//::gluDisk(gluquad, 0, p.abs()*0.05, slices, 1);
	glPopMatrix();
}

void glVector3d(GLUquadric* gluquad, Vector& p, unsigned int slices)
{
	glPushMatrix();
		Vector axis = p.cross(Vector(0,0,1));
		double angle = std::acos(p.getZ()/p.abs());
		glRotated(180.0, 0.0, 0.0, 1.0);
		glRotated(angle*180/PI, axis.getX(), axis.getY(), axis.getZ());
		
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(0,0,p.abs()*0.85);
		glEnd();
		glTranslated(0.0, 0.0, p.abs()*0.85);
		::gluCylinder(gluquad, p.abs()*0.05, 0, p.abs()*0.15, slices, 1);
		//::gluDisk(gluquad, 0, p.abs()*0.05, slices, 1);
	glPopMatrix();
}

void glVector3d(Vector& o, Vector& p)
{
	glPushMatrix();
		glTranslated(o.getX(), o.getY(), o.getZ());
		Vector axis = p.cross(Vector(0,0,1));
		double angle = std::acos(p.getZ()/p.abs());
		glRotated(180.0, 0.0, 0.0, 1.0);
		glRotated(angle*180/PI, axis.getX(), axis.getY(), axis.getZ());
		
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(0,0,p.abs()*0.85);
		glEnd();
		glTranslated(0.0, 0.0, p.abs()*0.85);
		double h = p.abs()*0.15;
		double b = p.abs()*0.05;
		glBegin(GL_TRIANGLES);
			
			glNormal3d(b*h, b*h, b*b);
			glVertex3d(0,0,h);
			glVertex3d(0,b,0);
			glVertex3d(b,0,0);
		
			glNormal3d(b*h, -b*h, b*b);
			glVertex3d(0,0,h);
			glVertex3d(0,-b,0);
			glVertex3d(b,0,0);
		
			glNormal3d(-b*h, -b*h, b*b);
			glVertex3d(0,0,h);
			glVertex3d(0,-b,0);
			glVertex3d(-b,0,0);
		
			glNormal3d(-b*h, b*h, b*b);
			glVertex3d(0,0,h);
			glVertex3d(0,b,0);
			glVertex3d(-b,0,0);
		
		glEnd();

	glPopMatrix();
}

void glVector3d(Vector& p)
{
	glPushMatrix();
		Vector axis = p.cross(Vector(0,0,1));
		double angle = std::acos(p.getZ()/p.abs());
		glRotated(180.0, 0.0, 0.0, 1.0);
		glRotated(angle*180/PI, axis.getX(), axis.getY(), axis.getZ());
		
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(0,0,p.abs()*0.85);
		glEnd();
		glTranslated(0.0, 0.0, p.abs()*0.85);
		double h = p.abs()*0.15;
		double b = p.abs()*0.05;
		glBegin(GL_TRIANGLES);
			
			glNormal3d(b*h, b*h, b*b);
			glVertex3d(0,0,h);
			glVertex3d(0,b,0);
			glVertex3d(b,0,0);
		
			glNormal3d(b*h, -b*h, b*b);
			glVertex3d(0,0,h);
			glVertex3d(0,-b,0);
			glVertex3d(b,0,0);
		
			glNormal3d(-b*h, -b*h, b*b);
			glVertex3d(0,0,h);
			glVertex3d(0,-b,0);
			glVertex3d(-b,0,0);
		
			glNormal3d(-b*h, b*h, b*b);
			glVertex3d(0,0,h);
			glVertex3d(0,b,0);
			glVertex3d(-b,0,0);
		
		glEnd();
	glPopMatrix();
}

void glTriangle(Vector& a, Vector& b, Vector& c, Vector& eye)
{
	glNormal4v(a,b,c,eye);
	//glBegin(GL_TRIANGLES);
		//glNormalv(a);
		glVertexv(a);
		//glNormalv(b);
		glVertexv(b);
		//glNormalv(c);
		glVertexv(c);
	//glEnd();
}

void gluCone(double r, double h, unsigned int slices, bool closeBottom)
{
	double x=0, y=r;
	Vector a = Vector(0,0,1);
	Vector n = Vector(0,h,r);
	double angle = 2*3.14159265358979323846/((double)slices);
	double xn, yn, cos=std::cos(angle), sin=std::sin(angle);
	angle *= 0.5;
	//n.rotate(a, 0.5*angle);
	glBegin(GL_TRIANGLES);
	glNormalv(n);
	for(unsigned int c=0; c<slices; c++)
	{
		//glNormalv(n);
		glVertex3d(x,y,0);
		n.rotate(a,-angle);
		glNormalv(n);
		glVertex3d(0,0,h);
		xn = cos*x+sin*y;
		yn = -sin*x+cos*y;
		x=xn; y=yn;
		n.rotate(a,-angle);
		glNormalv(n);
		glVertex3d(x,y,0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	if(closeBottom)
	{
		glNormal3d(0,0,-1);
		glVertex3d(0,0,0);
		for(unsigned int c=0; c<=slices; c++)
		{
			glVertex3d(x,y,0);
			xn = cos*x+sin*y;
			yn = -sin*x+cos*y;
			x=xn; y=yn;
		}
	}
	glEnd();

}
