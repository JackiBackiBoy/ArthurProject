#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
class Node
{
public:
	Node(const sf::Vector2f& aPosition, Node *aParent);
	~Node();
	virtual void OnUpdate() = 0;
	virtual void OnRender(sf::RenderWindow *aWindow) = 0;
	virtual void SetPosition(const sf::Vector2f& aPosition);
	sf::Vector2f GetPosition();
	void SetActive(const bool& aState);
	bool GetActive();
protected:
	bool myActive = true;
	Node* myParent;
	std::vector<Node*> myChildren;
	sf::Vector2f myPosition;
};

