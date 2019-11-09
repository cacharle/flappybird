#include <iostream>
#include <ctime>
#include <cstdlib>
#include "graphics.hpp"

int main()
{
	srand(time(NULL));
	Graphics g;
	g.run();
}
