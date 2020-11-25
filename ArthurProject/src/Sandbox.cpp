#include "core/Window.h"
#include "SFML/Graphics.hpp"
#include "ui/UIText.h"
#include "Managers/AssetManager.h"
#include "Nodes/AudioSource.h"
#include "TimeTracker.h"

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};


	AudioSource myAudioSource;
	float myTimer = 0;

	void OnStart() override
	{
		AssetManager::Init();
		tempText = new UIText("Arthur Project", sf::Vector2f(0, 0), "Fonts/ArialCE", 60);

		myAudioSource = AudioSource();
	}

	void OnUpdate() override
	{
		TimeTracker::Update();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) && myTimer > 1000)
		{
			myAudioSource.Play("TempAssets/Arrow Flying Past 1");
			myTimer = 0;
		}
		else if (myTimer < 1000)
		{
			myTimer += TimeTracker::GetDeltaTime();

		}
	}

	void OnRender() override
	{
		myRawWindow->draw(*tempText->GetRawText());
	}

private:
	UIText* tempText;
};

Window* BuildWindow()
{
	return new Sandbox("Arthur", 1280, 720);
}