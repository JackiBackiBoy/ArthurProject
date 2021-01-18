#include "PastTime.h"
#include <iostream>
#include "TimeTracker.h"
#include "data/PlayerInfo.h"
#include "Managers/InputManager.h"
#include "Managers/AssetManager.h"
#include <Nodes\PolygonCollider.h>

PastTime::PastTime(const std::string& aName, const std::string& aDescription, const int& aManaCost, const float& aCooldown, const bool& aUnlockedFlag, sf::Texture* aTexture)
	: Spell(aName, aDescription, aManaCost, aCooldown, aUnlockedFlag, aTexture)
{
}
PastTime::~PastTime()
{
	delete mySr;
}
void PastTime::OnStart()
{
	Spell::OnStart();
	mySr = new SpriteRenderer(sf::Vector2f(0, 0), "Sr", AssetManager::GetTexture("Player/PastTimeShadow"));
}

void PastTime::OnUpdate()
{
	Spell::OnUpdate();
	if (myTimer <= 0)
	{
		myTimer = myTimeBetweenRecordPos;
		myPastPositions.push_back(PlayerInfo::GetNode()->GetPosition());
		if (myPastPositions.size() > 4 / myTimeBetweenRecordPos)
		{
			myPastPositions.erase(myPastPositions.begin());
		}

	}
	else
	{
		myTimer -= TimeTracker::GetDeltaTime();
	}



	if (myActiveFlag)
	{
		if (InputManager::GetKeyUp(sf::Keyboard::Q))
		{
			PlayerInfo::GetNode()->SetPosition(myPastPositions[0]);
			myActiveFlag = false;
			TimeTracker::SetTimeScale(1.f);
			((PolygonCollider*)PlayerInfo::GetNode())->SetVelocity(sf::Vector2f(0,0));
		}

	}
}

void PastTime::OnRender(sf::RenderWindow* aWindow)
{
	Spell::OnRender(aWindow);

	if (myActiveFlag)
	{
		int tempCount = myPastPositions.size();
		sf::VertexArray tempVArr(sf::PrimitiveType::LineStrip, tempCount);
		for (int i = 0; i < tempCount; i++)
		{
			sf::Vector2f tempPos = myPastPositions[i];
			tempPos = sf::Vector2f(tempPos.x, tempPos.y);
			tempVArr[i].position = sf::Vector2f(tempPos.x, tempPos.y);
			tempVArr[i].color = sf::Color::Magenta;

		}
		aWindow->draw(tempVArr);

		mySr->SetPosition(myPastPositions[0]);
		mySr->OnRender(aWindow);
	}

	//return;

	//debug
}

void PastTime::Activate()
{
	Spell::Activate();
	myActiveFlag = true;
	TimeTracker::SetTimeScale(0.6f);
}
