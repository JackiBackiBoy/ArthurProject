#include <iostream>
#include "core/Window.h"

extern Window* BuildWindow();

int main()
{
	sf::ContextSettings contSettings{};
	contSettings.antialiasingLevel = 0;
	Window* tempWindow = BuildWindow();
	Window::CurrentWindow = tempWindow;

	tempWindow->Run();
	delete tempWindow;

	return 0;
}