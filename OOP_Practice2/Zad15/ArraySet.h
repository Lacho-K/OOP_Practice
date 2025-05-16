#pragma once
#include "IntSet.h"
class ArraySet : public IntSet
{
public:
	ArraySet();
	explicit ArraySet(size_t cap);
	ArraySet(const ArraySet& other);
	ArraySet(ArraySet&& other);
	
	ArraySet& operator=(const ArraySet& other);
	ArraySet& operator=(ArraySet&& other);

	virtual bool member(int x) const override;
	virtual int get(int index) const override;
	virtual bool operator<(const IntSet& other) const override;
	virtual bool operator*(const IntSet& other) const override;
	virtual size_t size() const override;

	bool insert(int x);
	bool remove(int x);


	virtual ~ArraySet();

private:
	int* nums;
	size_t count;
	size_t cap;

	void swap(ArraySet& other);
	void copyDynamic(const ArraySet& other);
	void free();

	void ensureValidObject(const ArraySet& other) const;
};