#include "Player.h"
#include <cmath>
#include <stdexcept>

bool Player::Point::areAdjacent(const Point& other) const
{
	return abs(x - other.x) == 1 && abs(y - other.y) == 1;
}

void Player::copyDynamic(const Player& other)
{
	if (!other.name)
		throw std::runtime_error("cannot copy empty name");

	name = new char[strlen(other.name) + 1];

	strcpy(name, other.name);
}

void Player::copyFrom(const Player& other)
{
	copyDynamic(other);
	setAttackPower(other.attackDamage);
	health = other.health;
	weapon = other.weapon;
	position = other.position;
}

void Player::stealData(Player&& other)
{
	if (other.attackDamage < 0)
		throw std::invalid_argument("attack cannot be < 0");

	health = other.health;
	name = other.name;
	position = other.position;
	weapon = other.weapon;
	attackDamage = other.attackDamage;

	other.name = nullptr;
}

void Player::swapData(Player& other) noexcept
{
	std::swap(health, other.health);
	std::swap(name, other.name);
	std::swap(position, other.position);
	std::swap(weapon, other.weapon);
	std::swap(attackDamage, other.attackDamage);
}

void Player::free()
{
	delete[] name;
	name = nullptr;
}

void Player::move(int offsetX, int offsetY)
{
	position.x += offsetX;
	position.y += offsetY;
}

void Player::handleAttack(const Player& attacker)
{
	health -= attacker.getAttackPower();
}

void Player::attack(Player& attacked)
{
	attacked.health -= attackDamage;
}

unsigned Player::getAttackPower() const
{
	return attackDamage;
}

void Player::setAttackPower(unsigned attackPower)
{
	if (attackPower < 0)
		throw std::invalid_argument("attack power cannot be < 0");

	this->attackDamage = attackPower;
}

Player::Player(const Player& other)
{
	try
	{
		copyFrom(other);
	}
	catch (...)
	{
		free();
		throw;
	}
}

Player::Player(Player&& other)
{
	stealData(std::move(other));
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Player& Player::operator=(Player&& other)
{
	if (this != &other)
	{
		free();
		stealData(std::move(other));
	}

	return *this;
}

Player::~Player()
{
	free();
}
