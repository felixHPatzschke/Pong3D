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
	glClearColor(0, 0, 0, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_NORMALIZE);

	glOrtho(-1,1,-1,1,1,-1);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_COLOR_MATERIAL);

	//glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	//glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MAT_SHININESS);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MAT_WHITE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_YELLOW);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MAT_BLACK);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	::glLineWidth(2.0);
	//::glPointSize(2.0);
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

