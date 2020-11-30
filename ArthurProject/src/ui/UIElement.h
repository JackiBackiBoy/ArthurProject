#ifndef UIELEMENT_HEADER
#define UIELEMENT_HEADER

#include "SFML/System.hpp"
#include "Nodes/Node.h"
  
class UIElement : public Node
{
public:
	UIElement(const sf::Vector2f& aPosition, const std::string& aName) : Node(aPosition, aName) {};

	inline void OnUpdate() override { Node::OnUpdate(); };
	inline void OnRender(sf::RenderWindow* aWindow) override { Node::OnRender(aWindow); };
};
#endif