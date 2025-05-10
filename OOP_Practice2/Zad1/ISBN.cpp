#include "ISBN.h"

bool ISBN::validateDigits(const unsigned short* digits)
{
	for (int i = 0; i < Constants::staringDigitsLen; i++)
	{
		if (digits[i] != Constants::startingDigits[i])
		{
			return false;
		}
	}

	return true;
}

ISBN::ISBN()
{
	for (int i = 0; i < Constants::staringDigitsLen; i++)
	{
		digits[i] = Constants::startingDigits[i];
	}
}

ISBN::ISBN(const ISBN& other): ISBN(other.digits, other.len)
{}

ISBN::ISBN(const unsigned short* digits, const unsigned short len)
{
	if (!digits || !validateDigits(digits) || len != Constants::digitsLen)
		throw "Digits invalid!";

	for (int i = 0; i < Constants::digitsLen; i++)
	{
		this->digits[i] = digits[i];
	}
}

bool operator==(const ISBN& lhs, const ISBN& rhs)
{
	if (lhs.len != rhs.len)
		return false;

	for (int i = 0; i < lhs.len; i++)
	{
		if (lhs.digits[i] != rhs.digits[i])
			return false;
	}

	return true;
}
