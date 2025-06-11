#include "Conditional.h"
#include <stdexcept>
#include <iostream>

Conditional::Conditional(Formula* f1, Formula* f2, Formula* f3)
{
	copyFormulas(f1, f2, f3);
}

Conditional::Conditional(const Conditional& other)
	:Conditional(other.f1, other.f2, other.f3)
{}

Conditional::Conditional(Conditional && other)
{
	swap(other);
}

Conditional& Conditional::operator=(const Conditional& other)
{
	if (this != &other)
	{
		Conditional temp(other);
		swap(temp);
	}

	return *this;
}

Conditional& Conditional::operator=(Conditional&& other)
{
	if (this != &other)
	{
		free();
		swap(other);
	}
	return *this;
}

double Conditional::value() const
{
	if (f1->value())
		return f2->value();
	return f3->value();
}

void Conditional::print() const
{
	std::cout << "if ";
	f1->print();
	std::cout << " then ";
	f2->print();
	std::cout << " else ";
	f3->print();
}

Formula* Conditional::clone() const
{
	return new Conditional(*this);
}

void Conditional::copyFormulas(Formula* f1, Formula* f2, Formula* f3)
{
	if (!f1 || !f2 || !f3)
		throw std::invalid_argument("Conditional needs three formulas");

	this->f1 = f1->clone();

	try
	{
		this->f2 = f2->clone();
		this->f3 = f3->clone();
	}
	catch (...)
	{
		if (!f2)
			delete f1;
		else if (!f3)
		{
			delete f1;
			delete f2;
		}
		throw;
	}
}

void Conditional::swap(Conditional& other)
{
	std::swap(f1, other.f1);
	std::swap(f2, other.f2);
	std::swap(f3, other.f3);
}

void Conditional::free()
{
	delete f1;
	delete f2;
	delete f3;
	f1 = f2 = f3 = nullptr;
}
