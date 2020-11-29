#include "core/Window.h"
#include "SFML/Graphics.hpp"
#include "ui/UIText.h"
#include "Managers/AssetManager.h"
#include "Managers/MusicManager.h"
#include "Nodes/AudioSource.h"
#include "TimeTracker.h"
#include "Nodes\Scene.h"
#include "Nodes\Bush.h"
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

		myCamera = new Camera(sf::Vector2f(0,0), myScene);

		tempText = new UIText(sf::Vector2f(0, 0), myScene, "Arthur Project", sf::Color::Cyan, "Fonts/ArialCE", 60);

		//new UIButton(sf::Vector2f(myWidth - 50, 0), myScene, new UIText(sf::Vector2f(0, 0), nullptr, "O", sf::Color::Black, "Fonts/ArialCE", 50), 50, 50, sf::Color::Green, [this]() { myOptionsHolder->SetActive(!myOptionsHolder->GetActive()); });
		//Options
		myOptionsHolder = new UIText(sf::Vector2f(myWidth - 300, 0), myScene, "Options", sf::Color::Cyan, "Fonts/ArialCE", 30, false);

		myOptionsHolder->AddChild(new UIText(sf::Vector2f(-50, 30), nullptr, "Master Volume:" + std::to_string((int)Options::GetMasterVolume()), sf::Color::Cyan, "Fonts/ArialCE", 20, false));
		myOptionsHolder->GetChild<UIText>(0)->AddChild(new UIButton(sf::Vector2f(170, 0), nullptr, new UIText(sf::Vector2f(0, 0), nullptr, "+", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetMasterVolume() < 100)  Options::SetMasterVolume(Options::GetMasterVolume() + 10); ; }));
		myOptionsHolder->GetChild<UIText>(0)->AddChild(new UIButton(sf::Vector2f(-20, 0), nullptr, new UIText(sf::Vector2f(0, 0), nullptr, "-", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetMasterVolume() > 0)Options::SetMasterVolume(Options::GetMasterVolume() - 10); }));

		myOptionsHolder->AddChild(new UIText(sf::Vector2f(-50, 50), nullptr, "Sound Effects:" + std::to_string((int)Options::GetSoundEffectVolume()), sf::Color::Cyan, "Fonts/ArialCE", 20, false));
		myOptionsHolder->GetChild<UIText>(1)->AddChild(new UIButton(sf::Vector2f(170, 0), nullptr, new UIText(sf::Vector2f(0, 0), nullptr, "+", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetSoundEffectVolume() < 100)Options::SetSoundEffectVolume(Options::GetSoundEffectVolume() + 10); }));
		myOptionsHolder->GetChild<UIText>(1)->AddChild(new UIButton(sf::Vector2f(-20, 0), nullptr, new UIText(sf::Vector2f(0, 0), nullptr, "-", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetSoundEffectVolume() > 0)Options::SetSoundEffectVolume(Options::GetSoundEffectVolume() - 10); }));

		myOptionsHolder->AddChild(new UIText(sf::Vector2f(-50, 70), nullptr, "Music Volume:" + std::to_string((int)Options::GetMusicVolume()), sf::Color::Cyan, "Fonts/ArialCE", 20, false));
		myOptionsHolder->GetChild<UIText>(2)->AddChild(new UIButton(sf::Vector2f(170, 0), nullptr, new UIText(sf::Vector2f(0, 0), nullptr, "+", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetMusicVolume() < 100)Options::SetMusicVolume(Options::GetMusicVolume() + 10); }));
		myOptionsHolder->GetChild<UIText>(2)->AddChild(new UIButton(sf::Vector2f(-20, 0), nullptr, new UIText(sf::Vector2f(0, 0), nullptr, "-", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { if (Options::GetMusicVolume() > 0)Options::SetMusicVolume(Options::GetMusicVolume() - 10); }));

		myOptionsHolder->AddChild(new UIButton(sf::Vector2f(0, 100), nullptr, new UIText(sf::Vector2f(0, 0), nullptr, "Save", sf::Color::Black, "Fonts/ArialCE", 20), 20, 20, sf::Color::White, []() { Options::Save(); }));

		tempText = new UIText(sf::Vector2f(0, 0), nullptr, "Play", sf::Color::Black, "Fonts/ArialCE", 60);
		tempButton = new UIButton(sf::Vector2f(100, 100), myScene, tempText, 100, 30, sf::Color::White, K);
	}

	void OnUpdate() override
	{
		TimeTracker::Update();
		MusicManager::OnUpdate();
		sf::Listener::setGlobalVolume(Options::GetMasterVolume());

		myOptionsHolder->GetChild<UIText>(0)->SetText("Master Volume:" + std::to_string((int)Options::GetMasterVolume()));
		myOptionsHolder->GetChild<UIText>(1)->SetText("Sound Effects:" + std::to_string((int)Options::GetSoundEffectVolume()));
		myOptionsHolder->GetChild<UIText>(2)->SetText("Music Volume:" + std::to_string((int)Options::GetMusicVolume()));


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
		//tempButton->OnRender(myRawWindow);

		if (anItem != nullptr)
		{
			anItem->OnRender(myRawWindow);
		}
		myScene->OnRender(myRawWindow);
	}

private:
	UIText* tempText;
	UIButton* tempButton;
};

Window* BuildWindow()
{
	return new Sandbox("Arthur", 1280, 720);
}