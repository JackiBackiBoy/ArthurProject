#pragma once
#include "Nodes\Node.h"
#include "core/Window.h"
#include "Nodes/PolygonCollider.h"
#include "box2d/box2d.h"

#ifndef NODE_H
#define NODE_H

class Node;

class Scene : public Node
{
public:
	Scene();
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void SetView(sf::View aView);
	b2Body* AddPolygon(const b2PolygonShape aShape,const float& aDensity);
private:

	sf::View myView;

	static b2World myB2World;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;




};

#endif