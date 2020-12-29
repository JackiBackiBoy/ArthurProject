#pragma once
#include "Node.h"
class AABB :
    public Node
{

public:
    AABB(sf::Vector2f aPosition, std::string aName, sf::Vector2f aSize);
    void OnUpdate() override;
    void OnRender(sf::RenderWindow* aWindow) override;

    std::vector<AABB*> GetIntersecting();
    std::vector<AABB*> GetIntersecting(std::string aName);
    bool Intersects(std::string aName);
    bool Intersects(AABB* aRect);
    sf::Vector2f GetSize();
private:
    sf::Vector2f mySize;
    static std::vector<AABB*> Rects;

};

