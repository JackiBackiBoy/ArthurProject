#include "core/Window.h"
#include "SFML/Graphics.hpp"
#include "ui/UIText.h"
#include "Managers/AssetManager.h"
#include "Nodes/AudioSource.h"
#include "TimeTracker.h"
#include "Nodes\Scene.h"
#include "Nodes\Bush.h"

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};


	AudioSource myAudioSource;
	float myTimer = 0;

	Scene* myScene;
	Node* anItem;
	bool isPressed = false;
	void OnStart() override
	{
		myScene = new Scene();
		AssetManager::Init();
		tempText = new UIText("Arthur Project", sf::Vector2f(0, 0), sf::Color::Cyan,"Fonts/ArialCE", 60);

		myAudioSource = AudioSource();
	}

	void OnUpdate() override
	{
		TimeTracker::Update();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) && myTimer > 1)
		{
			myAudioSource.Play("TempAssets/Arrow Flying Past 1");
			myTimer = 0;
		}
		else if (myTimer < 1)
		{
			myTimer += TimeTracker::GetDeltaTime();

		}

	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !isPressed)
		{
			anItem = new Bush(sf::Vector2f(0, 0), nullptr);
			//anItem->AddChild(new UIButton());
			isPressed = true;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && isPressed)
		{
			isPressed = false;
			myScene->AddChild(anItem);
			anItem = nullptr;
		}
		if (anItem != nullptr)
		{
			sf::Vector2i tempVector = sf::Mouse::getPosition(*myRawWindow);
			anItem->SetPosition(sf::Vector2f(tempVector.x, tempVector.y));
			anItem->OnUpdate();
		}
		myScene->OnUpdate();
	}

	void OnRender() override
	{
		//myRawWindow->draw(*tempText->GetRawText());
		if (anItem != nullptr)
		{
			anItem->OnRender(myRawWindow);
		}
		myScene->OnRender(myRawWindow);
	}

private:
	UIText* tempText;
};

Window* BuildWindow()
{
	return new Sandbox("Arthur", 1280, 720);
}