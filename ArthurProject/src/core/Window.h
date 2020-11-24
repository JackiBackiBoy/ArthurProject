#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <string>

class Window
{
public:
	Window(const std::string& aTitle, const int& aWidth, const int& aHeight) : myTitle(aTitle), myWidth(aWidth), myHeight(aHeight) {};

	void Run();

protected:
	std::string myTitle;
	int myWidth;
	int myHeight;
};
#endif