#include "core/Window.h"
#include "SFML/Graphics.hpp"
#include "ui/UIText.h"
#include "ui/windows/UIWindowsButton.h"
#include "ui/windows/UIWindowsDropDown.h"
#include "Managers/AssetManager.h"
#include "Nodes/AudioSource.h"
#include "TimeTracker.h"
#include "Nodes\Scene.h"
#include "Managers/InputManager.h"
#include "Nodes/Camera.h"
#include "Nodes/SpriteRenderer.h"

#include "core/Precompiled.h"

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};


	std::vector<Body*> myBodies;
	std::vector<Manifold> myContacts;
	int myIterations = 1;

	AudioSource myAudioSource;
	float myTimer = 0;

	Scene* myScene;
	Scene* myUiScene;
	Node* anItem;
	Camera* myMainCamera;
	float myCameraMoveSpeed = 200;
	bool isPressed = false;

	float myPastDeltaTime[200];
	int myCurrentPastDeltaTimeIndex;
	float GetAverageDeltaTime()
	{
		myCurrentPastDeltaTimeIndex++;
		if (myCurrentPastDeltaTimeIndex == 200)
		{
			myCurrentPastDeltaTimeIndex = 0;
		}
		myPastDeltaTime[myCurrentPastDeltaTimeIndex] = TimeTracker::GetDeltaTime();
		float tempFloat = 0;
		for (float f : myPastDeltaTime)
		{
			tempFloat += f;
		}
		return (tempFloat / 200);
	}

	void OnStart() override
	{
		AssetManager::Init();
		myScene = new Scene();
		myUiScene = new Scene();


		myScene->AddChild(new PolygonCollider(sf::Vector2f(0, 0), "testCol", 4, 25));
		myScene->AddChild(new PolygonCollider(sf::Vector2f(0, 100), "testCol", 4, 25));

		//myScene->AddChild(new SpriteRenderer(sf::Vector2f(0, 0), "aaa", AssetManager::GetTexture("TempAssets/ENEMIES8bit_Blob Death")));

		myScene->AddChild(new Camera(sf::Vector2f(-200, 0), "MainCamera"));
		myUiScene->AddChild(new UIText(sf::Vector2f(0, 0), "FPStext", "Fps:", sf::Color::White, "Fonts/segoeui", 64));
		myMainCamera = myScene->GetChild<Camera>("MainCamera");


		tempText = new UIText(sf::Vector2f(0, 0), "text", "File", sf::Color::Black, "Fonts/segoeui", 64);
		//tempButton = new UIButton(sf::Vector2f(0, 0), myScene, tempText, 41, 19, sf::Color::White, K);
		tempFileButton = new UIWindowsButton("File", { 41 * 4, 0 }, "FileBtn");
		tempEditButton = new UIWindowsButton("Edit", { 82 * 4, 0 }, "EditBtn");
		//tempFileButton->AddChild(tempEditButton);
		myUiScene->AddChild(tempFileButton);
		myUiScene->AddChild(tempEditButton);

		//std::function<void()> tempFunction = [this]() { std::cout << "bruh" << std::endl; };
		//tempFileButton->SetOnClick(tempFunction);

		tempFileDropDown = new UIWindowsDropDown("File", { 0, 0 }, "FileDD");
		myUiScene->AddChild(tempFileDropDown);
		myScene->OnStart();
		myUiScene->OnStart();
		//	myAudioSource = AudioSource(sf::Vector2f(0, 0), "AudioSource");


		PolygonShape tempPoly = PolygonShape();
		Vec2* tempVecArr = new Vec2[4];
		tempVecArr[0].Set(0, 0);
		tempVecArr[1].Set(50, 0);
		tempVecArr[2].Set(50, 50);
		tempVecArr[3].Set(0, 50);
		tempPoly.Set(tempVecArr, 4);
		delete[] tempVecArr;
		Body* A = new Body(&tempPoly, 0, 0);
		A->SetStatic();
		A->restitution = 0.2f;
		A->dynamicFriction = 0.2f;
		A->staticFriction = 0.4f;
		A->position = Vec2(50, 100);
		A->SetOrient(PI / 8);

		PolygonShape tempPoly1 = PolygonShape();
		Vec2* tempVecArr1 = new Vec2[6];
		tempVecArr1[0].Set(0, 0);
		tempVecArr1[1].Set(25, -10);
		tempVecArr1[2].Set(50, 0);
		tempVecArr1[3].Set(50, 50);
		tempVecArr1[4].Set(0, 50);
		tempVecArr1[5].Set(-25, 25);
		tempPoly1.Set(tempVecArr1, 6);
		delete[] tempVecArr1;
		Body* B = new Body(&tempPoly1, 0, 0);
		B->position = Vec2(50, -100);
		B->SetOrient(PI *1.5f);
		B->restitution = 0.1f;
		B->dynamicFriction = 0.2f;
		B->staticFriction = 0.4f;
		myBodies.push_back(A);
		myBodies.push_back(B);

	}

	// see http://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html
	void IntegrateForces(Body* b, float dt)
	{
		if (b->im == 0.0f)
			return;

		b->velocity += (b->force * b->im + gravity) * (dt / 2.0f);
		b->angularVelocity += b->torque * b->iI * (dt / 2.0f);
	}

	void IntegrateVelocity(Body* b, float dt)
	{
		if (b->im == 0.0f)
			return;

		b->position += b->velocity * dt;
		b->orient += b->angularVelocity * dt;
		b->SetOrient(b->orient);
		IntegrateForces(b, dt);
	}

	void OnUpdate() override
	{
		TimeTracker::Update();


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
		for (unsigned int j = 0; j < myIterations; ++j)
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








		myUiScene->GetChild<UIText>("FPStext")->SetText("Fps:" + std::to_string((int)(1 / GetAverageDeltaTime())));

		//Camera Movement (debug)
		if (InputManager::GetKey(sf::Keyboard::W))
		{
			myMainCamera->SetPosition(myMainCamera->GetPosition() - sf::Vector2f(0, TimeTracker::GetDeltaTime() * myCameraMoveSpeed));
		}
		if (InputManager::GetKey(sf::Keyboard::A))
		{
			myMainCamera->SetPosition(myMainCamera->GetPosition() - sf::Vector2f(TimeTracker::GetDeltaTime() * myCameraMoveSpeed, 0));
		}
		if (InputManager::GetKey(sf::Keyboard::S))
		{
			myMainCamera->SetPosition(myMainCamera->GetPosition() + sf::Vector2f(0, TimeTracker::GetDeltaTime() * myCameraMoveSpeed));
		}
		if (InputManager::GetKey(sf::Keyboard::D))
		{
			myMainCamera->SetPosition(myMainCamera->GetPosition() + sf::Vector2f(TimeTracker::GetDeltaTime() * myCameraMoveSpeed, 0));
		}
		if (InputManager::GetKey(sf::Keyboard::P))
		{
			myMainCamera->Zoom(TimeTracker::GetDeltaTime());
		}
		if (InputManager::GetKey(sf::Keyboard::O))
		{
			myMainCamera->Zoom(-TimeTracker::GetDeltaTime());
		}




		myScene->OnUpdate();
		myUiScene->OnUpdate();
	}

	void OnRender() override
	{
		//myRawWindow->draw(*tempText->GetRawText());
		//tempButton->OnRender(myRawWindow);


		if (anItem != nullptr)
		{
			anItem->OnRender(myRawWindow);
		}
		myScene->OnRender(myRawWindow);

		int iteration = 0;
		for (Body* body : myBodies)
		{
			int vCount = ((PolygonShape*)body->shape)->m_vertexCount + 1;
			sf::VertexArray tempVBuff(sf::PrimitiveType::TrianglesFan, vCount);
			for (int i = 0; i < vCount; i++)
			{
				Vec2 tempPos = ((PolygonShape*)body->shape)->m_vertices[i % (vCount - 1)];

				tempPos = Vec2(tempPos.x * cos(body->orient) - tempPos.y * sin(body->orient), tempPos.x * sin(body->orient) + tempPos.y * cos(body->orient));
				tempVBuff[i].position = sf::Vector2f(tempPos.x + body->position.x, tempPos.y + body->position.y);
				tempVBuff[i].color = sf::Color::Color(128 * iteration + 127, 128 * iteration + 127, 128 * iteration + 127, 255);

			}
			myRawWindow->draw(tempVBuff);
			iteration++;
		}
		myUiScene->OnRender(myRawWindow);
		//tempFileButton->OnRender(myRawWindow);
	}

private:
	UIText* tempText;
	//UIButton* tempButton;
	UIWindowsButton* tempFileButton;
	UIWindowsButton* tempEditButton;
	UIWindowsButton* tempViewButton;
	UIWindowsDropDown* tempFileDropDown;
};

Window* BuildWindow()
{
	return new Sandbox("Arthur", 1280, 720);
}