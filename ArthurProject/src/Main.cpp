#include <iostream>
#include "core/Window.h"

int main()
{
	Window* tempWindow = new Window("Arthur Project", 1280, 720);
	tempWindow->Run();
	delete tempWindow;
	std::cout << "yes";

	return 0;
}