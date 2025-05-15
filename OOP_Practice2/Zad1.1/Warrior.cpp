#include "Warrior.h"
#include <stdexcept>
#include <iostream>

Warrior::Warrior(const Warrior& other) : Player(other)
{
	setArmour(other.armour);
}

Warrior::Warrior(unsigned armour, unsigned health, const char* name, Weapons weapon, unsigned attackDamage)
	:Player(health, name, weapon, attackDamage)
{
	setArmour(armour);
}

void Warrior::handleAttack(const Player& attacker)
{
	unsigned attack = attacker.getAttackPower();

	if (attack >= armour)
	{
		health -= (attack - armour);
		armour = 0;

		if (health < 0)
			health = 0;
	}
	else
	{
		armour -= attack;
	}
}

void Warrior::print() const
{
	Player::print();
	std::cout << "Warrior info: " << std::endl;
	std::cout << "Armour: " << armour << std::endl;
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

Player* Warrior::clone() const
{
	return new Warrior(*this);
}
