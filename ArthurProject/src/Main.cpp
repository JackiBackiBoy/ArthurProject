#include <iostream>
#include "core/Window.h"

extern Window* BuildWindow();

int main()
{
	Window* tempWindow = BuildWindow();
	tempWindow->Run();
	delete tempWindow;

	return 0;
}