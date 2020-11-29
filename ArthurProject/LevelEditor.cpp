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

class LevelEditor : public Window 
{
private:

public:
	LevelEditor(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};


	Scene* myScene;
	Node* aNode;

	void OnStart() override
	{
		AssetManager::Init();
		myScene = new Scene();
	}

	void OnUpdate() override
	{
		TimeTracker::Update();

		if (false)//item was selected from menu
		{
			//anItem = new Node()

			//add button to move the selected item around
			//aNode->AddChild(new UIButton({ 0,0 }, "EditHandle", new UIText({ 0,0 }, "fill", "", sf::Color::White, "Fonts/ArialCE", 60), 50, 50, sf::Color::Transparent, );
		}
		if (false)//item was picked up from scene
		{
			//anitem = selected item
		}
		if (false)//item was placed in scene
		{
			myScene->AddChild(aNode);
		}
		if (aNode != nullptr)//updates the selected node to cursor position
		{
			sf::Vector2i tempVector = sf::Mouse::getPosition(*myRawWindow);
			aNode->SetPosition(sf::Vector2f(tempVector.x, tempVector.y));
			aNode->OnUpdate();
		}
		myScene->OnUpdate();
	}

	void OnRender() override
	{
		//myRawWindow->draw(*tempText->GetRawText());
		//tempButton->OnRender(myRawWindow);

		if (aNode != nullptr)//renders the selected node
		{
			aNode->OnRender(myRawWindow);
		}
		myScene->OnRender(myRawWindow);
	}
};

Window* BuildWindow()
{
	return new LevelEditor("LevelEditor", 1280, 720);
}