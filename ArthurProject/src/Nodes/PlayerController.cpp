#include "PlayerController.h"
#include "Managers/InputManager.h"
#include "TimeTracker.h"
#include "Nodes/Scene.h"
#include "Nodes\Health.h"
#include "Nodes\ResourceBar.h"

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
}

void PlayerController::OnUpdate()
{
	Node::OnUpdate();
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

void PlayerController::OnRender(sf::RenderWindow* aWindow)
{
	Node::OnRender(aWindow);
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

	if (myCollider->IsColliding())
	{
		sf::Vector2f tempSurfaceVector = myCollider->GetGroundVector();
		myCollider->SetVelocity(tempSurfaceVector * tempX * mySpeed);	
	}
	else 
	{
		myCollider->SetVelocity(sf::Vector2f(tempX * mySpeed, myCollider->GetVelocity().y));
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

	if (myJumpTimer <= 0 && !myCollider->IsColliding())
	{
		myCollider->SetGravityScale(myFasterFallValue);
	}
}

