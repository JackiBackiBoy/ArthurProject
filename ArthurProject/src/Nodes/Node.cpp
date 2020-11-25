#include "Node.h"
Node::Node(const sf::Vector2f& aPosition, Node* aParent) 
{
	myPosition = aPosition;
	myParent = aParent;
}

Node::~Node() 
{
	for (int i = 0; i < myChildren.size(); i++)
	{
		myChildren.at(i)->~Node();
		delete myChildren.at(i);
		myChildren.at(i) = nullptr;
	}
	delete myParent;
	myParent = nullptr;
}

void Node::SetActive(const bool& aState) 
{
	myActive = aState;
}

bool Node::GetActive() 
{
	if (myParent == nullptr) return myActive;
	return myActive + myParent->GetActive();
}

void Node::SetPosition(const sf::Vector2f& aPosition) 
{
	myPosition = aPosition;
}

sf::Vector2f Node::GetPosition() const
{
	if (myParent == nullptr) return myPosition;
	return myPosition + myParent->GetPosition();
}

void Node::OnUpdate()
{
	for (int i = 0; i < myChildren.size(); i++)
	{
		myChildren.at(i)->OnUpdate();
	}
}

void Node::OnRender(sf::RenderWindow* aWindow)
{
	for (int i = 0; i < myChildren.size(); i++)
	{
		myChildren.at(i)->OnRender(aWindow);
	}
}