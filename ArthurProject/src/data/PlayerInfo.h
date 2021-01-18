#pragma once
#include <vector>
#include "Spells/Spell.h"
#include "Nodes/Health.h"
#include "Spells/PastTime.h"

class PlayerInfo
{
public:
	static Health* GetHealth();
	static void SetHealth(Health* aHealth);
	static float GetMana();
	static void SetMana(float aValue);
	static std::vector<std::vector<std::shared_ptr<Spell>>> GetSpells();
private:
	static Health* myHealth;
	static float myMana;
	static std::vector<std::vector<std::shared_ptr<Spell>>> mySpells;
};
