#include "IntRange.h"
#include <stdexcept>

IntRange::IntRange(int min, int max):min(min), max(max)
{
	if (min > max)
		throw std::invalid_argument("invalid range");
}

bool IntRange::member(int x) const
{
	return x >= min && x <= max;
}

int IntRange::get(int i) const
{
	if (i < 0 || i >= size())
		throw std::out_of_range("Index out of range");

	return min + i;
}

size_t IntRange::size() const
{
	return max - min + 1;
}

bool IntRange::operator<(const IntSet& other) const
{
	size_t mySize = size();
	size_t otherSize = other.size();

	for (size_t i = 0; i < mySize; i++)
	{
		int x = get(i);
		if (!other.member(x))
			return false;
	}

	for (size_t i = 0; i < other.size(); i++)
	{
		int x = other.get(i);

		if (!member(x))
			return true;
	}
	
	return false;
}

bool IntRange::operator*(const IntSet& other) const
{
	for (size_t i = 0; i < size(); i++)
	{
		if (other.member(get(i)))
			return true;
	}
	return false;
}

