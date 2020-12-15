#pragma once
#include "Node.h"
class SpriteRenderer : public Node
{
public:
	SpriteRenderer() : Node(sf::Vector2f(0,0), "SpriteRenderer") {};
	SpriteRenderer(const sf::Vector2f& aPosition, const std::string& aName, const sf::Texture& aTexture);
	inline void OnUpdate() override { Node::OnUpdate(); }
	void OnRender(sf::RenderWindow* aWindow) override;
	void SetPosition(const sf::Vector2f& aPosition) override;
protected:
	virtual void CenterOrigin();
	sf::Sprite* mySprite;
};