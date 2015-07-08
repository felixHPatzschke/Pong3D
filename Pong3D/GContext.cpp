#include "GContext.h"

#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <iostream>


namespace mouse
{
	bool left=false;
	int x=0, y=0, dx=0, dy=0;
}
GLUquadric* gluquad;
double aspectRatio;


GContext::GContext(unsigned int width, unsigned int height, sf::Uint32 sm, sf::ContextSettings cs, unsigned int fps)
{
	window = new sf::RenderWindow(sf::VideoMode(width, height), "Title", sm, cs);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(fps);

	aspectRatio = ((double)width)/((double)height);
	running = true;
	gluquad = gluNewQuadric();
}


GContext::~GContext(void)
{
	window->~RenderWindow();
}

void GContext::initGL()
{
	glClearColor(COLOR_CLEAR[0], COLOR_CLEAR[1], COLOR_CLEAR[2], COLOR_CLEAR[3]);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_NORMALIZE);

	glOrtho(-1,1,-1,1,1,-1);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MAT_SHININESS);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MAT_WHITE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_YELLOW);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MAT_BLACK);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	::glLineWidth(4.0);
	//::glPointSize(2.0);

	glEnable(GL_LIGHTING);

}

void GContext::loopGL()
{
	while(running)
	{
		drawGL();
		window->pushGLStates();
		drawSFML();
		window->popGLStates();
		window->display();
		pollEvents();
	}
}

void GContext::drawGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, aspectRatio, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(PLAYER_ONE_PERSPECTIVE);
	glPushMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);

		glColor4d(1.0, 0.5, 0.0, 0.2);
		glVertex3d(X_MIN, Y_MIN, Z_MAX);
		glVertex3d(X_MAX, Y_MIN, Z_MAX);
		glVertex3d(X_MAX, Y_MAX, Z_MAX);
		glVertex3d(X_MIN, Y_MAX, Z_MAX);
	
		glColor4d(0.0, 0.5, 1.0, 0.2);
		glVertex3d(X_MIN, Y_MIN, Z_MIN);
		glVertex3d(X_MAX, Y_MIN, Z_MIN);
		glVertex3d(X_MAX, Y_MAX, Z_MIN);
		glVertex3d(X_MIN, Y_MAX, Z_MIN);
	
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glColor4fv(::MAT_MAGNETIC);
	gluSphere(gluquad, 1.0, 64, 64);

	glPushMatrix();
	glTranslated(0.0, 6.0, Z_MAX);
	glColor4fv(::MAT_GRAVITATIONAL);
	gluSphere(gluquad, 1.0, 64, 64);
	glTranslated(4.0, -6.0, 0.0);
	glColor4d(1.0, 0.0, 0.0, 0.375);
	gluDisk(gluquad, 0.0, PADDLE_RADIUS, 24, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, -6.0, Z_MIN);
	glColor4fv(::MAT_ELECTRIC);
	gluSphere(gluquad, 1.0, 64, 64);
	glTranslated(-2.0, 6.0, 0.0);
	glColor4d(0.0, 0.0, 1.0, 0.375);
	gluDisk(gluquad, 0.0, PADDLE_RADIUS, 24, 1);
	glPopMatrix();

	glFlush();
}

void GContext::drawSFML()
{
	sf::CircleShape circle(120);
	circle.setPosition(120,120);
	circle.setFillColor(sf::Color(0,0,0,0));
	circle.setOutlineColor(sf::Color(199, 221, 12, 128));
	circle.setOutlineThickness(10);
	window->draw(circle);
}

void GContext::resizeGL(unsigned int width, unsigned int height)
{
	aspectRatio = ((double)width)/((double)height);
	glViewport(0,0,width, height);
	//window->setSize(sf::Vector2u(width, height));
}

void GContext::pollEvents()
{
	mouse::dx = sf::Mouse::getPosition().x - mouse::x;
	mouse::dy = sf::Mouse::getPosition().y - mouse::y;
	mouse::x += mouse::dx;
	mouse::y += mouse::dy;
	
	sf::Event evt;
	while(window->pollEvent(evt))
	{
		if(evt.type == sf::Event::Resized)
		{
			resizeGL(window->getSize().x, window->getSize().y);
		}else if(evt.type == sf::Event::Closed)
		{
			running = false;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		running = false;
	}
	
}

