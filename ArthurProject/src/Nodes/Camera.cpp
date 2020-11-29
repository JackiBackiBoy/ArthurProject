#include "Camera.h"
#include "core/Window.h"


Camera::Camera(const sf::Vector2f& aPosition,std::string aName) : Node(aPosition, aName)
{

	myView = sf::View(aPosition, (sf::Vector2f)Window::CurrentWindow->GetRawWindow()->getSize());
	Window::CurrentWindow->GetRawWindow()->setView(myView);
}

void Camera::OnUpdate()
{
	Node::OnUpdate();

	myView.setCenter(GetPosition().x, GetPosition().y);
}

sf::Vector2f Camera::ScreenToWorldPoint(sf::Vector2f aPosition)
{
	return (sf::Vector2f)Window::CurrentWindow->GetRawWindow()->mapPixelToCoords((sf::Vector2i)aPosition);
}

sf::Vector2f Camera::ScreenToWorldPoint(sf::Vector2i aPosition)
{
	return (sf::Vector2f)Window::CurrentWindow->GetRawWindow()->mapPixelToCoords(aPosition);
}

sf::Vector2i Camera::WorldToScreenPoint(sf::Vector2f aPosition)
{
	return Window::CurrentWindow->GetRawWindow()->mapCoordsToPixel(aPosition);

}
