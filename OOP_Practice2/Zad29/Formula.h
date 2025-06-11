#pragma once
class Formula
{
public:
	virtual double value() const = 0;
	virtual void print() const = 0;
	virtual Formula* clone() const = 0;
	virtual ~Formula() = default;
};