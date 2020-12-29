#include "BushSpawnBehaviour.h"
#include "Random.hpp"
#include <TimeTracker.h>
void BushSpawnBehaviour::OnStart()
{
	myCollider = (PolygonCollider*)myParent;
	myAnimator = myParent->GetChild<Animator>("Animator");
	myPlayerDetectionBox = myParent->GetChild<AABB>("PlayerDetectingCol");
}
void BushSpawnBehaviour::OnUpdate()
{
	Node::OnUpdate();
	if (myAwakeFlag)
	{
		AwakeUpdate();
	}
	else if (myWakingUpFlag)
	{
		myStateTimer -= TimeTracker::GetDeltaTime();
		if (myStateTimer <= 0)
		{
			if (myAnimator->GetCurrentAnimation() != "WakeUp")
			{
				myAnimator->SetAnimation("WakeUp");
				myAnimator->SetLoopFlag(false);
			}
			else
			{
				if (!myAnimator->GetPlayingFlag())
				{
					WakeUp();
				}
			}
		}
	}
	else
	{
		AsleepUpdate();
	}


}

void BushSpawnBehaviour::OnRender(sf::RenderWindow* aWindow)
{
	Node::OnRender(aWindow);
}

void BushSpawnBehaviour::AsleepUpdate()
{
	if (myIdleFidgetTimer <= 0 && !myPlayingIdleFidgetFlag)
	{
		int tempIdleAnim = Random::Int(0, 1);
		switch (tempIdleAnim)
		{
		case 0:
			myCurrentIdleAnim = "LookAround";
			break;
		case 1:
			myCurrentIdleAnim = "Shake";
			break;
		}
		myAnimator->SetAnimation(myCurrentIdleAnim);
		myAnimator->SetLoopFlag(false);
		myPlayingIdleFidgetFlag = true;
	}

	if (myPlayingIdleFidgetFlag)
	{
		if (!myAnimator->GetPlayingFlag())
		{
			myPlayingIdleFidgetFlag = false;
			myIdleFidgetTimer = Random::Int(100, 300) / 100.f;
			myAnimator->SetAnimation("AsleepIdle");
			myAnimator->SetLoopFlag(true);
		}
	}
	else
	{
		myIdleFidgetTimer -= TimeTracker::GetDeltaTime();
	}

	if (myPlayerDetectionBox->Intersects("PlayerCollisionBox"))
	{
		myPlayerNode = myPlayerDetectionBox->GetIntersecting("PlayerCollisionBox")[0]->GetParent();
		myStateTimer = myWakingUpTime;
		myWakingUpFlag = true;
		myParent->GetChild<SpriteRenderer>("NoticeSprite")->SetActive(true);
	}

}

void BushSpawnBehaviour::WakeUp()
{
	myParent->GetChild<SpriteRenderer>("NoticeSprite")->SetActive(false);

	myAwakeFlag = true;


	myAttackState = AttackState::ChargeUp;
	myAnimator->SetAnimation("ChargeUp");
	myAnimator->SetLoopFlag(false);
}

void BushSpawnBehaviour::AwakeUpdate()
{
	if (myAttackState == AttackState::ChargeUp)
	{
		if (!myAnimator->GetPlayingFlag())
		{
			myCounter++;
			if (myCounter < myChargeUpTimes)
			{
				myAnimator->SetAnimation("ChargeUp");
				myAnimator->SetLoopFlag(false);
			}
			else if (myCounter >= myChargeUpTimes)
			{
				myAttackState = AttackState::Dash;
				myCounter = 0;
				myAnimator->SetAnimation("Dash");
				myAnimator->SetLoopFlag(true);
				myStateTimer = myDashingTime;

				if (myPlayerNode->GetPosition().x > GetPosition().x)
				{
					myDashDirection = 1;
				}
				else
				{
					myDashDirection = -1;
				}
			}
		}
	}
	else if (myAttackState == AttackState::Dash)
	{
		myStateTimer -= TimeTracker::GetDeltaTime();
		if (myStateTimer <= 0)
		{
			myAttackState = AttackState::Exhausted;
			myAnimator->SetAnimation("Exhausted");
			myAnimator->SetLoopFlag(false);
			myCounter = 0;
			myCollider->SetVelocity(sf::Vector2f(0, 0));
		}
		else
		{
			if (myCollider->IsColliding())
			{
				sf::Vector2f tempSurfaceVector = myCollider->GetGroundVector();
				myCollider->SetVelocity(tempSurfaceVector * myDashDirection * myDashSpeed);
			}
			else
			{
				myCollider->SetVelocity(sf::Vector2f(myDashDirection * myDashSpeed, myCollider->GetVelocity().y));
			}
		}


	}
	else if (myAttackState == AttackState::Exhausted)
	{

		if (!myAnimator->GetPlayingFlag())
		{
			myCounter++;
			if (myCounter < myExhaustedTimes)
			{
				myAnimator->SetAnimation("Exhausted");
				myAnimator->SetLoopFlag(false);
			}
			else if (myCounter >= myExhaustedTimes)
			{
				myAttackState = AttackState::ChargeUp;
				myCounter = 0;
				myAnimator->SetAnimation("ChargeUp");
			}
		}

	}
}

void BushSpawnBehaviour::GoSleep()
{
}
