#include "Scene.h"
#include "TimeTracker.h"

b2World Scene::myB2World = b2World(b2Vec2(0.0f, 10.0f));
Scene* Scene::UiScene = nullptr;

Scene::Scene() : Node(sf::Vector2f(0, 0), "Scene")
{
	myView = Window::CurrentWindow->GetRawWindow()->getDefaultView();
    myB2World.SetGravity(b2Vec2(0,100));
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
		for (int j = 0; j < myGroundVerts.size(); j++) 
		{
			int vCount = myGroundVerts[j].size() + 1;
			sf::VertexArray tempVArr(sf::PrimitiveType::LineStrip, vCount);
			for (int i = 0; i < vCount; i++)
			{
				sf::Vector2f tempPos = myGroundVerts[j][i % (vCount - 1)];
				tempVArr[i].position = tempPos;
				tempVArr[i].color = sf::Color::White;
			}
			aWindow->draw(tempVArr);
		}
	}
}

void Scene::SetView(sf::View aView)
{
	myView = aView;
}

b2Body* Scene::AddPolygon(const b2PolygonShape aShape, const float& aDensity,int16 aGroup, int16 aMask)
{
	b2BodyDef tempDef;
	tempDef.type = b2_dynamicBody;
	tempDef.fixedRotation = true;

	b2Body* tempBody = myB2World.CreateBody(&tempDef);

	b2FixtureDef* tempFixDef = new b2FixtureDef();
	tempFixDef->density = aDensity;
	tempFixDef->shape = &aShape;
	tempFixDef->filter.categoryBits = aGroup;
	tempFixDef->filter.maskBits = aMask;
	tempBody->CreateFixture(tempFixDef);

	return tempBody;
}

double perpDot(sf::Vector2f A, sf::Vector2f B)
{
    float a = atan2(A.y, A.x) - atan2(B.y, B.x);
    return a;
}

void Scene::AddGround(const std::vector<sf::Vector2f>& someVertices)
{
    int tempLastEndVert = 0;
    while (tempLastEndVert < someVertices.size() - 1)
    {
        int tempVertCount = 1;
        if (tempLastEndVert + tempVertCount != someVertices.size() - 1)
        {
            while (perpDot(someVertices[tempLastEndVert + tempVertCount + 0] - someVertices[tempLastEndVert + tempVertCount - 1],
                someVertices[tempLastEndVert + tempVertCount + 1] - someVertices[tempLastEndVert + tempVertCount + 0]) < 0)
            {
                //convex and can continue
                tempVertCount++;
                if (tempLastEndVert + tempVertCount == someVertices.size() - 1)
                {
                    break;
                }
            }
        }
        tempVertCount++;
        myGroundVerts.push_back(std::vector<sf::Vector2f>());
        for (int i = 0; i < tempVertCount; i++)
        {
            myGroundVerts.back().push_back(someVertices[tempLastEndVert + i]);
        }
        if (0 == tempVertCount - 2)//lonely surface vector is ordered in a triangle
        {
            sf::Vector2f tempVec = (someVertices[tempLastEndVert + 1] - someVertices[tempLastEndVert]) / 2.f;
            sf::Vector2f tempNewVert = someVertices[tempLastEndVert] + tempVec;
            float tempLen = sqrt(tempVec.x * tempVec.x + tempVec.y * tempVec.y);
            tempVec = sf::Vector2f(-tempVec.y / tempLen, tempVec.x / tempLen) * 2.f;
            tempNewVert += tempVec;
            myGroundVerts.back().push_back(tempNewVert);

            b2PolygonShape tempShape;
            b2Vec2* tempVArr = new b2Vec2[3];
            tempVArr[0] = b2Vec2(someVertices[tempLastEndVert + 0].x, someVertices[tempLastEndVert + 0].y);
            tempVArr[1] = b2Vec2(someVertices[tempLastEndVert + 1].x, someVertices[tempLastEndVert + 1].y);
            tempVArr[2] = b2Vec2(tempNewVert.x, tempNewVert.y);

            tempShape.Set(tempVArr, 3);
            AddPolygon(tempShape, 0, CollisionMask::Ground, 0xFFFF);
        }
        else
        {
            b2PolygonShape tempShape;
            b2Vec2* tempVArr = new b2Vec2[tempVertCount];
            for (int i = 0; i < tempVertCount; i++)
            {
                tempVArr[i] = b2Vec2(someVertices[tempLastEndVert + i].x, someVertices[tempLastEndVert + i].y);
            }
            tempShape.Set(tempVArr, tempVertCount);
            AddPolygon(tempShape, 0, CollisionMask::Ground, 0xFFFF);
        }
        tempLastEndVert += tempVertCount - 1;
    }
}




