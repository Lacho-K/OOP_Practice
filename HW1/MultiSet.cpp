#pragma once
#include<iostream>
#include "MultiSet.h"

unsigned int toBinaryFromDecimal(unsigned int n)
{
	int result = 0;
	int mult = 1;
	while (n != 0)
	{
		if (n % 2 == 1)
			result += mult;
		mult *= 10;
		n /= 2;
	}
	return result;
}

void makeBitZero(uint8_t& n, unsigned int ind)
{
	unsigned int mask = 1;
	mask <<= ind;

	mask = ~mask;

	n &= mask;
}

bool checkBit(unsigned int n, unsigned ind)
{
	unsigned int mask = 1;
	mask <<= ind;
	return (mask & n) == mask;
}


MultiSet::MultiSet(int maxNumber, int maxCountBits) : n(maxNumber), k(maxCountBits) {
	bucketsCount = (n / (bucketSize / k)) + 1;
	bucketSize = (sizeof(uint8_t) * 8);
	elementsInBucket = bucketSize / k;
	maxCount = (1 << k) - 1;
	counts = new uint8_t[bucketsCount]();
}

MultiSet::~MultiSet() {
	delete[] counts;
}

void MultiSet::insert(int num)
{

	if (num < 0 || num > n)
	{
		std::cerr << "Error: Number out of range!" << std::endl;
		return;
	}

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = getBitIndex(num);

	if (count(num) < maxCount)
	{
		unsigned mask = 1;
		unsigned bitIndexCopy = bitIndex;
		mask <<= bitIndex;

		while (checkBit(counts[bucketIndex], bitIndex) && bitIndexCopy < (bitIndex + k))
		{
			counts[bucketIndex] ^= mask;
			mask <<= 1;
			bitIndexCopy++;
		}

		counts[bucketIndex] |= mask;
	}
	else
	{
		std::cerr << "Error: Maximum count reached for number " << num << std::endl;
	}
}

void MultiSet::remove(int num) {

	if (num < 0 || num > n) {
		std::cerr << "Error: Number out of range!" << std::endl;
		return;
	}

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = getBitIndex(num);

	if (count(num) > 0) {

		unsigned mask = 1;
		unsigned bitIndexCopy = bitIndex;
		mask <<= bitIndex;

		while (!checkBit(counts[bucketIndex], bitIndex) && bitIndexCopy < (bitIndex + k))
		{
			counts[bucketIndex] |= mask;
			mask <<= 1;
			bitIndexCopy++;
		}

		makeBitZero(counts[bucketIndex], bitIndexCopy);
	}
	else {
		std::cerr << "Error: Number " << num << " not found!" << std::endl;
	}
}

int MultiSet::checkBits(unsigned int n, unsigned ind)
{
	int result = 0;
	unsigned int mask = 1;
	mask <<= ind;
	for (size_t i = 0; i < k; i++)
	{
		(result *= 10) += ((mask & n) == mask);
		n <<= 1;
	}
	return result;
}

unsigned MultiSet::getBitIndex(unsigned num) const
{
	return (num % elementsInBucket) * k;
}

unsigned MultiSet::getBucketIndex(const unsigned num) const
{
	return num / elementsInBucket;
}


int MultiSet::count(int num) const {
	if (num < 0 || num > n) {
		std::cerr << "Error: Number out of range!" << std::endl;
		return -1;
	}
	int bucketIndex = getBucketIndex(num);
	int offset = getBitIndex(num);
	unsigned char mask = maxCount;
	return (counts[bucketIndex] >> offset) & mask;
}

void MultiSet::printAll() const {
	std::cout << '{' << " ";
	for (unsigned i = 0; i <= n; ++i) {
		unsigned count = this->count(i);
		for (unsigned j = 0; j < count; ++j) {
			std::cout << i << " ";
		}
	}
	std::cout << '}' << std::endl;
}

void MultiSet::printMemoryRepresantation() const
{
	for (unsigned i = 0; i < bucketsCount; i++)
	{
		std::cout << "Bucket " << i << ":" << toBinaryFromDecimal(counts[i]) << std::endl;
	}
}


int main() {
	MultiSet ms(10, 2);

	ms.insert(5);
	ms.insert(5);
	ms.insert(5);

	ms.remove(5);

	ms.insert(7);

	ms.remove(7);

	ms.insert(1);
	ms.insert(1);
	ms.insert(1);

	ms.remove(1);
	ms.remove(1);
	ms.insert(2);
	ms.printAll();
	ms.printMemoryRepresantation();
	ms.insert(7);

	return 0;
}