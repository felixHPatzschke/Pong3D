#pragma once

#include "Vector.h"
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>

using namespace phs;

class Camera
{
private:
	Vector eye, center, up;
	double fov;

public:
	Camera(double, double, double, double, double, double, double, double, double, double);
	Camera();
	virtual ~Camera(void);

	void rotateZBound(double, double, double);
	void rotateFree(double, double, double);
	void translateFlat(double, double, double);
	void translateParallel(double, double, double);
	inline void zoom(double r){eye*=(1.0+(0.05*r));}
	inline void zoomFOV(double r){ fov+=r; if(fov<10)fov=10; if(fov>120)fov=120; }
	//Because who needs readable code, right?
	void orthogonalize();

	inline double getEX()const{return eye.getX()+center.getX();}
	inline double getEY()const{return eye.getY()+center.getY();}
	inline double getEZ()const{return eye.getZ()+center.getZ();}
	inline double getCX()const{return center.getX();}
	inline double getCY()const{return center.getY();}
	inline double getCZ()const{return center.getZ();}
	inline double getUX()const{return up.getX();}
	inline double getUY()const{return up.getY();}
	inline double getUZ()const{return up.getZ();}
	inline Vector getEYE()const{return eye;}
	inline Vector getCENTER()const{return center;}
	inline Vector getUP()const{return up;}
	inline double getFOV()const{return fov;}

};

inline void gluLookAt(Camera& cam){::gluLookAt( cam.getEX(), cam.getEY(), cam.getEZ(), cam.getCX(), cam.getCY(), cam.getCZ(), cam.getUX(), cam.getUY(), cam.getUZ() );}
inline void glVertexv(const Vector& v){::glVertex3d(v.getX(), v.getY(), v.getZ());}
void glVector3d(GLUquadric*, Vector&, Vector&, unsigned int);
void glVector3d(GLUquadric*, Vector&, unsigned int);
void glVector3d(Vector&, Vector&);
void glVector3d(Vector&);
void glTriangle(Vector&, Vector&, Vector&, Vector&);
inline void glNormalv(const Vector& v){glNormal3d(v.getX(), v.getY(), v.getZ());}
inline void glTranslatev(const Vector& v){glTranslated(v.getX(), v.getY(), v.getZ());}
inline void glNormal4v(Vector& a, Vector& b, Vector& c, Vector& eye){Vector n = eye.getParallelComponent((b-a).cross(c-a));glNormalv(n);}
void gluCone(double, double, unsigned int, bool);

