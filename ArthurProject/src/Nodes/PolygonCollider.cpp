#include "PolygonCollider.h"
#include "core/Math.h"
#include "Nodes/Scene.h"

PolygonCollider::PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, int aVertexCount, sf::Vector2f* someVertices, const ColliderMaterial& aColMat) : Node(aPosition, aName), myVertexCount(aVertexCount)
{
	myRotationFrozenFlag = false;
	Vec2* tempVecArr = new Vec2[myVertexCount];
	for (int i = 0; i < aVertexCount; i++)
	{
		tempVecArr[i] = Vec2(someVertices[i].x, someVertices[i].y);
	}

	PolygonShape tempPolygonShape;
	tempPolygonShape.Set(tempVecArr, aVertexCount);
	delete[] tempVecArr;
	myBody = new Body(&tempPolygonShape, 0, 0);
	myBody->SetOrient(0);

	SetColMat(aColMat);
}

PolygonCollider::PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, int aVertexCount, float aRadius, const ColliderMaterial& aColMat ) : Node(aPosition, aName), myVertexCount(aVertexCount)
{

	myRotationFrozenFlag = false;
	Vec2* tempVecArr = new Vec2[myVertexCount];

	float tempAngle = 2 * PI / myVertexCount;
	for (int i = 0; i < aVertexCount; i++)
	{
		tempVecArr[i] = Vec2(cos(tempAngle * i) * aRadius, sin(tempAngle * i) * aRadius);
	}

	PolygonShape tempPolygonShape;
	tempPolygonShape.Set(tempVecArr, aVertexCount);
	delete[] tempVecArr;
	myBody = new Body(&tempPolygonShape, 0, 0);
	myBody->SetOrient(0);

	SetColMat(aColMat);
}

void PolygonCollider::OnStart()
{
	Node::OnStart();
	myBody->SetPosition(Vec2(GetPosition().x, GetPosition().y));
	GetActiveScene()->AddCollider(this);
}

void PolygonCollider::OnUpdate()
{
	Node::OnUpdate();
	if (myBody->MovedFlag)
	{
		SetPosition(sf::Vector2f(myBody->position.x, myBody->position.y));
	}
}

void PolygonCollider::SetPosition(const sf::Vector2f& aPos)
{
	Node::SetPosition(aPos);
	myBody->SetPosition(Vec2(GetPosition().x, GetPosition().y));
}

void PolygonCollider::OnRender(sf::RenderWindow* aWindow)
{
	Node::OnRender(aWindow);
	int iteration = 0;
	int vCount = ((PolygonShape*)myBody->shape)->m_vertexCount + 1;
	sf::VertexArray tempVBuff(sf::PrimitiveType::LineStrip, vCount);
	for (int i = 0; i < vCount; i++)
	{
		Vec2 tempPos = ((PolygonShape*)myBody->shape)->m_vertices[i % (vCount - 1)];

		tempPos = Vec2(tempPos.x * cos(myBody->orient) - tempPos.y * sin(myBody->orient), tempPos.x * sin(myBody->orient) + tempPos.y * cos(myBody->orient));
		tempVBuff[i].position = sf::Vector2f(tempPos.x + myBody->position.x, tempPos.y + myBody->position.y);
		tempVBuff[i].color = sf::Color::Color(128 * iteration + 127, 128 * iteration + 127, 128 * iteration + 127, 255);

	}
	aWindow->draw(tempVBuff);
	iteration++;
}

void PolygonCollider::SetStatic(bool aFlag)
{
	if (aFlag)
	{
		myBody->SetStatic();
	}
	else
	{
		SetColMat(myColMat);
		if (myRotationFrozenFlag)
		{
			FreezeRotation(true);
		}
	}
}

void PolygonCollider::SetColMat(ColliderMaterial aColMat)
{
	myColMat = aColMat;

	myBody->restitution = aColMat.Bouncyness;
	myBody->dynamicFriction = aColMat.DynamicFriction;
	myBody->staticFriction = aColMat.StaticFriction;
	((PolygonShape*)(myBody->shape))->ComputeMass(aColMat.Density);
}

void PolygonCollider::FreezeRotation(bool aFlag)
{
	myRotationFrozenFlag = aFlag;
	if (aFlag)
	{
		myBody->I = 0;
		myBody->iI = 0;
	}
	else
	{
		if (myBody->m != 0)
		{
			SetColMat(myColMat);
		}
	}
}

void PolygonCollider::SetRotation(float aValue)
{
	myBody->SetOrient(aValue);
}

float PolygonCollider::GetRotation()
{
	return myBody->orient;
}

void PolygonCollider::AddVelocity(const sf::Vector2f& aVal)
{
	myBody->velocity += Vec2(aVal.x, aVal.y);
}

sf::Vector2f PolygonCollider::GetVelocity()
{
	return sf::Vector2f(myBody->velocity.x, myBody->velocity.y);
}

void PolygonCollider::SetVelocity(const sf::Vector2f& aVal)
{
	myBody->velocity = Vec2(aVal.x, aVal.y);
}

Body* PolygonCollider::GetBody()
{
	return myBody;
}


