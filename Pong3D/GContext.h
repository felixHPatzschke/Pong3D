#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class GContext
{
public:
	sf::RenderWindow* window;
	
	GContext(unsigned int width, unsigned int height, sf::Uint32 sm, sf::ContextSettings cs, unsigned int fps);
	virtual ~GContext(void);

	void initGL();
	void loopGL();
	void drawGL();
	void drawSFML();
	void resizeGL(unsigned int, unsigned int);
	void pollEvents();

private:
	bool running;
	bool paused;
};

