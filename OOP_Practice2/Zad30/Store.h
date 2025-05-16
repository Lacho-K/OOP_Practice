#pragma once
#include "Cashier.h"

namespace StoreConstants
{
	static constexpr unsigned short MAX_CASHIERS = 10;
}

class Store
{

public:
	Store() = default;
	Store(const Cashier* cashiers, unsigned short count);


	Cashier& operator[](const char* targetName);
	const Cashier& operator[](const char* targetName) const;
	std::ostream& operator<<(std::ostream& os) const;
	friend std::istream& operator>>(std::istream& is, Store& s);
	friend bool operator<(const Store& lhs, const Store& rhs);
	friend bool operator>(const Store& lhs, const Store& rhs);

	double getTotalTurnover() const;

private:
	Cashier cashiers[StoreConstants::MAX_CASHIERS];
	unsigned short occupied = 0;
};