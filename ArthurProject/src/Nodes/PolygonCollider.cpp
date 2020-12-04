#include "PolygonCollider.h"
#include "core/Math.h"

PolygonCollider::PolygonCollider(sf::Vector2f aPosition, std::string aName, int aVertexCount, sf::Vector2f* someVertices, ColliderMaterial aColMat) : Node(aPosition, aName), myVertexCount(aVertexCount)
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

PolygonCollider::PolygonCollider(sf::Vector2f aPosition, std::string aName, int aVertexCount, float aRadius, ColliderMaterial aColMat ) : Node(aPosition, aName), myVertexCount(aVertexCount)
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
	myBody->position = Vec2(GetPosition().x, GetPosition().y);
}

void PolygonCollider::OnUpdate()
{
	Node::OnUpdate();
}

void PolygonCollider::OnRender(sf::RenderWindow* aWindow)
{
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


