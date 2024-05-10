#include "Bar.h"
#include <iostream>

Bar::Bar(const Bar& other)
{
	copyFrom(other);
}

Bar::Bar(Bar&& other) noexcept
{
	moveFrom(std::move(other));
}

Bar& Bar::operator=(const Bar& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Bar& Bar::operator=(Bar&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

void Bar::addDrink(const char* name, unsigned ml, unsigned quantity)
{
	if (drinksCount + quantity > drinksCapacity)
		return;

	for (size_t i = 0; i < quantity; i++)
	{
		AlcoholDrink drinkToAdd(name, ml, 0);
		drinks[drinksCount++] = drinkToAdd;
	}
}

void Bar::addAlcoholDrink(const char* name, unsigned ml, unsigned alcPercent, unsigned quantity)
{
	if (drinksCount + quantity > drinksCapacity)
		return;

	for (size_t i = 0; i < quantity; i++)
	{
		AlcoholDrink drinkToAdd(name, ml, alcPercent);
		drinks[drinksCount++] = drinkToAdd;
	}

}


const Drink& Bar::getDrink()
{
	Drink maxDrink;
	unsigned maxMl = 0;

	for (size_t i = 0; i < drinksCount; i++)
	{
		if (drinks[i].getAlcPercent() == 0 && drinks[i].getMl() > maxMl)
		{
			maxDrink = drinks[i];
			maxMl = drinks[i].getMl();
		}
	}

	soldDrinks++;
	mlSold += maxDrink.getMl();

	return maxDrink;
}

const AlcoholDrink& Bar::getAlcoholDrink()
{
	AlcoholDrink maxDrink;
	unsigned maxMl = 0;

	for (size_t i = 0; i < drinksCount; i++)
	{
		if (drinks[i].getAlcPercent() > 0 && drinks[i].getMl() > maxMl)
		{
			maxDrink = drinks[i];
			maxMl = drinks[i].getMl();
		}
	}

	soldAlcoholDrinks++;
	mlSold += maxDrink.getMl();

	return maxDrink;
}

unsigned Bar::getAlocholDrinksSold()
{
	return soldAlcoholDrinks;
}

unsigned Bar::getDrinksSold()
{
	return soldDrinks;
}

unsigned Bar::getDrinksMlSold()
{
	return mlSold;
}

Bar::~Bar()
{
	free();
}

void Bar::copyFrom(const Bar& other)
{
	drinks = new AlcoholDrink[drinksCapacity];

	for (size_t i = 0; i < other.drinksCount; i++)
	{
		drinks[i] = other.drinks[i];
	}

	drinksCount = other.drinksCount;
	soldDrinks = other.soldDrinks;
	soldAlcoholDrinks = other.soldAlcoholDrinks;
}

void Bar::moveFrom(Bar&& other)
{
	drinks = other.drinks;
	drinksCount = other.drinksCount;
	soldDrinks = other.soldDrinks;
	soldAlcoholDrinks = other.soldAlcoholDrinks;

	other.drinks = nullptr;
	other.drinksCount = 0;
	other.soldDrinks = 0;
	other.soldAlcoholDrinks = 0;
	other.drinksCapacity = 0;
}

void Bar::free()
{
	delete[] drinks;

	drinks = nullptr;
	drinksCount = 0;
	soldDrinks = 0;
	soldAlcoholDrinks = 0;
	drinksCapacity = 0;
}
