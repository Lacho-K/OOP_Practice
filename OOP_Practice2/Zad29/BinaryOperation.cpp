#include "BinaryOperation.h"
#include <stdexcept>
#include <iostream>

BinaryOperation::BinaryOperation(const char ch, const Formula* f1, const Formula* f2)
{
	copyDynamic(ch, f1, f2);
}

BinaryOperation::BinaryOperation(const BinaryOperation& other) 
	:BinaryOperation(other.ch, other.f1, other.f2)
{
}

BinaryOperation::BinaryOperation(BinaryOperation&& other)
{
	swap(other);
}

BinaryOperation& BinaryOperation::operator=(const BinaryOperation& other)
{
	if (this != &other)
	{
		BinaryOperation temp(other);
		swap(temp);
	}

	return *this;
}

BinaryOperation& BinaryOperation::operator=(BinaryOperation&& other)
{
	if (this != &other)
	{
		free();
		swap(other);
	}

	return *this;
}

BinaryOperation::~BinaryOperation()
{
	free();
}

Formula* BinaryOperation::clone() const
{
	return new BinaryOperation(*this);
}

void BinaryOperation::print() const
{
	std::cout << "( ";
	f1->print();
	std::cout << " ";
	std::cout << ch << " ";
	f2->print();
	std::cout << " )";
}

double BinaryOperation::value() const
{
	switch (ch)
	{
	case '+':
		return f1->value() + f2->value();
	case '-':
		return f1->value() - f2->value();
	case '*':
		return f1->value() * f2->value();
	case '/':
		return f1->value() / f2->value();
	case '<':
		return f1->value() < f2->value();
	case '=':
		return f1->value() == f2->value();
	default:
		break;
	}
}

void BinaryOperation::free()
{
	delete f1;
	delete f2;
	f1 = f2 = nullptr;
}

void BinaryOperation::copyDynamic(const char ch, const Formula* f1, const Formula* f2)
{
	if (!f1 || !f2)
		throw std::invalid_argument("Missing formulas for bin operation");

	validateOperation(ch);

	this->f1 = f1->clone();
	try
	{
		this->f2 = f2->clone();
	}
	catch (...)
	{
		delete f1;
		throw;
	}
}

void BinaryOperation::swap(BinaryOperation& other)
{
	std::swap(ch, other.ch);
	std::swap(f1, other.f1);
	std::swap(f2, other.f2);
}

void BinaryOperation::validateOperation(const char ch)
{
	for (size_t i = 0; i < COUNT_OPERATIONS; i++)
	{
		if (ch == DEFINED_OPERAIONS[i])
			return;
	}

	throw std::invalid_argument("Undefined operation");
}
