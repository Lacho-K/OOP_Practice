#pragma once
#include "Mag.h"

class Necromancer : public Mag
{
	Player** killedPlayers = nullptr;
	size_t count = 0;
	size_t cap = 8;

	void copyFrom(const Necromancer& other);
	void free();
	void resize();
	void addPlayer(Player* player);

public:
	Necromancer() = default;
	Necromancer(const Necromancer& other);
	Necromancer(Necromancer&& other);
	Necromancer(const char* skill, double coef, unsigned health, const char* name, Weapons weapon, unsigned damage);

	virtual void attack(Player& attacked) override;
	virtual Player* clone() const override;

	Necromancer& operator=(const Necromancer& other) = delete;
	Necromancer& operator=(Necromancer&& other) = delete;


	virtual ~Necromancer();
};