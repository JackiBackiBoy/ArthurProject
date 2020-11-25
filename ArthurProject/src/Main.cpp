#include <iostream>
#include "core/Window.h"

extern Window* BuildWindow();

int main()
{
	Window* tempWindow = BuildWindow();
	Window::CurrentWindow = tempWindow;

	tempWindow->Run();
	delete tempWindow;

	return 0;
}