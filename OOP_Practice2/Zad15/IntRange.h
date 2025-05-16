#pragma once
#include "IntSet.h";
class IntRange : public IntSet
{

public:
	IntRange() = default;
	IntRange(int min, int max);

	virtual bool member(int x) const override;
	virtual int get(int x) const override;
	virtual size_t size() const override;
	virtual bool operator<(const IntSet& other) const override;
	virtual bool operator*(const IntSet& other) const override;
private:

	int min, max = 0;
};