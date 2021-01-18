#include "Spell.h"
#include "TimeTracker.h"

Spell::Spell(const std::string& aName, const std::string& aDescription, const int& aManaCost, const float& aCooldown, const bool& aUnlockedFlag, sf::Texture* aTexture)
	:myName(aName), myDescription(aDescription), myManaCost(aManaCost), myCooldown(aCooldown),myUnlockedFlag(aUnlockedFlag), myTexture(aTexture)
{
}

void Spell::OnStart()
{
}

void Spell::OnUpdate()
{
	if (myCooldownTimer > 0)
		myCooldownTimer -= TimeTracker::GetDeltaTime();
}

void Spell::OnRender(sf::RenderWindow* aWindow)
{
}

void Spell::Activate()
{
	myCooldownTimer = myCooldown;
}

float Spell::GetCooldownTimer()
{
	return myCooldownTimer;
}

float Spell::GetCooldownTimerPercent()
{
	return myCooldownTimer / myCooldown;
}

float Spell::GetManaCost()
{
	return myManaCost;
}

sf::Texture* Spell::GetTexture()
{
	return myTexture;
}

void Spell::Unlock()
{
	myUnlockedFlag = true;
}
