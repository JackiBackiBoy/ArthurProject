#include "PolygonCollider.h"
#include "Nodes/Scene.h"

PolygonCollider::PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, const std::vector<sf::Vector2f>& someVertices , const float& aDensity): Node(aPosition, aName)
{
	myVertices = someVertices;
	b2PolygonShape tempShape = VerticesToShape(someVertices);

	myBody = GetActiveScene()->AddPolygon(tempShape, aDensity);
	SetPosition(aPosition);
}

PolygonCollider::PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, const float& aWidth, const float& aHeight, const float& aDensity) : Node(aPosition, aName)
{
	myVertices.push_back(sf::Vector2f(0, 0));
	myVertices.push_back(sf::Vector2f(aWidth, 0));
	myVertices.push_back(sf::Vector2f(aWidth, aHeight));
	myVertices.push_back(sf::Vector2f(0, aHeight));
	b2PolygonShape tempShape = VerticesToShape(myVertices);

	myBody = GetActiveScene()->AddPolygon(tempShape, aDensity);
	SetPosition(aPosition);
}

b2PolygonShape PolygonCollider::VerticesToShape(const std::vector<sf::Vector2f>& someVertices)
{
	b2PolygonShape tempShape;

	b2Vec2* tempVArr = new b2Vec2[someVertices.size()];
	for (int i = 0; i < someVertices.size(); i++)
	{
		tempVArr[i] = b2Vec2(someVertices[i].x, someVertices[i].y);
	}
	tempShape.Set(tempVArr, someVertices.size());

	return tempShape;
}

void PolygonCollider::SetVelocity(const sf::Vector2f& aVelocity)
{
	myBody->SetLinearVelocity(b2Vec2(aVelocity.x, aVelocity.y));
}

void PolygonCollider::AddVelocity(const sf::Vector2f aValue)
{
	myBody->SetLinearVelocity(b2Vec2(myBody->GetLinearVelocity().x + aValue.x, myBody->GetLinearVelocity().y + aValue.y));
}

sf::Vector2f PolygonCollider::GetVelocity()
{
	return sf::Vector2f(myBody->GetLinearVelocity().x, myBody->GetLinearVelocity().y);
}

void PolygonCollider::SetPosition(const sf::Vector2f& aPosition)
{
	Node::SetPosition(aPosition);
	myBody->SetTransform(b2Vec2(aPosition.x, aPosition.y), myBody->GetAngle());
}

void PolygonCollider::SetRotation(const float& anAngle)
{
	myBody->SetTransform(myBody->GetTransform().p, anAngle);
}

void PolygonCollider::OnUpdate()
{
	SetPosition(b2VecToSfVec(myBody->GetPosition()));
	Node::OnUpdate();
}

void PolygonCollider::OnRender(sf::RenderWindow* aWindow)
{
	Node::OnRender(aWindow);



	int vCount = myVertices.size() + 1;
	sf::VertexArray tempVArr(sf::PrimitiveType::LineStrip, vCount);
	for (int i = 0; i < vCount; i++)
	{
		sf::Vector2f tempPos = myVertices[i % (vCount - 1)];
		tempPos = sf::Vector2f(tempPos.x * cos(myBody->GetAngle()) - tempPos.y * sin(myBody->GetAngle()), tempPos.x * sin(myBody->GetAngle()) + tempPos.y * cos(myBody->GetAngle()));
		tempVArr[i].position = sf::Vector2f(tempPos.x + myBody->GetPosition().x, tempPos.y + myBody->GetPosition().y);
		tempVArr[i].color = sf::Color::White;

	}
	aWindow->draw(tempVArr);
}

sf::Vector2f PolygonCollider::b2VecToSfVec(const b2Vec2& aVec)
{
	return sf::Vector2f(aVec.x, aVec.y);
}
