#pragma once
#include <string>
#include <map>
#include <Nodes\Node.h>
#include "Nodes/Animator.h"
#include "Nodes/PolygonCollider.h"
#include "Nodes/Behaviours/BushSpawnBehaviour.h"
class EntityDatabase
{
public:
	inline static Node* CreateEntity(sf::Vector2f aPosition, std::string anEntity, int aVariant = 0)
	{
		Node* tempNode = nullptr;

		if (anEntity == "BushSpawn")
		{
			tempNode = new PolygonCollider(aPosition,"BushSpawn", 20,10, 1);
			tempNode->AddChild(new BushSpawnBehaviour());
			tempNode->AddChild(new Animator(sf::Vector2f(-77*0.125f, -10), "Animator", std::map<std::string, Animation*>
			{
				{"LookAround", & AssetManager::GetAnimation("Enemies/BushSpawn/LookAround")},
				{ "Shake", &AssetManager::GetAnimation("Enemies/BushSpawn/Shake") },
				{ "WakeUp", &AssetManager::GetAnimation("Enemies/BushSpawn/WakeUp") },
				{ "AsleepIdle", &AssetManager::GetAnimation("Enemies/BushSpawn/AsleepIdle") },
				{ "ChargeUp", & AssetManager::GetAnimation("Enemies/BushSpawn/ChargeUp") },
				{ "Dash", & AssetManager::GetAnimation("Enemies/BushSpawn/Dash") },
				{ "Exhausted", &AssetManager::GetAnimation("Enemies/BushSpawn/Exhausted") }
			}, "AsleepIdle" ));
			tempNode->GetChild<Animator>("Animator")->SetScale(sf::Vector2f(0.5f , 0.5f));
			tempNode->AddChild(new AABB(sf::Vector2f(-40, -45), "PlayerDetectingCol", sf::Vector2f(100, 100)));
			tempNode->AddChild(new SpriteRenderer(sf::Vector2f(6,-12), "NoticeSprite", AssetManager::GetTexture("Enemies/NoticeSprite")));
			tempNode->GetChild<SpriteRenderer>("NoticeSprite")->SetScale(sf::Vector2f(0.5f, 0.5f));
			tempNode->GetChild<SpriteRenderer>("NoticeSprite")->SetActive(false);
		}
		else if (anEntity == "Player")
		{
			tempNode = new PolygonCollider(sf::Vector2f(-30, -100), "Player", std::vector<sf::Vector2f>{sf::Vector2f(0, 0), sf::Vector2f(16, 0), sf::Vector2f(16, 16), sf::Vector2f(0, 16)}, 1.f);
			tempNode->AddChild(new Animator(sf::Vector2f(0, 0), "Animator", std::map<std::string, Animation*>{ {"Blob", & AssetManager::GetAnimation("Animations/Blob")} }, "Blob"));
			tempNode->AddChild(new PlayerController(sf::Vector2f(0, 0), "PlayerController", 6, 40, 60, 70, 0.1f, 0.1f, 0.25f, 20.f));
			tempNode->AddChild(new AABB(sf::Vector2f(0, 0), "PlayerCollisionBox", sf::Vector2f(16, 16)));

		}

		return tempNode;
	}
};
