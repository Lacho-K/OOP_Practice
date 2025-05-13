#pragma once
#include "Player.h"
class Mag: public Player
{
	char* skill = nullptr;
	double coeficient = 0;
	void free();

public:

	Mag() = default;
	Mag(const char* skill, double coeficient, unsigned health, const char* name, Weapons weapon, unsigned attackDamage);
	Mag(const Mag& other);
	Mag(Mag&& other);

	void setCoeficient(double coeficient);
	void setSkill(const char* skill);

	virtual void attack(Player& attacked) override;
	virtual Player* clone() const override;

	Mag& operator=(const Mag& other) = delete;
	Mag& operator=(Mag&&) = delete;

	virtual ~Mag();
};