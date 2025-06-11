#pragma once
#include "Formula.h"

class BinaryOperation : public Formula
{
public:

	BinaryOperation(const char ch, const Formula* f1, const Formula* f2);
	BinaryOperation(const BinaryOperation& other);
	BinaryOperation(BinaryOperation&& other);

	BinaryOperation& operator=(const BinaryOperation& other);
	BinaryOperation& operator=(BinaryOperation&& other);

	~BinaryOperation();

	virtual Formula* clone() const;

	virtual void print() const;

	virtual double value() const;

private:
	Formula* f1;
	Formula* f2;
	char ch;

	constexpr static unsigned COUNT_OPERATIONS = 7;
	constexpr static char DEFINED_OPERAIONS[COUNT_OPERATIONS] = "+-*/<=";

	void free();
	void copyDynamic(const char ch, const Formula* f1, const Formula* f2);
	void swap(BinaryOperation& other);
	void validateOperation(const char ch);
};