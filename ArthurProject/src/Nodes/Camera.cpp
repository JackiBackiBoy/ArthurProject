#include "Camera.h"
#include "core/Window.h"

Camera::Camera(const sf::Vector2f& aPosition, Node* aParent)
{
	myView = sf::View(aPosition, (sf::Vector2f)Window::CurrentWindow->GetRawWindow()->getSize());
	Window::CurrentWindow->GetRawWindow()->setView(myView);
}

void Camera::OnUpdate()
{
	Node::OnUpdate();

	myView.setCenter(GetPosition().x, GetPosition().y);
}

sf::Vector2f Camera::ScreenToWorldPoint(sf::Vector2f aVector)
{
	myView.getInverseTransform().getMatrix();
}
