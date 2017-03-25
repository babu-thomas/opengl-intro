#include <iostream>
#include <GL/glew.h>
#include "Display.h"

int main(int argc, char* argv[])
{
	Display display(800, 600, "Hello World");
	while (!display.isClosed())
	{
		display.clear(0.0f, 1.0f, 0.3f, 1.0f);
		display.update();
	}
	return 0;
}