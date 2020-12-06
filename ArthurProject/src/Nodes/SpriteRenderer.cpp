#include "SpriteRenderer.h"
SpriteRenderer::SpriteRenderer(const sf::Vector2f& aPosition, const std::string& aName, const sf::Texture& aTexture) : Node(aPosition, aName) 
{
	aSprite = new sf::Sprite(aTexture);
	aSprite->setPosition(GetPosition());
}

void SpriteRenderer::OnRender(sf::RenderWindow* aWindow)
{
	aSprite->setPosition(GetPosition());
	aWindow->draw(*aSprite);
	Node::OnRender(aWindow);
}

void SpriteRenderer::SetPosition(const sf::Vector2f& aPosition)
{
	Node::SetPosition(aPosition);
	aSprite->setPosition(GetPosition());
}