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
#include "data/EntityDatabase.h"
#include "Nodes/ResourceBar.h"
class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

	int myIterations = 1;

	AudioSource myAudioSource;
	float myTimer = 0;

	Scene* myScene;
	Scene* myUiScene;
	Camera* myMainCamera;
	float myCameraMoveSpeed = 200;
	bool isPressed = false;

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

	void CreateUi()
	{
		//Player Health Bar
		myUiScene->AddChild(new ResourceBar(sf::Vector2f(500, 0), "HealthBar", 1.f, AssetManager::GetTexture("UI/HealthBar")));
		myUiScene->GetChild<ResourceBar>("HealthBar")->AddChild(new SpriteRenderer(sf::Vector2f(0, 0), "HealthBarBackground", AssetManager::GetTexture("UI/HealthBarBackground")));
	}

	void OnStart() override
	{


		AssetManager::Init();
		myScene = new Scene();
		myUiScene = new Scene();
		Scene::UiScene = myUiScene;



		CreateUi();
		myScene->AddGround(std::vector<sf::Vector2f>
			{
				sf::Vector2f(-1000, -150),
				sf::Vector2f(-110, -150),
				sf::Vector2f(-100, -100),
				sf::Vector2f(50, 50),
				sf::Vector2f(200, -100),
				sf::Vector2f(190, -150),
				sf::Vector2f(150, -160),
				sf::Vector2f(170, -170),
				sf::Vector2f(230, -150),
				sf::Vector2f(300, -100),
				sf::Vector2f(400, 0)
			});
		myScene->AddChild(EntityDatabase::CreateEntity(sf::Vector2f(0, 0), "Player"));
		myScene->AddChild(EntityDatabase::CreateEntity(sf::Vector2f(-200,-200), "BushSpawn"));

		//myScene->AddChild(new PolygonCollider(sf::Vector2f(-50, 0), "ground", std::vector<sf::Vector2f>{sf::Vector2f(0, 0), sf::Vector2f(100, 0), sf::Vector2f(100, 10), sf::Vector2f(0, 10)}, 0.f));
		//myScene->AddChild(new PolygonCollider(sf::Vector2f(-70, -60), "ground1", 100,10, 0.f));
		//myScene->GetChild<PolygonCollider>("ground1")->SetRotation(3.1415f/4.f);
		myScene->AddChild(new Camera(sf::Vector2f(0, -50), "MainCamera"));
		myScene->GetChild<Camera>("MainCamera")->Zoom(0.7f);
		//myUiScene->AddChild(new UIText(sf::Vector2f(0, 0), "FPStext", "Fps:", sf::Color::White, "Fonts/segoeui", 64));
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

		//myUiScene->GetChild<UIText>("FPStext")->SetText("Fps:" + std::to_string((int)(1 / GetAverageDeltaTime())));

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