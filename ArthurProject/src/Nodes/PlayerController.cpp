#include "PlayerController.h"
#include "Managers/InputManager.h"
#include "TimeTracker.h"

PlayerController::PlayerController(const sf::Vector2f& aPosition, const std::string& aName, float aMaxSpeed, float anAcceleration,
	float aDeceleration, float aJumpHeight, float aGroundedTimerValue, float aJumpBufferTimerValue, float aJumpTimerValue, float aFasterFallValue)
	: Node(aPosition, aName), myMaxSpeed(aMaxSpeed), myJumpHeight(aJumpHeight), myAcceleration(anAcceleration), myDeceleration(aDeceleration),
	myGroundedTimerValue(aGroundedTimerValue), myJumpBufferTimerValue(aJumpBufferTimerValue), myJumpTimerValue(aJumpTimerValue), myFasterFallValue(aFasterFallValue)
{
}

void PlayerController::OnStart()
{
	Node::OnStart();
	myCollider = ((BoxCollider*)myParent);
}

void PlayerController::OnUpdate()
{
	Node::OnUpdate();
	Movement();
	GroundCheck();
	Jump();
}

void PlayerController::OnRender(sf::RenderWindow* aWindow)
{
	Node::OnRender(aWindow);
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

	if (std::abs(myCollider->GetVelocity().x) < myMaxSpeed || (tempX < 0 && myCollider->GetVelocity().x >0) || (tempX > 0 && myCollider->GetVelocity().x < 0))
	{
		myCollider->AddVelocity(sf::Vector2f(tempX * myAcceleration * TimeTracker::GetDeltaTime(), 0));
	}


	//If no movement input
	if (tempX == 0)
	{
		if (std::abs(myCollider->GetVelocity().x) > 0.01f)
		{
			if (myCollider->GetVelocity().x > 0)
			{
				myCollider->AddVelocity(sf::Vector2f(-myDeceleration * TimeTracker::GetDeltaTime(), 0));
			}
			else if (myCollider->GetVelocity().x < 0)
			{
				myCollider->AddVelocity(sf::Vector2f(myDeceleration * TimeTracker::GetDeltaTime(), 0));
			}
		}
		else
		{
			myCollider->SetVelocity(sf::Vector2f(0, myCollider->GetVelocity().y));
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

	if (myJumpTimer <= 0)
	{
		myCollider->AddVelocity(sf::Vector2f(0, myFasterFallValue * TimeTracker::GetDeltaTime()));
	}
}

