#include "Mag.h"
#include <stdexcept>
#pragma warning (disable:4996)

void Mag::free()
{
	delete[] skill;
	skill = nullptr;
}

Mag::Mag(const char* skill, double coeficient, unsigned health, const char* name, Weapons weapon, unsigned attackDamage)
	:Player(health, name, weapon, attackDamage)
{
	setSkill(skill);
	setCoeficient(coeficient);
}

Mag::Mag(const Mag& other): Player(other)
{
	setSkill(other.skill);
	setCoeficient(other.coeficient);
}

Mag::Mag(Mag&& other) : Player(std::move(other))
{
	skill = other.skill;
	coeficient = other.coeficient;

	other.skill = nullptr;
}

void Mag::setCoeficient(double coeficient)
{
	if (coeficient <= 0 || coeficient >= 1)
		throw std::invalid_argument("mag coeficient must be in the open interval (0,1)");

	this->coeficient = coeficient;
}

void Mag::setSkill(const char* skill)
{
	if (!skill)
		throw std::invalid_argument("skill cannot by nullptr");

	this->skill = new char[strlen(skill) + 1];
	strcpy(this->skill, skill);
}

void Mag::attack(Player& attacked)
{
	unsigned tempAttack = getAttackPower();
	setAttackPower(getAttackPower() * coeficient);
	Player::attack(attacked);
	setAttackPower(tempAttack);
	Player::attack(attacked);
}

Player* Mag::clone() const
{
	return new Mag(*this);
}

Mag::~Mag()
{
	free();
}
