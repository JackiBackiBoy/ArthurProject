#include "core/Window.h"
#include "SFML/Graphics.hpp"
#include "ui/UIText.h"
#include "Managers/AssetManager.h"
#include "Managers/MusicManager.h"
#include "Nodes/AudioSource.h"
#include "TimeTracker.h"
#include "Nodes\Scene.h"
#include "ui\UIButton.h"
#include "Data/SaveLoad.h"
#include "data/Options.h"
#include "Nodes/Camera.h"

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

	float myTimer = 0;

	Scene* myScene;
	Node* anItem;
	Node* myOptionsHolder;
	bool isPressed = false;
	Camera* myCamera;

	static void K()
	{

	}


	void OnStart() override
	{
		AssetManager::Init();
		Options::Load();
		sf::Listener::setGlobalVolume(Options::GetMasterVolume());
		MusicManager::TransitionTo("New Hope");

		myScene = new Scene();
		myScene->AddChild(new UIText(sf::Vector2f(0, 0), "text", "Arthur Project", sf::Color::Cyan, "Fonts/ArialCE", 60));

		myCamera = new Camera(sf::Vector2f(0,0),"MainCam");
		//new UIButton(sf::Vector2f(myWidth - 50, 0), myScene, new UIText(sf::Vector2f(0, 0), nullptr, "O", sf::Color::Black, "Fonts/ArialCE", 50), 50, 50, sf::Color::Green, [this]() { myOptionsHolder->SetActive(!myOptionsHolder->GetActive()); });
		//Options
		myOptionsHolder = new UIText(sf::Vector2f(myWidth - 300, 0), "opthold", "Options", sf::Color::Cyan, "Fonts/ArialCE", 30, false);
		myScene->AddChild(myOptionsHolder);
		myOptionsHolder->AddChild(new UIText(sf::Vector2f(-50, 30), "MasVol", "Master Volume:" + std::to_string((int)Options::GetMasterVolume()), sf::Color::Cyan, "Fonts/ArialCE", 20, false));
		myOptionsHolder->GetChild<UIText>("MasVol")->AddChild(new UIButton(sf::Vector2f(170, 0), "MasVol+", new UIText(sf::Vector2f(0, 0), "text", "+", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetMasterVolume() < 100)  Options::SetMasterVolume(Options::GetMasterVolume() + 10); }));
		myOptionsHolder->GetChild<UIText>("MasVol")->AddChild(new UIButton(sf::Vector2f(-20, 0), "MasVol-", new UIText(sf::Vector2f(0, 0), "text", "-", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetMasterVolume() > 0)Options::SetMasterVolume(Options::GetMasterVolume() - 10); }));

		myOptionsHolder->AddChild(new UIText(sf::Vector2f(-50, 50), "SFX", "Sound Effects:" + std::to_string((int)Options::GetSoundEffectVolume()), sf::Color::Cyan, "Fonts/ArialCE", 20, false));
		myOptionsHolder->GetChild<UIText>("SFX")->AddChild(new UIButton(sf::Vector2f(170, 0), "SFX+", new UIText(sf::Vector2f(0, 0), "text", "+", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetSoundEffectVolume() < 100)Options::SetSoundEffectVolume(Options::GetSoundEffectVolume() + 10); }));
		myOptionsHolder->GetChild<UIText>("SFX")->AddChild(new UIButton(sf::Vector2f(-20, 0), "SFX-", new UIText(sf::Vector2f(0, 0), "text", "-", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetSoundEffectVolume() > 0)Options::SetSoundEffectVolume(Options::GetSoundEffectVolume() - 10); }));

		myOptionsHolder->AddChild(new UIText(sf::Vector2f(-50, 70), "MusVol", "Music Volume:" + std::to_string((int)Options::GetMusicVolume()), sf::Color::Cyan, "Fonts/ArialCE", 20, false));
		myOptionsHolder->GetChild<UIText>("MusVol")->AddChild(new UIButton(sf::Vector2f(170, 0), "MusVol+", new UIText(sf::Vector2f(0, 0), "text", "+", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetMusicVolume() < 100)Options::SetMusicVolume(Options::GetMusicVolume() + 10); }));
		myOptionsHolder->GetChild<UIText>("MusVol")->AddChild(new UIButton(sf::Vector2f(-20, 0), "MusVol-", new UIText(sf::Vector2f(0, 0), "text", "-", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetMusicVolume() > 0)Options::SetMusicVolume(Options::GetMusicVolume() - 10); }));

		myOptionsHolder->AddChild(new UIButton(sf::Vector2f(0, 100), "Save", new UIText(sf::Vector2f(0, 0), "text", "Save", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { Options::Save(); }));

		tempButton = new UIButton(sf::Vector2f(100, 100), "PlayBtn", new UIText(sf::Vector2f(0, 0), "play", "Play", sf::Color::Black, "Fonts/ArialCE", 60), 100, 30, sf::Color::White, K);
		myScene->AddChild(tempButton);
	}

	void OnUpdate() override
	{
		TimeTracker::Update();
		MusicManager::OnUpdate();
		sf::Listener::setGlobalVolume(Options::GetMasterVolume());

		myOptionsHolder->GetChild<UIText>("MasVol")->SetText("Master Volume:" + std::to_string((int)Options::GetMasterVolume()));
		myOptionsHolder->GetChild<UIText>("SFX")->SetText("Sound Effects:" + std::to_string((int)Options::GetSoundEffectVolume()));
		myOptionsHolder->GetChild<UIText>("MusVol")->SetText("Music Volume:" + std::to_string((int)Options::GetMusicVolume()));


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !isPressed)
		{
			//anItem = new Node
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
		//tempButton->OnRender(myRawWindow);

		if (anItem != nullptr)
		{
			anItem->OnRender(myRawWindow);
		}
		myScene->OnRender(myRawWindow);
	}

private:
	UIButton* tempButton;
};

Window* BuildWindow()
{
	return new Sandbox("Arthur", 1280, 720);
}