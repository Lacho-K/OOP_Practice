#pragma once

namespace Constants
{
	static const unsigned short startingDigits[3] = { 9,7,8 };
	static const unsigned short staringDigitsLen = 3;
	static const unsigned short digitsLen = 13;
}

class ISBN
{
	unsigned short digits[Constants::digitsLen];
	unsigned short len = Constants::digitsLen;

	friend bool operator==(const ISBN& lhs, const ISBN& rhs);
	bool validateDigits(const unsigned short* digits);

public:
	ISBN();
	ISBN(const ISBN& other);
	ISBN(const unsigned short* digits, const unsigned short len);
};