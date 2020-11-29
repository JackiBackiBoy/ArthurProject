#pragma once
#include "SpriteRenderer.h"
class Animator : public SpriteRenderer
{
public:
	Animator() : SpriteRenderer({ 0, 0 }, "Animator", sf::Texture()) {};
	Animator(const sf::Vector2f& aPosition, const std::string& aName, const sf::Texture& aSpriteSheet);
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
};

