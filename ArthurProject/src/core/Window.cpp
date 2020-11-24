#include "Window.h"

Window::~Window()
{
	delete myRawWindow;
	myRawWindow = nullptr;
}

void Window::Run()
{
	myRawWindow = new sf::RenderWindow(sf::VideoMode(myWidth, myHeight), sf::String(myTitle));

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (myRawWindow->isOpen())
	{
		sf::Event event;
		while (myRawWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				myRawWindow->close();
		}

		myRawWindow->clear();
		myRawWindow->draw(shape);
		myRawWindow->display();
	}
}

void Window::OnStart()
{

}

void Window::OnUpdate()
{

}

void Window::OnRender()
{

}
