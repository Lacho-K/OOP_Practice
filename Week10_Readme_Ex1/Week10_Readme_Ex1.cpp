#include <iostream>
#include "Bar.h"


int main()
{
	Bar b;

	b.addDrink("Coke", 330, 2); //2x Coca cola 330 ml

	b.addDrink("Fanta", 500);   //1x Fanta 500 ml

	b.addAlcoholDrink("Zagorka", 500, 5); //1x Zagorka, 5% alc,  500 ml

	b.getAlcoholDrink(); // Zagorka 

	b.getDrink(); // Coke
	b.getDrink(); // Coke
	b.getDrink(); // Fanta

	b.getAlocholDrinksSold(); // 1
	b.getDrinksMlSold(); // 830

}