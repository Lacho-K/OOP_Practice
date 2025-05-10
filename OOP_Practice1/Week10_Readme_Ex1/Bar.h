#pragma once
#include "AlchoholDrink.h"
class Bar
{
public:
	//Bar() = default;
	//Bar(const Bar& other);
	//Bar(Bar&& other) noexcept;

	//Bar& operator=(const Bar& other);
	//Bar& operator=(Bar&& other) noexcept;

	void addDrink(const char* name, unsigned ml, unsigned quantity = 1);
	void addAlcoholDrink(const char* name, unsigned ml, unsigned alcPercent, unsigned quantity = 1);

	const Drink& getDrink();
	const AlcoholDrink& getAlcoholDrink();

	unsigned getAlocholDrinksSold() const;
	unsigned getDrinksSold() const;
	unsigned getDrinksMlSold() const;
private:
	AlcoholDrink drinks[100];

	size_t drinksCount = 0;
	size_t drinksCapacity = 100;

	unsigned soldDrinks = 0;
	unsigned soldAlcoholDrinks = 0;
	unsigned mlSold = 0;

	/*void copyFrom(const Bar& other);
	void moveFrom(Bar&& other);
	void free();*/
};