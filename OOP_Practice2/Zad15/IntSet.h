#pragma once
class IntSet
{
public:

	virtual bool member(int x) const = 0;
	virtual int get(int i) const = 0;

	virtual bool operator<(const IntSet& other) const = 0;
	virtual bool operator*(const IntSet& other) const = 0;

	virtual size_t size() const = 0;

	virtual ~IntSet() = default;
};