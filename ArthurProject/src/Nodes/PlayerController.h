#pragma once
#include "Node.h"
#include "core\Ray.h"
#include "Nodes/PolygonCollider.h"
#include "Nodes/Health.h"
class PlayerController :
	public Node
{
public:
	PlayerController(const sf::Vector2f& aPosition, const std::string& aName, float aSpeed, float aJumpHeight,
		float aGroundedTimerValue, float aJumpBufferTimerValue, float aJumpTimerValue, float aFasterFallValue);
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
private:
	void Movement();
	void GroundCheck();
	void Jump();
	void OnTakeDamage();
	void MagicUpdate();

	int myCurrentSpellType = 0;


	float mySpeed;
	float myJumpHeight; 
	float myFasterFallValue;

	float myJumpTimerValue;
	float myJumpTimer;

	float myGroundedTimerValue;
	float myGroundedTimer;

	float myJumpBufferTimerValue;
	float myJumpBufferTimer;

	bool LeftGround;

	float myInvulnurableTimerValue = 1.f;
	float myInvulnurableTimer;

	PolygonCollider* myCollider;
	Health* myHealth;
};

