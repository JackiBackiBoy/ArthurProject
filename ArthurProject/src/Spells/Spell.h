#pragma once
#include "SFML/Graphics.hpp"
class Spell
{
public: 
	Spell(const std::string& aName, const std::string& aDescription, const int& aManaCost, const float& aCooldown,const bool& aUnlockedFlag, sf::Texture* aTexture);
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnRender(sf::RenderWindow* aWindow);
	virtual void Activate();
	float GetCooldownTimer();
	float GetCooldownTimerPercent();
	float GetManaCost();
	sf::Texture* GetTexture();
	void Unlock();
private:
	bool myUnlockedFlag;
	sf::Texture* myTexture;
	std::string myName = "Null";
	std::string myDescription = "Null";
	float myManaCost = 0;
	float myCooldown = 1;
	float myCooldownTimer;
};

