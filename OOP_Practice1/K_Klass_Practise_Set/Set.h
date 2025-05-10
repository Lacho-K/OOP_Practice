#pragma once
class Set
{
protected:
	virtual Set* copy() = 0;

public:

	virtual bool member(int x) const = 0;
};