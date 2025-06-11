#pragma once
#include "Formula.h"
class Read : public Formula
{
public:

	virtual double value() const;
	virtual void print() const;
	virtual Formula* clone() const;

	Read();

private:
	double data;
};