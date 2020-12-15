#include "SpriteRenderer.h"
SpriteRenderer::SpriteRenderer(const sf::Vector2f& aPosition, const std::string& aName, const sf::Texture& aTexture) : Node(aPosition, aName) 
{

	mySprite = new sf::Sprite(aTexture);
	mySprite->setPosition(GetPosition());
	CenterOrigin();
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

void SpriteRenderer::CenterOrigin()
{
	mySprite->setOrigin((sf::Vector2f)(mySprite->getTexture()->getSize()) / 2.f);
}
