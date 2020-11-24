#ifndef UIELEMENT_HEADER
#define UIELEMENT_HEADER

#include "SFML/System.hpp"

class UIElement : public Node
{
public:
	UIElement(const sf::Vector2f& aPosition) : Node() {};
};
#endif