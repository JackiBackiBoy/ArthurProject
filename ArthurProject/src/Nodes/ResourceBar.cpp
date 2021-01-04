#include "ResourceBar.h"

ResourceBar::ResourceBar(const sf::Vector2f& aPosition, const std::string& aName, const float& aValue, const sf::Texture& aTexture) : Node(aPosition, aName), myValue(aValue)
{
	myTargetSr = new SpriteRenderer(sf::Vector2f(0, 0), "BarSprite", aTexture);
	AddChild(myTargetSr);
	UpdateBar();

}

void ResourceBar::OnUpdate()
{
	Node::OnUpdate();
}

void ResourceBar::OnRender(sf::RenderWindow* aWindow)
{
	Node::OnRender(aWindow);
}

void ResourceBar::SetValue(float aValue)
{
	myValue = aValue;
	UpdateBar();
}

void ResourceBar::UpdateBar()
{
	myTargetSr->SetTextureRect(sf::IntRect(0, 0, myTargetSr->GetTextureSize().x * myValue, myTargetSr->GetTextureSize().y));
}
