#pragma once
#include "SpriteRenderer.h"
class Animator : public SpriteRenderer
{
public:
	Animator() : SpriteRenderer() {};
	Animator(const sf::Vector2f& aPosition, Node* aParent, const sf::Texture& aSpriteSheet);
	void OnUpdate() override;
	void OnRender(sf::RenderWindow *aWindow) override;
};

