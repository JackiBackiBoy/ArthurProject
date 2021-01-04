#pragma once
#include "Node.h"
#include "SpriteRenderer.h"
class ResourceBar :
    public Node
{
public:
    ResourceBar(const sf::Vector2f& aPosition, const std::string& aName, const float& aValue, const sf::Texture& aTexture);
    void OnUpdate();
    void OnRender(sf::RenderWindow* aWindow);
    void SetValue(float aValue);
private:
    float myValue;
    void UpdateBar();
    SpriteRenderer* myTargetSr;
};

