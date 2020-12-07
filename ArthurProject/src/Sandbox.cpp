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
#include "Nodes/BoxCollider.h"
#include "Nodes/PlayerController.h"

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

		myScene->AddChild(new BoxCollider(sf::Vector2f(10, -300), "Player",8,18, ColliderMaterial(1,0,0.4f,0.6f)));
		myScene->GetChild<BoxCollider>("Player")->FreezeRotation(true);
		myScene->GetChild<BoxCollider>("Player")->AddChild(new PlayerController(sf::Vector2f(0,0), "PlayerController", 100,600, 500, 120,0.1f, 0.1f, 0.25f, 300.f ));
		myScene->GetChild<BoxCollider>("Player")->AddChild(new SpriteRenderer(sf::Vector2f(-10,-15),"Sprite",AssetManager::GetTexture("Player/Temp")));

		myScene->AddChild(new PolygonCollider(sf::Vector2f(0, 0), "tempGroundCol", 4, 
			new sf::Vector2f[]
			{
				sf::Vector2f(-300,0),
				sf::Vector2f(300,0),
				sf::Vector2f(300,20),
				sf::Vector2f(-300,20),
			}));
		myScene->GetChild<PolygonCollider>("tempGroundCol")->SetStatic(true);

		myScene->AddChild(new BoxCollider(sf::Vector2f(50, 0), "tempGroundCol1", 500, 20));
		myScene->GetChild<PolygonCollider>("tempGroundCol1")->SetStatic(true);
		myScene->GetChild<PolygonCollider>("tempGroundCol1")->SetRotation(PI / 8);


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