#pragma once
#include "Nodes\Node.h"
#include "core/Window.h"
#include "Nodes/PolygonCollider.h"
#include "box2d/box2d.h"

#ifndef NODE_H
#define NODE_H

class Node;

enum CollisionMask
{
	None = 0x0000,
	Ground = 0x0001,
	Player = 0x0002,
	Enemy = 0x0004,
	All = 0xFFFF

};
class Scene : public Node
{
public:
	Scene();
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void OnStart() override;
	void SetView(sf::View aView);
	b2Body* AddPolygon(const b2PolygonShape aShape,const float& aDensity,int16 aGroup, int16 aMask);
	b2Body* AddCircle(const b2CircleShape aCircle, const float& aDensity, int16 aGroup, int16 aMask);
	void AddGround(const std::vector<sf::Vector2f>& someVertices);
	static Scene* UiScene;

private:

	sf::View myView;

	static b2World myB2World;
	const int32 velocityIterations = 1;
	const int32 positionIterations = 1;
	std::vector<b2Body*> myGround;
	std::vector<b2Body*> myDynamicBodies;
	std::vector<std::vector<sf::Vector2f>> myGroundVerts;


};

#endif