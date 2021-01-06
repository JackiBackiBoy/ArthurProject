#include "PlayerController.h"
#include "Managers/InputManager.h"
#include "TimeTracker.h"
#include "Nodes/Scene.h"

PlayerController::PlayerController(const sf::Vector2f& aPosition, const std::string& aName, float aSpeed, float aRunningSpeed, float aJumpHeight,
	float aGroundedTimerValue, float aJumpBufferTimerValue, float aJumpTimerValue, float aFasterFallValue)
	: Node(aPosition, aName), mySpeed(aSpeed), myRunningSpeed(aRunningSpeed), myJumpHeight(aJumpHeight), myGroundedTimerValue(aGroundedTimerValue),
	myJumpBufferTimerValue(aJumpBufferTimerValue), myJumpTimerValue(aJumpTimerValue), myFasterFallValue(aFasterFallValue)
{
}
void PlayerController::OnStart()
{
	myCollider = (PolygonCollider*)myParent;
	Node::OnStart();
}

void PlayerController::OnUpdate()
{
	Node::OnUpdate();
	GroundCheck();
	Movement();
	Jump();
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

	float tempSpeed = 0;

	if (InputManager::GetKey(sf::Keyboard::LShift))
	{
		tempSpeed = myRunningSpeed;
	}
	else
	{
		tempSpeed = mySpeed;
	}
	if (myCollider->IsTouchingGround() && !myCollider->IsTouchingWall())
	{
		LeftGround = false;
     	sf::Vector2f tempSurfaceVector = myCollider->GetGroundVector();
		myCollider->SetVelocity(tempSurfaceVector * tempX * tempSpeed);	
	}
	else 
	{
		if (myCollider->IsTouchingWall()) 
		{
			if (myCollider->GetCollidedContact()->contact->GetManifold()->localNormal.x * tempX > 0)
			{
				myCollider->SetVelocity(sf::Vector2f(tempX * tempSpeed, myCollider->GetVelocity().y));
			}
		}
		else 
		{
			myCollider->SetVelocity(sf::Vector2f(tempX * tempSpeed, myCollider->GetVelocity().y));
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

	if (myJumpTimer <= 0 && !myCollider->IsTouchingGround())
	{
		myCollider->AddVelocity(sf::Vector2f(0, myFasterFallValue * TimeTracker::GetDeltaTime()));
	}
}

