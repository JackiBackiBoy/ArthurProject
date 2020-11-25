#include "Nodes\Bush.h"
#include "..\Managers\AssetManager.h"

Bush::Bush(const sf::Vector2f& aPosition, Node* aParent) : SpriteRenderer(aPosition, aParent, AssetManager::GetTexture("Bush")) 
{

}

void Bush::OnUpdate() 
{
	SpriteRenderer::OnUpdate();
}

void Bush::OnRender(sf::RenderWindow* aWindow)
{
	SpriteRenderer::OnRender(aWindow);
}

void Bush::SetPosition(const sf::Vector2f& aPosition) 
{
	SpriteRenderer::SetPosition(aPosition);
}