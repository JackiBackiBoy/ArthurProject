#include "core/Window.h"
#include "SFML/Graphics.hpp"
#include "ui/UIText.h"
#include "AssetManager.h"

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};

	void OnStart() override
	{
		AssetManager::Init();
		tempText = new UIText("Arthur Project", sf::Vector2f(0, 0), "Fonts/ArialCE", 60);
	}

	void OnUpdate() override
	{
		
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