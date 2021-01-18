#include "PlayerInfo.h"
std::vector<std::vector<std::shared_ptr<Spell>>> PlayerInfo::mySpells =
{
	//Denial
	{std::make_shared<PastTime>(PastTime("","",0,0,true,nullptr))},
	{},
	{},
	{}
};
float PlayerInfo::myMana = 100;
Health* PlayerInfo::myHealth = nullptr;

Health* PlayerInfo::GetHealth()
{
    return myHealth;
}

void PlayerInfo::SetHealth(Health* aHealth)
{
    myHealth = aHealth;
}

float PlayerInfo::GetMana()
{
    return myMana;
}

void PlayerInfo::SetMana(float aValue)
{
    myMana = aValue;
}

std::vector<std::vector<std::shared_ptr<Spell>>> PlayerInfo::GetSpells()
{
    return mySpells;
}
