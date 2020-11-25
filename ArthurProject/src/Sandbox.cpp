#include "core/Window.h"
#include "SFML/Graphics.hpp"

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

	void OnStart() override
	{

	}

	void OnUpdate() override
	{
		
	}

	void OnRender() override
	{
 
	}
};

Window* BuildWindow()
{
	return new Sandbox("Arthur", 1280, 720);
}