#pragma once
#include "Nodes\Node.h"
#include "core/Window.h"
#include "core/Body.h"
#include "Nodes/PolygonCollider.h"
class Scene : public Node
{
public:
	inline Scene() : Node(sf::Vector2f(0, 0), "Scene") { myView = Window::CurrentWindow->GetRawWindow()->getDefaultView(); };
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void SetView(sf::View aView);
	void AddBody(Body* aBody);
	void RemoveBody(Body* aBody);
private:
	sf::View myView;
	std::vector<Body*> myBodies;
	std::vector<Manifold> myContacts;
	void IntegrateForces(Body* b, float dt);
	void IntegrateVelocity(Body* b, float dt);




};

