#include "Warrior.h"
#include <stdexcept>

Warrior::Warrior(unsigned armour, unsigned health, const char* name, Weapons weapon, unsigned attackDamage)
	:Player(health, name, weapon, attackDamage)
{
	setArmour(armour);
}

void Warrior::handleAttack(unsigned recievedDamage)
{
	if (armour - recievedDamage <= 0)
	{
		armour = 0;
		Player::handleAttack(recievedDamage - armour);
	}
	else
	{
		armour -= recievedDamage;
	}
}

void Warrior::setArmour(unsigned armour)
{
	if (armour < 0)
		throw std::invalid_argument("armour cannot be < 0");

	this->armour = armour;
}

unsigned Warrior::getArmour() const
{
	return armour;
}
