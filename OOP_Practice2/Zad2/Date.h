#pragma once
#include <ostream>

class Date
{
public:

	Date(unsigned short day, unsigned short month, unsigned short year);
	Date(const char* date);
	void print(std::ostream& os);
	unsigned short getDay() const;
	unsigned short getMonth() const;
	unsigned short getYear() const;

private:

	unsigned short day : 5;
	unsigned short month : 4;
	unsigned short year : 6;

	static const unsigned short dateSize;
	
	void validateDate(const char* date);
};