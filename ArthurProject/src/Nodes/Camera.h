#pragma once
#include "Node.h"
#include "SFML/Graphics/View.hpp"
class Camera :
    public Node
{
public:
	Camera(const sf::Vector2f& aPosition, Node* aParent);
	~Camera();

	void OnUpdate() override;
	inline void OnRender(sf::RenderWindow* aWindow) override { Node::OnRender(aWindow); };
	sf::Vector2f ScreenToWorldPoint(sf::Vector2f aPosition);

private:
	 sf::View myView;

};

