#include "BoxCollider.h"

BoxCollider::BoxCollider(const sf::Vector2f& aPosition, const std::string& aName, int aWidth, int aHeight, const ColliderMaterial& aColMat): PolygonCollider(aPosition, aName, 4, 1,aColMat ), myWidth(aWidth), myHeight(aHeight)
{

}

void BoxCollider::OnStart()
{
	PolygonCollider::OnStart();
	((PolygonShape*)myBody->shape)->SetBox(myWidth / 2.f, myHeight/ 2.f);
}

void BoxCollider::OnUpdate()
{
	PolygonCollider::OnUpdate();
}

void BoxCollider::OnRender(sf::RenderWindow* aWindow)
{
	PolygonCollider::OnRender(aWindow);
}

void BoxCollider::SetWidth(int aVal)
{
	myWidth = aVal;
	((PolygonShape*)myBody->shape)->SetBox(myWidth / 2.f, myHeight / 2.f);
}

void BoxCollider::SetHeight(int aVal)
{
	myHeight = aVal;
	((PolygonShape*)myBody->shape)->SetBox(myWidth / 2.f, myHeight / 2.f);
}

int BoxCollider::GetWidth()
{
	return myWidth;
}

int BoxCollider::GetHeight()
{
	return myHeight;
}
