#include "Window.h"
#include "Managers/MusicManager.h"
#include <iostream>
#include "Managers/InputManager.h"
#include "data/EntityDatabase.h"
Window::~Window()
{
	delete myRawWindow;
	myRawWindow = nullptr;
}
bool tempFlag = false;
void Window::Run()
{
	myRawWindow = new sf::RenderWindow(sf::VideoMode(myWidth, myHeight), sf::String(myTitle));

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// Call OnStart once
	OnStart();
	//myRawWindow->setFramerateLimit(500);
	while (myRawWindow->isOpen())
	{
		sf::Event event;
		while (myRawWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				myRawWindow->close();
		}

		myRawWindow->clear();

		InputManager::OnUpdate();
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


Window* Window::CurrentWindow = nullptr;