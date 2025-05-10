#pragma warning (disable:4996)
#include "Date.h"
#include "Utils.h"

const unsigned short Date::dateSize = 10;

Date::Date(unsigned short day, unsigned short month, unsigned short year)
{
	this->day = day - 1;
	this->month = month - 1;
	this->year = year - 1970;
}

Date::Date(const char* s)
{
	validateDate(s);

	int d = (s[0] - '0') * 10 + (s[1] - '0');
	int m = (s[3] - '0') * 10 + (s[4] - '0');
	int y = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');

	day = d - 1;
	month = m - 1;
	year = y - 1970;
}

void Date::print(std::ostream& os)
{
	os << getDay() << "/" << getMonth() << "/" << getYear();
}

unsigned short Date::getDay() const
{
	return day + 1;
}

unsigned short Date::getMonth() const
{
	return month + 1;
}

unsigned short Date::getYear() const
{
	return year + 1970;
}

void Date::validateDate(const char* date)
{
	if (!date || date[0] == '\0')
		throw std::runtime_error("date empty or nullptr");

	if (strlen(date) < dateSize)
		throw std::invalid_argument("date invalid format");

	for (int i = 0; i < dateSize; i++)
	{
		if (!isNumber(date[i]) && i != 2
			|| !isNumber(date[i]) && i != 5)
		{
			throw std::invalid_argument("date invalid format");
		}
	}
}
