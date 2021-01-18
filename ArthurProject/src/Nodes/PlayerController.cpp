#include "PlayerController.h"
#include "Managers/InputManager.h"
#include "TimeTracker.h"
#include "Nodes/Scene.h"
#include "Nodes\Health.h"
#include "Nodes\ResourceBar.h"
#include "data/PlayerInfo.h"
PlayerController::PlayerController(const sf::Vector2f& aPosition, const std::string& aName, float aSpeed, float aJumpHeight,
	float aGroundedTimerValue, float aJumpBufferTimerValue, float aJumpTimerValue, float aFasterFallValue)
	: Node(aPosition, aName), mySpeed(aSpeed), myJumpHeight(aJumpHeight), myGroundedTimerValue(aGroundedTimerValue),
	myJumpBufferTimerValue(aJumpBufferTimerValue), myJumpTimerValue(aJumpTimerValue), myFasterFallValue(aFasterFallValue)
{
}
void PlayerController::OnStart()
{
	myCollider = (PolygonCollider*)myParent;
	myHealth = myParent->GetChild<Health>("Health");
	myHealth->OnTakeDamage.AddListener([&]() { OnTakeDamage(); });
	Node::OnStart();

	for (int i = 0; i < PlayerInfo::GetSpells().size(); i++)
	{
		for (int j = 0; j < PlayerInfo::GetSpells()[i].size(); j++)
		{
			PlayerInfo::GetSpells()[i][j]->OnStart();
		}
	}

}

void PlayerController::OnUpdate()
{
	Node::OnUpdate();

	MagicUpdate();

	GroundCheck();
	Movement();
	Jump();

	if (myInvulnurableTimer <= 0)
	{
		myHealth->SetInvulnurableFlag(false);
	}
	else
	{
		myInvulnurableTimer -= TimeTracker::GetDeltaTime();
	}
}

void PlayerController::OnTakeDamage()
{
	Scene::UiScene->GetChild<ResourceBar>("HealthBar")->SetValue(myHealth->GetHealthPercent());
	myHealth->SetInvulnurableFlag(true);
	myInvulnurableTimer = myInvulnurableTimerValue;
}

void PlayerController::MagicUpdate()
{
	for (int i = 0; i < PlayerInfo::GetSpells().size(); i++)
	{
		for (int j = 0; j < PlayerInfo::GetSpells()[i].size(); j++)
		{
			PlayerInfo::GetSpells()[i][j]->OnUpdate();
		}
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Q))
	{
		PlayerInfo::GetSpells()[myCurrentSpellType][0]->Activate();
	}
}

void PlayerController::OnRender(sf::RenderWindow* aWindow)
{
	Node::OnRender(aWindow);

	for (int i = 0; i < PlayerInfo::GetSpells().size(); i++)
	{
		for (int j = 0; j < PlayerInfo::GetSpells()[i].size(); j++)
		{
			PlayerInfo::GetSpells()[i][j]->OnRender(aWindow);
		}
	}

	sf::Vector2f tempPosition = GetPosition();
}

void PlayerController::Movement()
{
	float tempX = 0;
	if (InputManager::GetKey(sf::Keyboard::Key::A))
	{
		tempX -= 1;
	}
	if (InputManager::GetKey(sf::Keyboard::Key::D))
	{
		tempX += 1;
	}

	if (myCollider->IsTouchingGround())
	{
		LeftGround = false;
		sf::Vector2f tempSurfaceVector = myCollider->GetGroundVector();
		myCollider->SetVelocity(tempSurfaceVector * tempX * mySpeed);
	}
	else
	{
		if (myCollider->IsTouchingWall())
		{
			if (myCollider->GetVelocity().y < 0)
			{
				myCollider->SetVelocity(sf::Vector2f(0, 0));
			}
			if (myCollider->GetCollidedContact()->contact->GetManifold()->localNormal.x * tempX > 0)
			{
				myCollider->SetVelocity(sf::Vector2f(tempX * mySpeed, myCollider->GetVelocity().y));
			}
		}
		else
		{
			myCollider->SetVelocity(sf::Vector2f(tempX * mySpeed, myCollider->GetVelocity().y));
		}
	}	
}

void PlayerController::GroundCheck()
{
	myGroundedTimer = myGroundedTimerValue;
	myGroundedTimer -= TimeTracker::GetDeltaTime();

}

void PlayerController::Jump()
{
	if (InputManager::GetKeyDown(sf::Keyboard::Space))
	{
		myJumpBufferTimer = myJumpBufferTimerValue;
	}

	if (myJumpBufferTimer > 0)
	{
		myJumpBufferTimer -= TimeTracker::GetDeltaTime();
		if (myGroundedTimer > 0)
		{
			myJumpBufferTimer = 0;
			myJumpTimer = myJumpTimerValue;
			myCollider->SetGravityScale(1);
		}
	}

	if (myJumpTimer > 0)
	{
		if (InputManager::GetKey(sf::Keyboard::Space))
		{
			myCollider->SetVelocity(sf::Vector2f(myCollider->GetVelocity().x, -myJumpHeight));
			myJumpTimer -= TimeTracker::GetDeltaTime();
		}
		if (InputManager::GetKeyUp(sf::Keyboard::Space))
		{
			myJumpTimer = 0;
		}
	}

	if (myJumpTimer <= 0 && !myCollider->IsTouchingGround())
	{
		myCollider->SetGravityScale(myFasterFallValue);
	}
}

