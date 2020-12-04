#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef SCENE_H 
#define SCENE_H

class Scene;

class Node
{
public:
	inline Node() { myParent = nullptr; };
	Node(const sf::Vector2f& aPosition, const std::string& aName);
	~Node();
	virtual void OnUpdate() = 0;
	virtual void OnRender(sf::RenderWindow *aWindow) = 0;
	virtual void OnStart();
	virtual void SetPosition(const sf::Vector2f& aPosition);
	sf::Vector2f GetPosition() const;
	void SetActive(const bool& aState);
	bool GetActive();
	void AddChild(Node* aChild);
	void OrphanChild(Node* aChild);
	Scene* GetActiveScene();

	template <typename T>
	T* GetChild(const std::string& aName)
	{
		for (int i = 0; i < myChildren.size(); i++)
		{
			if (myChildren.at(i)->myName == aName)
			{
				return (T*)myChildren.at(i);
			}
		}
		return nullptr;
	}

protected:
	bool myActive = true;
	Node* myParent;
	std::vector<Node*> myChildren;
	sf::Vector2f myPosition;
	std::string myName;
};
#endif 