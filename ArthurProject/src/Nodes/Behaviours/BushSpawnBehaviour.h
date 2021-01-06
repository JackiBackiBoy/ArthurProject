#pragma once
#include "../Node.h"
#include "Nodes/Animator.h"
#include "Nodes/AABB.h"
#include "Nodes/PolygonCollider.h"
class BushSpawnBehaviour :
    public Node
{
public:
    void OnStart() override;
    void OnUpdate() override;
    void OnRender(sf::RenderWindow* aWindow) override;
private:
    enum AttackState
    {
        ChargeUp,
        Dash,
        Exhausted
    };

    void AsleepUpdate();
    void WakeUp();
    void AwakeUpdate();
    void GoSleep();
    std::string myCurrentIdleAnim;
    bool myAwakeFlag = false;
    float myIdleFidgetTimer = 0.f;
    bool myPlayingIdleFidgetFlag = false;

    float myStateTimer;

    float myWakingUpTime = 0.2f;
    bool myWakingUpFlag;


    int myCounter;
    int myChargeUpTimes = 2;
    float myDashingTime = 2.f;
    int myExhaustedTimes = 4;

    float myDashDirection;
    float myDashSpeed = 35;

    PolygonCollider* myCollider;
    Animator* myAnimator;
    AABB* myPlayerDetectionBox;
    Node* myPlayerNode;
    AABB* myHitbox;
    AttackState myAttackState = AttackState::ChargeUp;
};

