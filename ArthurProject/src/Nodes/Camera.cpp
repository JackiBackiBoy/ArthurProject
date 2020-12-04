#include "Camera.h"
#include "core/Window.h"
#include <Nodes\Scene.h>


Camera::Camera(const sf::Vector2f& aPosition, std::string aName) : Node(aPosition, aName)
{

	myView = sf::View(aPosition, (sf::Vector2f)Window::CurrentWindow->GetRawWindow()->getSize());
	myZoom = 1;
}

void Camera::OnUpdate()
{
	Node::OnUpdate();
	((Scene*)myParent)->SetView(myView);

}

void Camera::SetPosition(const sf::Vector2f& aPosition)
{
	Node::SetPosition(aPosition);
	myView.setCenter(myPosition);
	((Scene*)myParent)->SetView(myView);
	//Window::CurrentWindow->GetRawWindow()->setView(myView);
}

void Camera::Zoom(float aValue)
{
	float tempMultiplier = (myZoom + aValue) / myZoom;

	myView.zoom(tempMultiplier);

	myZoom = myZoom * tempMultiplier;
	((Scene*)myParent)->SetView(myView);

	//Window::CurrentWindow->GetRawWindow()->setView(myView);

	//for (Node* child : myChildren)
	//{
	//	float tempXMultiplier = (myView.getSize().x * myZoom) / myView.getSize().x;
	//	float tempYMultiplier = (myView.getSize().y * myZoom) / myView.getSize().y;
	//	sf::Vector2f tempDiff = child->GetPosition()- GetPosition();
	//	child->SetPosition(sf::Vector2f(tempXMultiplier * tempDiff.x, tempYMultiplier * tempDiff.y));
	//}
}

float Camera::GetZoom()
{
	return myZoom;
}

sf::Vector2f Camera::ScreenToWorldPoint(sf::Vector2f aPosition)
{
	sf::View tempView = Window::CurrentWindow->GetRawWindow()->getView();
	Window::CurrentWindow->GetRawWindow()->setView(myView);

	sf::Vector2f tempResult = (sf::Vector2f)Window::CurrentWindow->GetRawWindow()->mapPixelToCoords((sf::Vector2i)aPosition);
	Window::CurrentWindow->GetRawWindow()->setView(tempView);
	return tempResult;

}


sf::Vector2f Camera::ScreenToWorldPoint(sf::Vector2i aPosition)
{
	sf::View tempView = Window::CurrentWindow->GetRawWindow()->getView();
	Window::CurrentWindow->GetRawWindow()->setView(myView);

	sf::Vector2f tempResult = (sf::Vector2f)Window::CurrentWindow->GetRawWindow()->mapPixelToCoords(aPosition);
	Window::CurrentWindow->GetRawWindow()->setView(tempView);

	return tempResult;
}

sf::Vector2i Camera::WorldToScreenPoint(sf::Vector2f aPosition)
{
	sf::View tempView = Window::CurrentWindow->GetRawWindow()->getView();
	Window::CurrentWindow->GetRawWindow()->setView(myView);

	sf::Vector2i tempResult = Window::CurrentWindow->GetRawWindow()->mapCoordsToPixel(aPosition);
	Window::CurrentWindow->GetRawWindow()->setView(tempView);

	return tempResult;

}
