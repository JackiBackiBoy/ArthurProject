#include "Scene.h"
#include "TimeTracker.h"
void Scene::OnUpdate()
{
	Node::OnUpdate();
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




