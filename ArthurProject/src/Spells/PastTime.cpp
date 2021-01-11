#include "PastTime.h"
#include <iostream>

PastTime::PastTime(const std::string& aName, const std::string& aDescription, const int& aManaCost, const float& aCooldown, const bool& aUnlockedFlag, sf::Texture* aTexture)
	: Spell(aName, aDescription, aManaCost, aCooldown, aUnlockedFlag, aTexture)
{
}

void PastTime::OnUpdate()
{
	Spell::OnUpdate();
}

void PastTime::OnRender(sf::RenderWindow* aWindow)
{
	Spell::OnRender(aWindow);
}

void PastTime::Activate()
{
	Spell::Activate();
	std::cout << "Activated PastTime";
}
