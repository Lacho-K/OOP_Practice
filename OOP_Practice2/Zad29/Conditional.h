#pragma once
#include "Formula.h"

class Conditional : public Formula
{
public:
	Conditional(Formula* f1, Formula* f2, Formula* f3);
	Conditional(const Conditional& other);
	Conditional(Conditional&& other);

	Conditional& operator=(const Conditional& other);
	Conditional& operator=(Conditional&& other);

	virtual double value() const;

	virtual void print() const;

	virtual Formula* clone() const;

private:
	Formula* f1;
	Formula* f2;
	Formula* f3;

	void copyFormulas(Formula* f1, Formula* f2, Formula* f3);
	void swap(Conditional& other);
	void free();
};