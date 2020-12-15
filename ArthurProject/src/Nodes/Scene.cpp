#include "Scene.h"
#include "TimeTracker.h"
void Scene::OnUpdate()
{
	Node::OnUpdate();


	// Generate new collision info
	myContacts.clear();
	for (unsigned int i = 0; i < myColliders.size(); ++i)
	{
		Body* A = myColliders[i]->GetBody();
		for (unsigned int j = i + 1; j < myColliders.size(); ++j)
		{
			Body* B = myColliders[j]->GetBody();
			if (A->im == 0 && B->im == 0)
				continue;
			Manifold m(A, B);
			m.Solve();
			if (m.contact_count)
				myContacts.emplace_back(m);
		}
	}

	// Integrate forces
	for (unsigned int i = 0; i < myColliders.size(); ++i)
		IntegrateForces(myColliders[i]->GetBody(), TimeTracker::GetDeltaTime());

	// Initialize collision
	for (unsigned int i = 0; i < myContacts.size(); ++i)
		myContacts[i].Initialize();

	// Solve collisions
		for (unsigned int i = 0; i < myContacts.size(); ++i)
			myContacts[i].ApplyImpulse();

	// Integrate velocities
	for (unsigned int i = 0; i < myColliders.size(); ++i)
		IntegrateVelocity(myColliders[i]->GetBody(), TimeTracker::GetDeltaTime());

	// Correct positions
	for (unsigned int i = 0; i < myContacts.size(); ++i)
		myContacts[i].PositionalCorrection();

	// Clear all forces
	for (unsigned int i = 0; i < myColliders.size(); ++i)
	{
		Body* b = myColliders[i]->GetBody();
		b->force.Set(0, 0);
		b->torque = 0;
	}
}
void Scene::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->setView(myView);
	Node::OnRender(aWindow);
}

void Scene::SetView(sf::View aView)
{
	myView = aView;
}

void Scene::AddCollider(PolygonCollider* aCollider)
{
	myColliders.push_back(aCollider);
}
void Scene::RemoveCollider(PolygonCollider* aCollider)
{
	myColliders.erase(std::find(myColliders.begin(), myColliders.end(), aCollider));
}

// see http://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html
void Scene::IntegrateForces(Body* b, float dt)
{
	if (b->im == 0.0f)
		return;

	b->velocity += (b->force * b->im + gravity) * (dt / 2.0f);
	b->angularVelocity += b->torque * b->iI * (dt / 2.0f);
}

void Scene::IntegrateVelocity(Body* b, float dt)
{
	if (b->im == 0.0f)
		return;

	b->SetPosition(Vec2(b->position + b->velocity * dt));
	b->orient += b->angularVelocity * dt;
	b->SetOrient(b->orient);
	IntegrateForces(b, dt);
}
