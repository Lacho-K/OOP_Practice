#pragma once
#include "Drink.h"

class AlcoholDrink : public Drink
{
public:
	AlcoholDrink() = default;
	AlcoholDrink(const char* name, int ml, int alcPercent);

	const int getAlcPercent() const;
	void setAlcPercent(int percent);

private:
	int alcPercent = 0;
};