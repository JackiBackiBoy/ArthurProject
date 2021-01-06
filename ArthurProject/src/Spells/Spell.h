#pragma once
#include "SFML/Graphics.hpp"
class Spell
{
public: 
	virtual void OnUpdate() = 0;
	virtual void OnRender(sf::RenderWindow aWindow) = 0;
	virtual void Activate();
private:
	sf::Texture* myTexture;
	std::string myName = "Null";
	std::string myDescription = "Null";
	float myManaCost = 0;
	float myCooldown = 1;
	float myCooldownTimer;
};

