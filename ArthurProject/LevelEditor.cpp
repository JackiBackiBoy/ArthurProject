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

class LevelEditor : public Window 
{
private:

public:
	LevelEditor(const std::string& aTitle, const int& aWidth, const int& aHeight) : Window(aTitle, aWidth, aHeight) {};


	Scene* myScene;
	Scene* myUIScene;
	Camera* myMainCamera;
	Node* aNode;
	UIWindowsDropDown* myEntityList;
	float myCameraMoveSpeed = 200;

	void MoveCamera()
	{
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
	}

	void OnStart() override
	{
		AssetManager::Init();
		myScene = new Scene();
		myUIScene = new Scene();
		Scene::UiScene = myUIScene;

		myUIScene->AddChild(new UIWindowsDropDown("Entities", sf::Vector2f(0, 0), "EntityList"));
		myEntityList = myUIScene->GetChild<UIWindowsDropDown>("EntityList");
		for (int i = 0; i < 1; i++) 
		{
			myEntityList->AddButton("BushSpawn", [&]() 
			{
				aNode = EntityDatabase::CreateEntity(sf::Vector2f(0, 0), "BushSpawn");
				aNode->AddChild(new UIButton(sf::Vector2f(0, 0), "Select", new UIText(sf::Vector2f(0,0),"","",sf::Color::Black, "arial", 12), 8, 8, sf::Color::Blue, nullptr));
			});
		}

		myScene->AddChild(new Camera(sf::Vector2f(0, -50), "MainCamera"));
		myScene->GetChild<Camera>("MainCamera")->Zoom(0.7f);
		myMainCamera = myScene->GetChild<Camera>("MainCamera");
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
		myUIScene->OnUpdate();
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
		myUIScene->OnRender(myRawWindow);
	}
};

Window* BuildWindow()
{
	return new LevelEditor("LevelEditor", 1280, 720);
}