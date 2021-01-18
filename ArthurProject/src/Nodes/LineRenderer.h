#pragma once
#include "SpriteRenderer.h"
class LineRenderer :
    public SpriteRenderer
{
public:
    LineRenderer(sf::Vector2f aPosition, std::string aName, std::vector<sf::Vector2f> somePoints);
    void OnUpdate() override;
    void OnRender(sf::RenderWindow* aWindow) override;
private:
    std::vector<sf::Vector2f> myPoints;
    bool myWorldPositionFlag = false;
};

