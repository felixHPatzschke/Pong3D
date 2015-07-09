#include "GContext.h"

#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>
#include <SFML/Graphics.hpp>
#include "GUtils.h"
#include "Constants.h"
#include <iostream>
#include "Ball.h"
#include "Paddle.h"


namespace mouse
{
	bool left=false;
	int x=0, y=0, dx=0, dy=0;
}
GLUquadric* gluquad;
double aspectRatio;

namespace scene
{
	Ball ball;
	Paddle pad_a(PLAYER_ONE), pad_b(PLAYER_TWO);
	unsigned int lives_a=LIVES, lives_b=LIVES;
	
	void tick(double dt)
	{
		ball.s+=(ball.v*dt);
		
		if(ball.s.getX()<=X_MIN+BALL_RADIUS | ball.s.getX()>=X_MAX-BALL_RADIUS)
		{
			ball.v.setX(-1.0*ball.v.getX());
			if(ball.s.getX()<=X_MIN+BALL_RADIUS)
			{
				ball.s.setX(X_MIN+BALL_RADIUS);
			}else
			{
				ball.s.setX(X_MAX-BALL_RADIUS);
			}
		}
		if(ball.s.getY()<=Y_MIN+BALL_RADIUS | ball.s.getY()>=Y_MAX-BALL_RADIUS)
		{
			ball.v.setY(-1.0*ball.v.getY());
			if(ball.s.getY()<=Y_MIN+BALL_RADIUS)
			{
				ball.s.setY(Y_MIN+BALL_RADIUS);
			}else
			{
				ball.s.setY(Y_MAX-BALL_RADIUS);
			}
		}
		
		if(ball.s.getZ()<=Z_MIN+BALL_RADIUS)
		{
			Vector diff = ball.s-pad_a.s;
			diff.setZ(0.0);
			if(diff.abs()<=PADDLE_RADIUS)
			{
				ball.v.setZ(-1.0*ball.v.getZ());
				ball.v+=diff*DEFLECTION_FACTOR;
				if(ball.v.getX()>BALL_MAX_SIDEWAYS_SPEED)
				{
					ball.v.setX(BALL_MAX_SIDEWAYS_SPEED);
				}else if(ball.v.getX()<-BALL_MAX_SIDEWAYS_SPEED)
				{
					ball.v.setX(-BALL_MAX_SIDEWAYS_SPEED);
				}else if(ball.v.getY()>BALL_MAX_SIDEWAYS_SPEED)
				{
					ball.v.setY(BALL_MAX_SIDEWAYS_SPEED);
				}else if(ball.v.getY()<-BALL_MAX_SIDEWAYS_SPEED)
				{
					ball.v.setY(-BALL_MAX_SIDEWAYS_SPEED);
				}
			}else
			{
				ball.s.setZ(Z_MAX-2);
				std::cout << ball.v.debug("") << std::endl;
				lives_a--;
				std::cout << "Player A: ";
				std::cout << lives_a << std::endl;
				if(lives_a==0)
				{
					std::cout << "Player A has lost" << std::endl;
				}
			}
		}

		if(ball.s.getZ()>=Z_MAX+BALL_RADIUS)
		{
			Vector diff = ball.s-pad_b.s;
			diff.setZ(0.0);
			if(diff.abs()<=PADDLE_RADIUS)
			{
				ball.v.setZ(-1.0*ball.v.getZ());
				ball.v+=diff*DEFLECTION_FACTOR;
				if(ball.v.getX()>BALL_MAX_SIDEWAYS_SPEED)
				{
					ball.v.setX(BALL_MAX_SIDEWAYS_SPEED);
				}else if(ball.v.getX()<-BALL_MAX_SIDEWAYS_SPEED)
				{
					ball.v.setX(-BALL_MAX_SIDEWAYS_SPEED);
				}else if(ball.v.getY()>BALL_MAX_SIDEWAYS_SPEED)
				{
					ball.v.setY(BALL_MAX_SIDEWAYS_SPEED);
				}else if(ball.v.getY()<-BALL_MAX_SIDEWAYS_SPEED)
				{
					ball.v.setY(-BALL_MAX_SIDEWAYS_SPEED);
				}
			}else
			{
				ball.s.setZ(Z_MIN+2);
				std::cout << ball.v.debug("") << std::endl;
				lives_b--;
				std::cout << "Player B: ";
				std::cout << lives_b << std::endl;
				if(lives_b==0)
				{
					std::cout << "Player B has lost" << std::endl;
				}
			}
		}
	}
}

inline void drawPaddle(GLUquadric* gluquad, Paddle& paddle)
{
	glPushMatrix();
	glTranslatev(paddle.s);
	gluDisk(gluquad, 0.0, PADDLE_RADIUS, SLICES, 1);
	glPopMatrix();
}

inline void drawBall(GLUquadric* gluquad, Ball& ball)
{
	glEnable(GL_LIGHTING);
	glPushMatrix();
	glTranslatev(ball.s);
	gluSphere(gluquad, BALL_RADIUS, SLICES, STACKS);
	//glVector3d(ball.v);
	glPopMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
	//glVertex3d(ball.s.getX(), Y_MIN, ball.s.getZ());
	glVertex3d(ball.s.getX(), Y_MAX, ball.s.getZ());
	glVertex3d(X_MIN, ball.s.getY(), ball.s.getZ());
	//glVertex3d(X_MAX, ball.s.getY(), ball.s.getZ());
	glEnd();
}

GContext::GContext(unsigned int width, unsigned int height, sf::Uint32 sm, sf::ContextSettings cs, unsigned int fps)
{
	window = new sf::RenderWindow(sf::VideoMode(width, height), "Title", sm, cs);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(fps);

	aspectRatio = ((double)width)/((double)height);
	running = true;
	paused = false;
	gluquad = gluNewQuadric();
}


GContext::~GContext(void)
{
	window->~RenderWindow();
}

void GContext::initGL()
{
	//glClearColor(COLOR_CLEAR[0], COLOR_CLEAR[1], COLOR_CLEAR[2], COLOR_CLEAR[3]);
	glClearColor(0.0, 0.0, 0.0, 1.0);

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
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MAT_SHININESS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MAT_WHITE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_YELLOW);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MAT_BLACK);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	::glLineWidth(4.0);
	::glPointSize(12.0);

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
		
		if(!paused)
			scene::tick(1.0/60.0);
	}
}

void GContext::drawGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspectRatio, 0.1, 1000.0);
	//gluPerspective(30.0, 16.0/9.0, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(PLAYER_ONE_PERSPECTIVE);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	glPushMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glColor4fv(::MAT_TRANSLATIONAL);

	glBegin(GL_LINES);
		glVertex3d(X_MIN, Y_MIN, Z_MIN);
		glVertex3d(X_MIN, Y_MIN, Z_MAX);
		glVertex3d(X_MAX, Y_MIN, Z_MIN);
		glVertex3d(X_MAX, Y_MIN, Z_MAX);
		glVertex3d(X_MAX, Y_MAX, Z_MIN);
		glVertex3d(X_MAX, Y_MAX, Z_MAX);
		glVertex3d(X_MIN, Y_MAX, Z_MIN);
		glVertex3d(X_MIN, Y_MAX, Z_MAX);
	glEnd();
	glBegin(GL_QUADS);
	for(int c=Z_MIN; c<=Z_MAX; c+=5)
	{
		glVertex3d(X_MIN, Y_MIN, c);
		glVertex3d(X_MIN, Y_MAX, c);
		glVertex3d(X_MAX, Y_MAX, c);
		glVertex3d(X_MAX, Y_MIN, c);
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//glEnable(GL_LIGHTING);
	glColor4fv(::MAT_MAGNETIC);
	::drawBall(gluquad, scene::ball);
	//glDisable(GL_LIGHTING);

	glColor4f(103.0f/255.0f, 140.0f/255.0f, 177.0f/255.0f, 0.35f);
	::drawPaddle(gluquad, scene::pad_b);
	
	glColor4d(210.0f/255.0f, 82.0f/255.0f, 82.0f/255.0f, 0.35f);
	::drawPaddle(gluquad, scene::pad_a);
	
	
	glFlush();
}

void GContext::drawSFML()
{
	//sf::CircleShape circle(120);
	//circle.setPosition(120,120);
	//circle.setFillColor(sf::Color(0,0,0,0));
	//circle.setOutlineColor(sf::Color(199, 221, 12, 128));
	//circle.setOutlineThickness(10);
	//window->draw(circle);
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
		}else if(evt.type == sf::Event::KeyReleased)
		{
			//std::cout << evt.key.code << std::endl;
			if(evt.key.code == sf::Keyboard::Space)
			{
				//if(paused==false)
				//{
				//	paused = true;
				//}else
				//{
				//	paused = false;
				//}
				//std::cout << paused << std::endl;
				paused = !paused;
			}
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		running = false;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		scene::pad_a.moveY(PADDLE_SPEED);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		scene::pad_a.moveY(-PADDLE_SPEED);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		scene::pad_a.moveX(PADDLE_SPEED);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		scene::pad_a.moveX(-PADDLE_SPEED);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		scene::pad_b.moveY(PADDLE_SPEED);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		scene::pad_b.moveY(-PADDLE_SPEED);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		scene::pad_b.moveX(PADDLE_SPEED);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		scene::pad_b.moveX(-PADDLE_SPEED);
	

}

