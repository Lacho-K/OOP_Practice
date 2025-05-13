#pragma once
#include "Player.h"
class Warrior: public Player
{
	unsigned armour = 0;

public:

	Warrior(unsigned armour, unsigned health, const char* name, Weapons weapon, unsigned attackDamage);
	virtual void handleAttack(unsigned recievedDamage) override;
	void setArmour(unsigned armour);
	unsigned getArmour() const;
};