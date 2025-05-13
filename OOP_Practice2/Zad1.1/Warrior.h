#pragma once
#include "Player.h"
class Warrior: public Player
{
	unsigned armour = 0;

public:

	Warrior() = default;
	Warrior(const Warrior& other);
	Warrior(unsigned armour, unsigned health, const char* name, Weapons weapon, unsigned attackDamage);
	virtual void handleAttack(const Player& attacker) override;
	virtual void print() const override;
	void setArmour(unsigned armour);
	unsigned getArmour() const;
	virtual Player* clone() const override;

	Warrior& operator=(const Warrior& other) = delete;
	Warrior& operator=(Warrior&&) = delete;
};