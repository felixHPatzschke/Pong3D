#include <iostream>

#include "GContext.h"

int main()
{
	std::cout << "Press [ENTER] to exit the program.\nIronic, isn't it?" << std::endl;
	
	sf::ContextSettings cs(24, 8, 2, 4, 3, 0);
	GContext gc(1600, 900, sf::Style::Default, cs, 60);

	gc.initGL();
	gc.loopGL();
	gc.~GContext();
	
	getchar();
}