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
	void OnUpdate();
	void OnRender(sf::RenderWindow *aWindow);
	void SetActive(const bool& aState);
	bool GetActive();
	void SetPosition(const sf::Vector2f& aPosition);
	sf::Vector2f GetPosition();

protected:
	bool myActive = true;
	Node* myParent;
	std::vector<Node*> myChildren;
	sf::Vector2f myPosition;
};

