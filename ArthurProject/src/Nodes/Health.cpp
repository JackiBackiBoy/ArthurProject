#include "Health.h"

Health::Health(std::string aName, float aMaxHealth) : Node(sf::Vector2f(0, 0), aName)
,myMaxHealth(aMaxHealth), myCurrentHealth(aMaxHealth)
{
}

void Health::OnUpdate()
{
	Node::OnUpdate();
}

void Health::OnRender(sf::RenderWindow* aWindow)
{
	Node::OnRender(aWindow);
}

void Health::Damage(float aValue)
{
	if (myInvulnurableFlag)
		return;

	myCurrentHealth -= aValue;
	OnTakeDamage.Invoke();

	if (myCurrentHealth <= 0)
	{
		myDeadFlag = true;
		myCurrentHealth = 0;
	}
}

void Health::Heal(float aValue)
{
	myCurrentHealth += aValue;
	if (myCurrentHealth > myMaxHealth)
	{
		myCurrentHealth = myMaxHealth;
	}
}

bool Health::GetDeadFlag()
{
	return myDeadFlag;
}

void Health::SetInvulnurableFlag(bool aValue)
{
	myInvulnurableFlag = aValue;
}

float Health::GetCurrentHealth()
{
	return myCurrentHealth;
}

float Health::GetMaxHealth()
{
	return myMaxHealth;
}

float Health::GetHealthPercent()
{
	return myCurrentHealth/myMaxHealth;
}
