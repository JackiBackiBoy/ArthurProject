#include "AABB.h"

std::vector<AABB*> AABB::Rects = std::vector<AABB*>();

AABB::AABB(sf::Vector2f aPosition, std::string aName, sf::Vector2f aSize) : Node(aPosition, aName), mySize(aSize)
{
	Rects.push_back(this);
}

void AABB::OnUpdate()
{
	Node::OnUpdate();
}

void AABB::OnRender(sf::RenderWindow* aWindow)
{
	Node::OnRender(aWindow);

	/*return;*/

	//Debug
	sf::VertexArray tempVArr(sf::PrimitiveType::LineStrip, 5);
	sf::Vector2f tempPos = GetPosition();
	tempVArr[0].position = sf::Vector2f(tempPos.x, tempPos.y);
	tempVArr[1].position = sf::Vector2f(tempPos.x + mySize.x, tempPos.y);
	tempVArr[2].position = sf::Vector2f(tempPos.x + mySize.x, tempPos.y + mySize.y);
	tempVArr[3].position = sf::Vector2f(tempPos.x, tempPos.y + mySize.y);
	tempVArr[4].position = sf::Vector2f(tempPos.x, tempPos.y);

	for (int i = 0; i < 5; i++)
	{
		tempVArr[i].color = sf::Color::Blue;
	}
	aWindow->draw(tempVArr);
}


std::vector<AABB*> AABB::GetIntersecting()
{

	std::vector<AABB*> tempRects;
	for (int i = 0; i < Rects.size(); i++)
	{
		if (Rects[i] == this)
		{
			continue;
		}

		if (Intersects(Rects[i]))
		{
			tempRects.push_back(Rects[i]);
		}
	}

	return tempRects;
}

std::vector<AABB*> AABB::GetIntersecting(std::string aName)
{
	std::vector<AABB*> tempRects;
	for (int i = 0; i < Rects.size(); i++)
	{
		if (Rects[i] == this)
		{
			continue;
		}
		if (Rects[i]->myName == aName)
		{
			if (Intersects(Rects[i]))
			{
				tempRects.push_back(Rects[i]);
			}
		}
	}

	return tempRects;
}

bool AABB::Intersects(std::string aName)
{
	bool tempCollided = false;
	for (int i = 0; i < Rects.size(); i++)
	{
		if (Rects[i] == this)
		{
			continue;
		}
		if (Rects[i]->myName == aName)
		{
			if (Intersects(Rects[i]))
			{
				return true;
			}
		}
	}

	return false;
}

bool AABB::Intersects(AABB* aRect)
{
	sf::Vector2f tempPos = GetPosition();
	sf::Vector2f tempOtherPos = aRect->GetPosition();
	if (tempPos.x < tempOtherPos.x + aRect->GetSize().x &&
		tempPos.x + mySize.x > tempOtherPos.x &&
		tempPos.y < tempOtherPos.y + aRect->GetSize().y &&
		tempPos.y + mySize.y > tempOtherPos.y)
	{
		// collision detected!
		return true;
	}

	return false;
}

sf::Vector2f AABB::GetSize()
{
	return mySize;
}
