#include "Read.h"
#include <iostream>

double Read::value() const
{
	return data;
}

void Read::print() const
{
	std::cout << data;
}

Formula* Read::clone() const
{
	return new Read(*this);
}

Read::Read()
{
	std::cin >> data;
}
