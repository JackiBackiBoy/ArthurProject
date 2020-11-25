#ifndef UIELEMENT_HEADER
#define UIELEMENT_HEADER

#include "SFML/System.hpp"
#include "Node.h"

class UIElement : public Node
{
public:
	UIElement(const sf::Vector2f& aPosition) : Node(aPosition, nullptr) {};
};
#endif