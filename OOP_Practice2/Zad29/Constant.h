#pragma once
#include "Formula.h"

class Constant : public Formula
{
public:

	Constant();
	explicit Constant(double val);

	virtual double value() const override;
	virtual void print() const override;
	virtual Formula* clone() const;

private:
	const double val;
};