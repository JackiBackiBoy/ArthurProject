#ifndef UIELEMENT_HEADER
#define UIELEMENT_HEADER

#include "SFML/System.hpp"
#include "Nodes/Node.h"
  
class UIElement : public Node
{
public:
	UIElement() : Node({ 0, 0 }, nullptr) {};
	UIElement(const sf::Vector2f& aPosition) : Node(aPosition, nullptr) {};

	inline void OnUpdate() override { Node::OnUpdate(); };
	inline void OnRender(sf::RenderWindow* aWindow) override { Node::OnRender(aWindow); };
};
#endif