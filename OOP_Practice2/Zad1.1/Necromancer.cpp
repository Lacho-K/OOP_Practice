#include "Necromancer.h"
#include <stdexcept>

void Necromancer::copyFrom(const Necromancer& other)
{
	if (other.count > other.cap)
		throw std::invalid_argument("invalid necromancer");

	if (other.killedPlayers)
	{
		killedPlayers = new Player * [other.cap];
		int clonedCount = 0;
		try
		{
			for (size_t i = 0; i < other.count; i++)
			{
				killedPlayers[i] = other.killedPlayers[i]->clone();
				clonedCount++;
			}
		}
		catch(...)
		{
			for (int i = 0; i < clonedCount; i++)
			{
				delete killedPlayers[i];
			}
			delete[] killedPlayers;
		}
	}

	count = other.count;
	cap = other.cap;

}

void Necromancer::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete killedPlayers[i];
	}
	delete[] killedPlayers;
}

void Necromancer::resize()
{
	Player** newContainer = new Player * [cap * 2];
	for (size_t i = 0; i < count; i++)
	{
		newContainer[i] = killedPlayers[i];
	}
	delete[] killedPlayers;
	killedPlayers = newContainer;
	cap *= 2;
}

void Necromancer::addPlayer(Player* player)
{
	if (count == cap)
		resize();

	killedPlayers[count++] = player;
}

Necromancer::Necromancer(const Necromancer& other) : Mag(other)
{
	copyFrom(other);
} 

Necromancer::Necromancer(const char* skill, double coef, unsigned health, const char* name, Weapons weapon, unsigned damage)
	: Mag(skill, coef, health, name, weapon, damage)
{}


Necromancer::Necromancer(Necromancer&& other) : Mag(std::move(other))
{
	if (other.count > other.cap)
		throw std::invalid_argument("invalid necromancer");

	killedPlayers = other.killedPlayers;
	count = other.count;
	cap = other.cap;

	other.killedPlayers = nullptr;
	other.count = other.cap = 0;
}

void Necromancer::attack(Player& attacked)
{
	if (killedPlayers)
	{
		int randIndex = rand() % count;
		attacked.handleAttack(*killedPlayers[randIndex]);
	}
	Player::attack(attacked);

	if (!attacked.isAlive())
		addPlayer(&attacked);
}

Player* Necromancer::clone() const
{
	return new Necromancer(*this);
}
