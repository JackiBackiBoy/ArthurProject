#pragma once
#include "Spell.h"
#include "Nodes/SpriteRenderer.h"
class PastTime :
	public Spell
{
public:
	PastTime(const std::string& aName, const std::string& aDescription, const int& aManaCost, const float& aCooldown, const bool& aUnlockedFlag, sf::Texture* aTexture);
	~PastTime();
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void Activate() override;
private:
	std::vector<sf::Vector2f> myPastPositions;
	float myTimeBetweenRecordPos = 0.1f;
	float myTimer;
	bool myActiveFlag = false;
	SpriteRenderer* mySr = nullptr;
};

