#pragma once
#include "Nodes\Node.h"
#include "core/Window.h"
class Scene : public Node
{
public:
	inline Scene() : Node(sf::Vector2f(0, 0), "Scene") { myView = Window::CurrentWindow->GetRawWindow()->getDefaultView(); };
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void SetView(sf::View aView);
private:
	sf::View myView;
};

