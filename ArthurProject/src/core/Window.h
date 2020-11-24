#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <string>
#include "SFML/Graphics.hpp"

class Window
{
public:
	Window(const std::string& aTitle, const int& aWidth, const int& aHeight) : myTitle(aTitle), myWidth(aWidth), myHeight(aHeight), myRawWindow(nullptr) {};

	void Run();

	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;

protected:
	std::string myTitle;
	int myWidth;
	int myHeight;
	sf::RenderWindow* myRawWindow;
};
#endif