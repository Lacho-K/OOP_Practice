#pragma once
#include <iostream>

class MultiSet
{
	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned N = 0;
	const unsigned elementsInBucket = sizeof(uint8_t) * 8;

	void free();
	void copyFrom(const MultiSet& other);

	unsigned getBucketIndex(unsigned num) const;
public:
	MultiSet(unsigned n); // [0....n] (n + 1 �����)

	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	void add(unsigned num);
	void remove(unsigned num);
	bool contains(unsigned num) const;
	void print() const;
	friend MultiSet UnionOfSets(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet IntersectionOfSets(const MultiSet& lhs, const MultiSet& rhs);

};
