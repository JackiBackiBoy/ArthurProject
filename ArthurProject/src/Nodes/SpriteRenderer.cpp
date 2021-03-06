#include "SpriteRenderer.h"
SpriteRenderer::SpriteRenderer(const sf::Vector2f& aPosition, const std::string& aName, const sf::Texture& aTexture) : Node(aPosition, aName) 
{

	mySprite = new sf::Sprite(aTexture);
	mySprite->setPosition(GetPosition());
}

void SpriteRenderer::OnRender(sf::RenderWindow* aWindow)
{
	mySprite->setPosition(GetPosition());
	aWindow->draw(*mySprite);
	Node::OnRender(aWindow);
}

void SpriteRenderer::SetPosition(const sf::Vector2f& aPosition)
{
	Node::SetPosition(aPosition);
	mySprite->setPosition(GetPosition());
}

void SpriteRenderer::SetScale(sf::Vector2f aValue)
{
	mySprite->setScale(aValue);
}

void SpriteRenderer::SetRotation(float anAngle) 
{
	mySprite->setRotation(anAngle);
}

void SpriteRenderer::SetTextureRect(const sf::IntRect& aRect)
{
	mySprite->setTextureRect(aRect);
}

sf::Vector2i SpriteRenderer::GetTextureSize()
{
	return (sf::Vector2i)(mySprite->getTexture()->getSize());
}

