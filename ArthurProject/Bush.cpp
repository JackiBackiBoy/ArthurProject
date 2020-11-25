#include "Bush.h"

Bush::Bush(const sf::Vector2f& aPosition, Node* aParent) : SpriteRenderer(aPosition, aParent, ) {

}

void Bush::OnUpdate() 
{
	SpriteRenderer::OnUpdate();
}

void Bush::OnRender(sf::RenderWindow* aWindow)
{
	SpriteRenderer::OnRender(aWindow);
}