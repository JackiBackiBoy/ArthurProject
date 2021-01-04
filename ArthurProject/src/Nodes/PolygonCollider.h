#pragma once
#include "Node.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
class PolygonCollider :
    public Node
{
public:
    PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, const std::vector<sf::Vector2f>& someVertices, const float& aDensity, int16 aGroup, int16 aMask);
    PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, const float& aWidth, const float & aHeight, const float& aDensity, int16 aGroup, int16 aMask);
    void SetPosition(const sf::Vector2f& aPosition) override;
    void SetRotation(const float& anAngle);
    void OnUpdate() override;
    void OnRender(sf::RenderWindow *aWindow) override;
    b2PolygonShape VerticesToShape(const std::vector<sf::Vector2f>& someVertices);

    void SetVelocity(const sf::Vector2f& aVelocity);
    void AddVelocity(const sf::Vector2f aValue);
    sf::Vector2f GetVelocity();
    sf::Vector2f GetGroundVector();
    b2ContactEdge* GetCollidedContact();
    bool IsColliding();
    void SetGravityScale(float aValue);
private:
    b2Body* myBody;

    sf::Vector2f b2VecToSfVec(const b2Vec2& aVec);
    std::vector<sf::Vector2f> myVertices;
};

