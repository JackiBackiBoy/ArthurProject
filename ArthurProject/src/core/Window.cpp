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

	// Call OnStart once
	OnStart();

	while (myRawWindow->isOpen())
	{
		sf::Event event;
		while (myRawWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				myRawWindow->close();
		}

		myRawWindow->clear();

		// Call base functions and overriden versions of OnUpdate and OnRender
		OnUpdate();
		Window::OnUpdate();

		OnRender();
		Window::OnRender();

		//myRawWindow->draw(shape);
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
