#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
class Node
{
public:
	inline Node() { myParent = nullptr; };
	Node(const sf::Vector2f& aPosition, Node *aParent);
	~Node();
	virtual void OnUpdate() = 0;
	virtual void OnRender(sf::RenderWindow *aWindow) = 0;
	virtual void SetPosition(const sf::Vector2f& aPosition);
	sf::Vector2f GetPosition() const;
	void SetActive(const bool& aState);
	bool GetActive();
	void AddChild(Node* aChild);

	template <typename T>
	T* GetChild(const int& anIndex)
	{
		return (T*)myChildren[anIndex];
	}

protected:
	bool myActive = true;
	Node* myParent;
	std::vector<Node*> myChildren;
	sf::Vector2f myPosition;
};

