#pragma once
#include "Nodes\Node.h"
#include "core/Window.h"
#include "core/Body.h"
#include "Nodes/PolygonCollider.h"

#ifndef NODE_H
#define NODE_H

class Node;

class Scene : public Node
{
public:
	inline Scene() : Node(sf::Vector2f(0, 0), "Scene") { myView = Window::CurrentWindow->GetRawWindow()->getDefaultView(); };
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void SetView(sf::View aView);
	void AddCollider(PolygonCollider* aCollider);
	void RemoveCollider(PolygonCollider* aCollider);
private:
	sf::View myView;
	std::vector<PolygonCollider*> myColliders;
	std::vector<Manifold> myContacts;
	void IntegrateForces(Body* b, float dt);
	void IntegrateVelocity(Body* b, float dt);




};

#endif