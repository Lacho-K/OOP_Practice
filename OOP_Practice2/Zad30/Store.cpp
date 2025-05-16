#include "Store.h"

Store::Store(const Cashier* cashiers, unsigned short count)
{
	if (count > StoreConstants::MAX_CASHIERS)
		throw std::invalid_argument("cashiers count exceded");

	for (unsigned short i = 0; i < count; i++)
	{
		this->cashiers[i] = cashiers[i];
	}
	occupied = count;
}

Cashier& Store::operator[](const char* targetName)
{
	for (unsigned short i = 0; i < StoreConstants::MAX_CASHIERS; i++)
	{
		if (strcmp(cashiers[i].getName(), targetName) == 0)
			return cashiers[i];
	}

	return *(new Cashier());
}

const Cashier& Store::operator[](const char* targetName) const
{
	for (unsigned short i = 0; i < StoreConstants::MAX_CASHIERS; i++)
	{
		if (strcmp(cashiers[i].getName(), targetName) == 0)
			return cashiers[i];
	}

	return Cashier();
}

std::ostream& Store::operator<<(std::ostream& os) const
{
	for (unsigned short i = 0; i < occupied; i++)
	{
		cashiers[i] << os;
	}
	return os;
}

double Store::getTotalTurnover() const
{
	double sum = 0.0;
	for (unsigned short i = 0; i < occupied; i++)
	{
		sum += cashiers[i].getTurnover();
	}
	return sum;
}

std::istream& operator>>(std::istream& is, Store& s)
{
	for (unsigned short i = 0; i < s.occupied; i++)
	{
		is >> s.cashiers[i];
	}

	return is;
}

bool operator<(const Store& lhs, const Store& rhs)
{
	return (lhs.getTotalTurnover() / lhs.occupied) < (rhs.getTotalTurnover() / rhs.occupied);
}

bool operator>(const Store& lhs, const Store& rhs)
{
	return !(lhs < rhs);
}
