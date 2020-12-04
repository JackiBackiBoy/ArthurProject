#include "Scene.h"
#include "TimeTracker.h"
void Scene::OnUpdate()
{
	Node::OnUpdate();


	// Generate new collision info
	myContacts.clear();
	for (unsigned int i = 0; i < myBodies.size(); ++i)
	{
		Body* A = myBodies[i];

		for (unsigned int j = i + 1; j < myBodies.size(); ++j)
		{
			Body* B = myBodies[j];
			if (A->im == 0 && B->im == 0)
				continue;
			Manifold m(A, B);
			m.Solve();
			if (m.contact_count)
				myContacts.emplace_back(m);
		}
	}

	// Integrate forces
	for (unsigned int i = 0; i < myBodies.size(); ++i)
		IntegrateForces(myBodies[i], TimeTracker::GetDeltaTime());

	// Initialize collision
	for (unsigned int i = 0; i < myContacts.size(); ++i)
		myContacts[i].Initialize();

	// Solve collisions
	for (unsigned int i = 0; i < myContacts.size(); ++i)
		myContacts[i].ApplyImpulse();

	// Integrate velocities
	for (unsigned int i = 0; i < myBodies.size(); ++i)
		IntegrateVelocity(myBodies[i], TimeTracker::GetDeltaTime());

	// Correct positions
	for (unsigned int i = 0; i < myContacts.size(); ++i)
		myContacts[i].PositionalCorrection();

	// Clear all forces
	for (unsigned int i = 0; i < myBodies.size(); ++i)
	{
		Body* b = myBodies[i];
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

void Scene::AddBody(Body* aBody)
{
	myBodies.push_back(aBody);
}
void Scene::RemoveBody(Body* aBody)
{
	myBodies.erase(std::find(myBodies.begin(), myBodies.end(), aBody));
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

	b->position += b->velocity * dt;
	b->orient += b->angularVelocity * dt;
	b->SetOrient(b->orient);
	IntegrateForces(b, dt);
}
