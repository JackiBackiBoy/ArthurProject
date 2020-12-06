#pragma once
#include "Node.h"
#include "Nodes/BoxCollider.h"
class PlayerController :
	public Node
{
public:
	PlayerController(const sf::Vector2f& aPosition, const std::string& aName, float aMaxSpeed, float anAcceleration,
		float aDeceleration, float aJumpHeight, float aGroundedTimerValue, float aJumpBufferTimerValue,
		float aJumpTimerValue, float aFasterFallValue);
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
private:
	void Movement();
	void GroundCheck();
	void Jump();
	float myMaxSpeed;
	float myAcceleration;
	float myDeceleration;
	float myJumpHeight; 
	float myFasterFallValue;

	float myJumpTimerValue;
	float myJumpTimer;

	float myGroundedTimerValue;
	float myGroundedTimer;

	float myJumpBufferTimerValue;
	float myJumpBufferTimer;


	BoxCollider* myCollider;
};

