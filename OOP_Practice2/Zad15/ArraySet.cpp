#include "ArraySet.h"
#include <stdexcept>

ArraySet::ArraySet() : nums(nullptr), count(0), cap(8)
{
	nums = new int[cap];
}

ArraySet::ArraySet(size_t cap):count(0)
{
	nums = new int[cap];
	this->cap = cap;
}

ArraySet::ArraySet(const ArraySet& other)
{
	ensureValidObject(other);
	try
	{
		copyDynamic(other);
		this->count = other.count;
		this->cap = other.cap;
	}
	catch (...)
	{
		free();
		throw;
	}
}

ArraySet::ArraySet(ArraySet&& other)
{
	ensureValidObject(other);

	nums = other.nums;
	cap = other.cap;
	count = other.count;

	other.nums = nullptr;
	other.cap = other.count = 0;
}

ArraySet& ArraySet::operator=(const ArraySet& other)
{
	if (this != &other)
	{
		ArraySet temp(other);
		swap(temp);
	}
	return *this;
}

ArraySet& ArraySet::operator=(ArraySet&& other)
{
	if (this != &other)
	{
		ArraySet temp(std::move(other));
		swap(temp);
	}
	return *this;
}

bool ArraySet::member(int x) const
{
	for (size_t i = 0; i < count; i++)
	{
		if (x == nums[i])
			return true;
	}

	return false;
}

int ArraySet::get(int index) const
{
	if (index < 0 || index >= count)
		throw std::out_of_range("Index out of range");

	return nums[index];
}

bool ArraySet::operator<(const IntSet& other) const
{
	size_t mySize = size();
	size_t otherSize = other.size();

	for (size_t i = 0; i < mySize; i++)
	{
		int x = get(i);
		if (!other.member(x))
			return false;
	}

	for (size_t i = 0; i < other.size(); i++)
	{
		int x = other.get(i);
		if (!member(x))
			return true;
	}

	return false;
}


bool ArraySet::operator*(const IntSet& other) const
{
	size_t mySize = size();
	for (size_t i = 0; i < mySize; i++)
	{
		int x = get(i);
		if (other.member(x))
			return true;
	}

	return false;
}

size_t ArraySet::size() const
{
	return count;
}

ArraySet::~ArraySet()
{
	free();
}

void ArraySet::ensureValidObject(const ArraySet& other) const
{
	if (other.count > other.cap || !other.nums)
		throw std::invalid_argument("Invalid object");
}

void ArraySet::free()
{
	delete[] nums;
	nums = nullptr;
}

bool ArraySet::insert(int x)
{
	if (count == cap || member(x))
		return false;

	nums[count++] = x;

	return true;
}

bool ArraySet::remove(int x)
{
	if (size() == 0 || !member(x))
		return false;

	int targetIndex = -1;
	for (size_t i = 0; i < size(); i++)
	{
		if (get(i) == x)
		{
			targetIndex = i;
			break;
		}
	}

	std::swap(nums[targetIndex], nums[count - 1]);
	count--;

	return true;
}

void ArraySet::copyDynamic(const ArraySet& other)
{
	ensureValidObject(other);
	nums = new int[other.cap];
	for (size_t i = 0; i < other.cap; i++)
	{
		nums[i] = other.nums[i];
	}
}

void ArraySet::swap(ArraySet& other)
{
	std::swap(nums, other.nums);
	std::swap(cap, other.cap);
	std::swap(count, other.count);
}

