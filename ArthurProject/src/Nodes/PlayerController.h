#pragma once
#include "Node.h"
#include "core\Ray.h"
#include "Nodes/PolygonCollider.h"
class PlayerController :
	public Node
{
public:
	PlayerController(const sf::Vector2f& aPosition, const std::string& aName, float aSpeed, float aRunningSpeed, float aJumpHeight,
		float aGroundedTimerValue, float aJumpBufferTimerValue, float aJumpTimerValue, float aFasterFallValue);
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
private:
	void Movement();
	void GroundCheck();
	void Jump();
	float mySpeed;
	float myRunningSpeed;
	float myJumpHeight; 
	float myFasterFallValue;

	float myJumpTimerValue;
	float myJumpTimer;

	float myGroundedTimerValue;
	float myGroundedTimer;

	float myJumpBufferTimerValue;
	float myJumpBufferTimer;

	bool LeftGround;

	PolygonCollider* myCollider;
};

