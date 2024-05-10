#include "AlchoholDrink.h"
#include <exception>

const int AlcoholDrink::getAlcPercent() const
{
	return alcPercent;
}

void AlcoholDrink::setAlcPercent(int percent)
{
	if (alcPercent < 0)
		throw std::exception("Invalid alc percent");

	alcPercent = percent;
}

AlcoholDrink::AlcoholDrink(const char* name, int ml, int percent):Drink(name, ml)
{
	setAlcPercent(percent);
}