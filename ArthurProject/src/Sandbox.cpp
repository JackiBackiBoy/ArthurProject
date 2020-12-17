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
#include "Nodes/PlayerController.h"
#include "Nodes/Animator.h"
#include "core/Ray.h"
#include <box2d\box2d.h>

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

	int myIterations = 1;

	AudioSource myAudioSource;
	float myTimer = 0;

	Scene* myScene;
	Scene* myUiScene;
	Node* anItem;
	Camera* myMainCamera;
	float myCameraMoveSpeed = 200;
	bool isPressed = false;

	b2World world = b2World(b2Vec2(0.0f, 10.0f));
	b2Body* bodyA = nullptr;
	b2Body* bodyB = nullptr;
	sf::CircleShape circleA;
	sf::CircleShape circleB;


	const float timeStep = 1.f / 600.f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;

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

		b2CircleShape circle;
		circle.m_radius = 5.f;

		circleA = sf::CircleShape(5.f);
		circleB = sf::CircleShape(5.f);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		bodyA = world.CreateBody(&bodyDef);
		bodyB = world.CreateBody(&bodyDef);
		bodyA->CreateFixture(&circle, 1.0f);
		bodyB->CreateFixture(&circle, 0.0f);

		bodyA->SetTransform(b2Vec2(105.f, -30.f), 0.f);
		bodyB->SetTransform(b2Vec2(100.f, 0.f), 0.f);



		AssetManager::Init();
		myScene = new Scene();
		myUiScene = new Scene();
		myScene->AddChild(new Animator(sf::Vector2f(0, 0), "Animator", std::map<std::string, Animation*>{ {"Blob", &AssetManager::GetAnimation("Animations/Blob")} },"Blob" ) );
		myScene->AddChild(new AudioSource(sf::Vector2f(0, 0), "asd"));
		myScene->GetChild<AudioSource>("asd")->AddChild(new PlayerController(sf::Vector2f(0, 0), "PlayerController", 100,200, 120, 0.1f, 0.1f, 0.25f, 300.f));

		myScene->AddChild(new Camera(sf::Vector2f(0, -50), "MainCamera"));
		myScene->GetChild<Camera>("MainCamera")->Zoom(0.7f);
		myUiScene->AddChild(new UIText(sf::Vector2f(0, 0), "FPStext", "Fps:", sf::Color::White, "Fonts/segoeui", 64));
		myMainCamera = myScene->GetChild<Camera>("MainCamera");


		tempText = new UIText(sf::Vector2f(0, 0), "text", "File", sf::Color::Black, "Fonts/segoeui", 64);

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
		TimeTracker::Update();
	}
	void OnUpdate() override
	{
		TimeTracker::Update();

		myUiScene->GetChild<UIText>("FPStext")->SetText("Fps:" + std::to_string((int)(1 / GetAverageDeltaTime())));

		//Camera Movement (debug)
		if (InputManager::GetKey(sf::Keyboard::Up))
		{
			myMainCamera->SetPosition(myMainCamera->GetPosition() - sf::Vector2f(0, TimeTracker::GetDeltaTime() * myCameraMoveSpeed));
		}
		if (InputManager::GetKey(sf::Keyboard::Left))
		{
			myMainCamera->SetPosition(myMainCamera->GetPosition() - sf::Vector2f(TimeTracker::GetDeltaTime() * myCameraMoveSpeed, 0));
		}
		if (InputManager::GetKey(sf::Keyboard::Down))
		{
			myMainCamera->SetPosition(myMainCamera->GetPosition() + sf::Vector2f(0, TimeTracker::GetDeltaTime() * myCameraMoveSpeed));
		}
		if (InputManager::GetKey(sf::Keyboard::Right))
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
		circleA.setPosition(sf::Vector2f(bodyA->GetWorldPoint(b2Vec2(0, 0)).x, bodyA->GetWorldPoint(b2Vec2(0, 0)).y));
		circleB.setPosition(sf::Vector2f(bodyB->GetWorldPoint(b2Vec2(0, 0)).x, bodyB->GetWorldPoint(b2Vec2(0, 0)).y));
		world.Step(TimeTracker::GetDeltaTime(), velocityIterations, positionIterations);
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
		myRawWindow->draw(circleA);
		myRawWindow->draw(circleB);
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