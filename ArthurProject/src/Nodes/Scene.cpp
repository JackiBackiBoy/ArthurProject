#include "Scene.h"
#include "TimeTracker.h"
#include "Managers\AssetManager.h"
#include <../Delaunator.hpp>
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

b2World Scene::myB2World = b2World(b2Vec2(0.0f, 10.0f));
Scene* Scene::UiScene = nullptr;

Scene::Scene() : Node(sf::Vector2f(0, 0), "Scene")
{
	myView = Window::CurrentWindow->GetRawWindow()->getDefaultView();
    myB2World.SetGravity(b2Vec2(0,100));
    myDynamicBodies = std::vector<b2Body*>();
}

void Scene::OnStart() 
{
    Node::OnStart();
}

void Scene::OnUpdate()
{
    //for (int j = 0; j < myDynamicBodies.size(); j++) 
    //{
    //    b2Vec2 tempTarget = myDynamicBodies[j]->GetPosition();
    //    for (int i = 0; i < myGround.size(); i++)
    //    {
    //        if (myGround[i]->IsEnabled())
    //        {
    //            b2PolygonShape* tempPS = ((b2PolygonShape*)(myGround[i]->GetFixtureList()->GetShape()));
    //            float tempDistance = FLT_MAX;
    //            for (int j = 0; j < tempPS->m_count; j++)
    //            {
    //                tempDistance = std::min<float>(tempDistance, (myGround[i]->GetPosition() + tempPS->m_vertices[j] - tempTarget).x);
    //            }
    //            myGround[i]->SetEnabled(tempDistance < 20);
    //        }  
    //    }
    //}

	myB2World.Step(TimeTracker::GetDeltaTime(), velocityIterations, positionIterations);
	Node::OnUpdate();
}
void Scene::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->setView(myView);
	Node::OnRender(aWindow);
    if (myGroundVerts.size() != 0) 
    {
        aWindow->draw(myVertArr, &texture);
        for (int j = 0; j < myGroundVerts.size(); j++) 
        {      
            int vCount = myGroundVerts[j].size() + 1;
            sf::VertexArray tempVArr(sf::PrimitiveType::LineStrip, vCount);
            for (int i = 0; i < vCount; i++)
            {
                sf::Vector2f tempPos = myGroundVerts[j][i % (vCount - 1)];
                tempVArr[i].position = tempPos;
                if (myGround[j]->IsEnabled()) 
                {
                    tempVArr[i].color = sf::Color::Green;
                }
                else
                {
                    tempVArr[i].color = sf::Color::Red;
                }
            }
            aWindow->draw(tempVArr);          
        }
    }
}

void Scene::SetView(sf::View aView)
{
	myView = aView;
}

b2Body* Scene::AddPolygon(const b2PolygonShape aShape, const float& aDensity, int16 aGroup, int16 aMask)
{
	b2BodyDef tempDef;
	tempDef.type = b2_dynamicBody;
	tempDef.fixedRotation = true;

	b2Body* tempBody = myB2World.CreateBody(&tempDef);

    //if (aDensity != 0) 
    //{
    //    myDynamicBodies.push_back(tempBody);
    //}

    b2FixtureDef* tempFixDef = new b2FixtureDef();
	tempFixDef->density = aDensity;
	tempFixDef->shape = &aShape;
	tempFixDef->filter.categoryBits = aGroup;
	tempFixDef->filter.maskBits = aMask;
	tempBody->CreateFixture(tempFixDef);

	return tempBody;
}

b2Body* Scene::AddCircle(const b2CircleShape aCircle, const float& aDensity, int16 aGroup, int16 aMask)
{
    b2BodyDef tempDef;
    tempDef.type = b2_dynamicBody;
    tempDef.fixedRotation = true;

    b2Body* tempBody = myB2World.CreateBody(&tempDef);

    //if (aDensity != 0)
    //{
    //    myDynamicBodies.push_back(tempBody);
    //}

    b2FixtureDef* tempFixDef = new b2FixtureDef();
    tempFixDef->density = aDensity;
    tempFixDef->shape = &aCircle;
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
    std::vector<double> tempCoords = std::vector<double>();
    float floor = -FLT_MAX;
    for (int i = 0; i < someVertices.size(); i++) 
    {
        tempCoords.push_back(someVertices[i].x);
        tempCoords.push_back(someVertices[i].y);
        floor = std::max(floor, someVertices[i].y);
    }
    tempCoords.push_back(someVertices.back().x);
    tempCoords.push_back(floor + 100);        
    tempCoords.push_back(someVertices.front().x);
    tempCoords.push_back(floor + 100);

    using Coord = double;
    using N = uint32_t;
    using Point = std::array<Coord, 2>;
    std::vector<std::vector<Point>> polygon;
    std::vector<Point> points;
    for (int i = 0; i < tempCoords.size(); i += 2) 
    {
        points.push_back({ tempCoords[i], tempCoords[i + 1] });
    }
    polygon.push_back(points);
    std::vector<N> indices = mapbox::earcut<N>(polygon);

    texture = AssetManager::GetTexture("GroundTexture");
    texture.setRepeated(true);
    myVertArr.setPrimitiveType(sf::PrimitiveType::Triangles);
    myVertArr.resize(indices.size());
    for (std::size_t i = 0; i < indices.size(); i++) 
    {
        myVertArr[i] = sf::Vector2f(points[indices[i]][0], points[indices[i]][1]);
        myVertArr[i].texCoords = sf::Vector2f(points[indices[i]][0], points[indices[i]][1]);
    }
    for (int i = 0; i < indices.size(); i += 3) 
    {
        if ((indices[i + 0] < someVertices.size() && indices[i + 1] < someVertices.size()
        ||  indices[i + 0] < someVertices.size() && indices[i + 2] < someVertices.size()
        ||  indices[i + 1] < someVertices.size() && indices[i + 2] < someVertices.size())
        && (std::abs((int)(indices[i + 1] - indices[i + 0])) == 1
        || std::abs((int)(indices[i + 2] - indices[i + 1])) == 1
        || std::abs((int)(indices[i + 2] - indices[i + 0])) == 1))
        {

            b2PolygonShape ps = b2PolygonShape();
            b2Vec2* vec = new b2Vec2[3];
            vec[0] = b2Vec2(points[indices[i + 0]][0], points[indices[i + 0]][1]);
            vec[1] = b2Vec2(points[indices[i + 1]][0], points[indices[i + 1]][1]);
            vec[2] = b2Vec2(points[indices[i + 2]][0], points[indices[i + 2]][1]);
            ps.Set(vec, 3);
            b2Body* b = AddPolygon(ps, 0, CollisionMask::Ground, CollisionMask::All);
            myGround.push_back(b);
            myGroundVerts.push_back({ {vec[0].x,vec[0].y},{vec[1].x, vec[1].y},{vec[2].x, vec[2].y} });
        }
    }
}




