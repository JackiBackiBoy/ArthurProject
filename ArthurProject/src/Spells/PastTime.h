#pragma once
#include "Spell.h"
class PastTime :
	public Spell
{
public:
	PastTime(const std::string& aName, const std::string& aDescription, const int& aManaCost, const float& aCooldown, const bool& aUnlockedFlag, sf::Texture* aTexture);
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void Activate() override;
};

