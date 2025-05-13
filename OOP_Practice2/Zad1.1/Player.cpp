#include "Player.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#pragma warning (disable:4996)

bool Player::Point::areAdjacent(const Point& other) const
{
	return abs(x - other.x) == 1 || abs(y - other.y) == 1;
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

void Player::stealData(Player&& other) noexcept
{
	
	setAttackPower(other.attackDamage);
	health = other.health;
	name = other.name;
	position = other.position;
	weapon = other.weapon;

	other.name = nullptr;
}

const char* Player::weaponToStr() const
{
	switch ((int)weapon)
	{
	case 0:
		return "SWORD";
	case 1:
		return "WAND";
	case 2:
		return "STAFF";
	case 3:
		return "AXE";
	default:
		return "UNKNOWN";
		break;
	}
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

void Player::handleAttack(unsigned recievedDamage)
{
	health -= recievedDamage;
}

void Player::attack(Player& attacked)
{
	attacked.health -= attackDamage;
}

void Player::print() const
{
	std::cout << "Player info: " << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Health: " << health << std::endl;
	std::cout << "Weapon: " << weaponToStr() << std::endl;
	std::cout << "Damage: " << attackDamage << std::endl;
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

Player::Player(unsigned health, const char* name, Weapons weapon, unsigned attackDamage)
	:health(health), weapon(weapon), attackDamage(attackDamage)
{
	if (!name)
		throw std::invalid_argument("name cannot be nullptr");

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
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

Player::~Player()
{
	free();
}
