#pragma once
#include "Node.h"
#include "core/Event.h"
class Health :
    public Node
{
public:
    Health(std::string aName, float aMaxHealth);
    void OnUpdate() override;
    void OnRender(sf::RenderWindow* aWindow) override;
    void Damage(float aValue);
    void Heal(float aValue);
    bool GetDeadFlag();
    void SetInvulnurableFlag(bool aValue);
    float GetCurrentHealth();
    float GetMaxHealth();
    float GetHealthPercent();
    Event OnTakeDamage;
private:
    float myMaxHealth;
    float myCurrentHealth;
    bool myDeadFlag = false;
    bool myInvulnurableFlag = false;
};

