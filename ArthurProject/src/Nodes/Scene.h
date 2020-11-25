#pragma once
#include "Nodes\Node.h"
class Scene : public Node
{
public:
	Scene() : Node(sf::Vector2f(0,0), nullptr) {};
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
};

