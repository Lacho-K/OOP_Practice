#include "Constant.h"
#include <iostream>

Constant::Constant():val(0)
{
}

Constant::Constant(double val):val(val)
{
}

double Constant::value() const
{
	return val;
}

void Constant::print() const
{
	std::cout << val;
}

Formula* Constant::clone() const
{
	return new Constant(*this);
}
