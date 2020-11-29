#pragma once
#include "Nodes\SpriteRenderer.h"
#include "ui\UIButton.h"
class Bush : public SpriteRenderer
{
public:
	Bush() : SpriteRenderer() {};
	Bush(const sf::Vector2f& aPosition, Node* aParent);
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void SetPosition(const sf::Vector2f& aPosition) override;
};

