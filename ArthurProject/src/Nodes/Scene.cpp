#include "Scene.h"
#include "TimeTracker.h"

b2World Scene::myB2World = b2World(b2Vec2(0.0f, 10.0f));

Scene::Scene() : Node(sf::Vector2f(0, 0), "Scene")
{
	myView = Window::CurrentWindow->GetRawWindow()->getDefaultView();
}
void Scene::OnUpdate()
{
	myB2World.Step(TimeTracker::GetDeltaTime(), velocityIterations, positionIterations);
	Node::OnUpdate();
}
void Scene::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->setView(myView);
	Node::OnRender(aWindow);

	if (myGroundVerts.size() != 0)
	{
		myGroundVerts.resize(myGroundVerts.size());
		int vCount = myGroundVerts.size() + 1;
		sf::VertexArray tempVArr(sf::PrimitiveType::LineStrip, vCount);
		for (int i = 0; i < vCount; i++)
		{
			sf::Vector2f tempPos = myGroundVerts[i % (vCount - 1)];
			tempVArr[i].position = tempPos;
			tempVArr[i].color = sf::Color::White;
		}
		aWindow->draw(tempVArr);
	}
}

void Scene::SetView(sf::View aView)
{
	myView = aView;
}

b2Body* Scene::AddPolygon(const b2PolygonShape aShape, const float& aDensity)
{
	b2BodyDef tempDef;
	tempDef.type = b2_dynamicBody;
	tempDef.fixedRotation = true;

	b2Body* tempBody = myB2World.CreateBody(&tempDef);
	tempBody->CreateFixture(&aShape, aDensity);

	return tempBody;
}

void Scene::AddGround(const std::vector<sf::Vector2f>& someVertices, const int& aCount)
{
	myGroundVerts = someVertices;

	int tempVertexGroupLength;
	for (int i = 0; i < aCount - 2; i += tempVertexGroupLength - 1)
	{
		tempVertexGroupLength = 1;
		b2Vec2 tempA;
		b2Vec2 tempB;
		int tempVIndex;
		do
		{
			tempVIndex = tempVertexGroupLength++ + i;
			if (tempVIndex == aCount - 1)
			{
				break;
			}
			tempA = b2Vec2((someVertices[tempVIndex] - someVertices[tempVIndex - 1]).x, (someVertices[tempVIndex] - someVertices[tempVIndex - 1]).y);
			tempB = b2Vec2((someVertices[tempVIndex + 1] - someVertices[tempVIndex]).x, (someVertices[tempVIndex + 1] - someVertices[tempVIndex]).y);
		} while (atan2(-tempA.y, tempA.x) >= atan2(-tempB.y, tempB.x));
		b2Vec2* tempPolygonVertices = new b2Vec2[tempVertexGroupLength];
		for (int j = 0; j < tempVertexGroupLength; j++)
		{
			tempPolygonVertices[j] = b2Vec2(someVertices[i + j].x, someVertices[i + j].y);
		}
		b2PolygonShape tempShape;
		tempShape.Set(tempPolygonVertices, tempVertexGroupLength);
		AddPolygon(tempShape, 0);
	}
}




