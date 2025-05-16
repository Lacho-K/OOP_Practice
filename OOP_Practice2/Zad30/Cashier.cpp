#include "Cashier.h"
#pragma warning(disable:4996)
#include <iostream>

Cashier::Cashier(const char* name, double turnover)
{
	setName(name);
	setTurnover(turnover);
}

const char* Cashier::getName() const
{
	return name;
}

void Cashier::setName(const char* newName)
{
	if (!newName || strlen(newName) >= CashierConstants::NAME_SIZE)
		throw std::invalid_argument("new name too long");

	strcpy(name, newName);
}

double Cashier::getTurnover() const
{
	return turnover;
}

void Cashier::setTurnover(double turnover)
{
	if (turnover < 0.0)
		throw std::invalid_argument("turnover cannot be < 0");
	this->turnover = turnover;
}

std::ostream& Cashier::operator<<(std::ostream& os) const
{
	os << name << " " << turnover;
	return os;
}

std::istream& operator>>(std::istream& is, Cashier& c)
{
	is.getline(c.name, CashierConstants::NAME_SIZE, ' ');
	is >> c.turnover;
	return is;
}
