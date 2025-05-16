#pragma once
#include <ostream>

namespace CashierConstants
{
	static constexpr unsigned short NAME_SIZE = 30;
}

class Cashier
{
public:

	Cashier() = default;
	Cashier(const char* name, double turnover);


	const char* getName() const;
	void setName(const char* newName);

	double getTurnover() const;
	void setTurnover(double turnover);

	std::ostream& operator<<(std::ostream& os) const;
	friend std::istream& operator>>(std::istream& is, Cashier& c);

private:
	char name[CashierConstants::NAME_SIZE] = "No name";
	double turnover = 0;
};