#include "PolygonCollider.h"
#include "Nodes/Scene.h"

PolygonCollider::PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, float aRadius, const float& aDensity, int16 aGroup, int16 aMask)
	: Node(aPosition, aName)
{
	myRadius = aRadius;
	b2CircleShape tempCS = b2CircleShape();
	tempCS.m_radius = myRadius;
	myBody = GetActiveScene()->AddCircle(tempCS, aDensity, aGroup, aMask);
	SetPosition(aPosition);
}

PolygonCollider::PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, const std::vector<sf::Vector2f>& someVertices , const float& aDensity, int16 aGroup, int16 aMask)
	: Node(aPosition, aName)
{
	myVertices = someVertices;
	b2PolygonShape tempShape = VerticesToShape(someVertices);

	myBody = GetActiveScene()->AddPolygon(tempShape, aDensity, aGroup, aMask);
	myRadius = myBody->GetFixtureList()->GetShape()->m_radius;
	SetPosition(aPosition);
}

PolygonCollider::PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, const float& aWidth, const float& aHeight, const float& aDensity, int16 aGroup, int16 aMask) 
	: Node(aPosition, aName)
{
	myVertices.push_back(sf::Vector2f(0, 0));
	myVertices.push_back(sf::Vector2f(aWidth, 0));
	myVertices.push_back(sf::Vector2f(aWidth, aHeight));
	myVertices.push_back(sf::Vector2f(0, aHeight));
	b2PolygonShape tempShape = VerticesToShape(myVertices);

	myBody = GetActiveScene()->AddPolygon(tempShape, aDensity, aGroup, aMask);
	myRadius = myBody->GetFixtureList()->GetShape()->m_radius;
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


	//return;

	//Debug
	if (myVertices.size() != 0) {
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
	else 
	{
		sf::CircleShape cs = sf::CircleShape(myRadius);
		cs.setPosition(GetPosition());
		cs.setFillColor(sf::Color::Transparent);
		cs.setOutlineColor(sf::Color::White);
		cs.setOutlineThickness(0.5f);
		aWindow->draw(cs);
	}
}

sf::Vector2f PolygonCollider::b2VecToSfVec(const b2Vec2& aVec)
{
	return sf::Vector2f(aVec.x, aVec.y);
}

b2ContactEdge* PolygonCollider::GetCollidedContact()
{
	b2ContactEdge* tempContact = myBody->GetContactList();

	while (tempContact)
	{
		if (tempContact->contact->IsTouching()) {
			return tempContact;
		}
		tempContact = tempContact->next;
	}
	return nullptr;
}

bool PolygonCollider::IsTouching()
{
	b2ContactEdge* tempContact = myBody->GetContactList();

	while (tempContact)
	{
		if (tempContact->contact->IsTouching()) 
		{
			return true;
		}
		tempContact = tempContact->next;
	}
	return false;
}

bool PolygonCollider::IsTouchingGround() 
{
	b2ContactEdge* tempContact = myBody->GetContactList();
	while (tempContact)
	{
		if (tempContact->contact->IsTouching()) 
		{ 
			if (abs(tempContact->contact->GetManifold()->localNormal.x) < 0.8f) //if less than 0.8f (temp value), the collided surface is a slope and can therefore be walked across by the player 
			{
				return true;
			}
		}
		tempContact = tempContact->next;
	}
	return false;
}

bool PolygonCollider::IsTouchingWall()
{
	b2ContactEdge* tempContact = myBody->GetContactList();
	while (tempContact)
	{
		if (tempContact->contact->IsTouching())
		{
			if (abs(tempContact->contact->GetManifold()->localNormal.x) >= 0.8f) //value must be equal to the above function's value (should have made a variable pls no hate) 
			{
				return true;
			}
		}
		tempContact = tempContact->next;
	}
	return false;
}

void PolygonCollider::SetGravityScale(float aValue)
{
	myBody->SetGravityScale(aValue);
}

sf::Vector2f PolygonCollider::GetGroundVector() 
{
	if (IsTouchingGround())
	{
		b2ContactEdge* tempContact = myBody->GetContactList();
		sf::Vector2f tempSurface;
		while (tempContact)
		{
			if (tempContact->contact->IsTouching()) 
			{
				b2Vec2 n = tempContact->contact->GetManifold()->localNormal;
				if (n.x == 0) 
				{
					n.y = -1;
				}
				return sf::Vector2f(-n.y, n.x);
			}
			tempContact = tempContact->next;
		}
	}
	return sf::Vector2f(1, 0);
}
