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

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};


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

		myScene->AddChild(new SpriteRenderer(sf::Vector2f(0, 0), "aaa", AssetManager::GetTexture("TempAssets/ENEMIES8bit_Blob Death")));

		myScene->AddChild(new Camera(sf::Vector2f(-200, 0), "MainCamera"));
		myUiScene->AddChild(new UIText(sf::Vector2f(0,0), "FPStext", "Fps:", sf::Color::White, "Fonts/segoeui", 64));
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

		//	myAudioSource = AudioSource(sf::Vector2f(0, 0), "AudioSource");
	}

	void OnUpdate() override
	{
		TimeTracker::Update();
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

	void OnRender(bool aUiDrawFlag) override
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