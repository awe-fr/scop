#include "Window.hpp"

int main()
{
	Window window("scop", 800, 600);
	while (!window.isClosed())
	{
		window.pollEvents();
	}
	return 0;
}