#include "SpriteRenderer.h"
SpriteRenderer::SpriteRenderer(const sf::Vector2f& aPosition, Node* aParent, const std::string& aName, const sf::Texture& aTexture) : Node(aPosition, aParent, aName) 
{
	aSprite = new sf::Sprite(aTexture);
	aSprite->setPosition(GetPosition());
}

void SpriteRenderer::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(*aSprite);
	Node::OnRender(aWindow);
}

void SpriteRenderer::SetPosition(const sf::Vector2f& aPosition)
{
	Node::SetPosition(aPosition);
	aSprite->setPosition(GetPosition());
}