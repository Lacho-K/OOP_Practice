#include<iostream>
#include "MultiSet.h"

static unsigned int reverse(unsigned int n)
{
	unsigned reversedNumber = 0;

	while (n != 0)
	{
		unsigned int lastDigit = n % 10;
		(reversedNumber *= 10) += lastDigit;
		n /= 10; //removes the last digit
	}
	return reversedNumber;

}

static unsigned int toBinaryFromDecimal(unsigned int n)
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

static unsigned fromBinaryToDecimal(unsigned n)
{
	unsigned result = 0;
	unsigned mult = 1; //2^0
	while (n != 0)
	{
		result += ((n % 10) * mult);
		mult *= 2;
		n /= 10;
	}
	return result;
}

static void makeBitZero(uint8_t& n, unsigned int ind)
{
	unsigned int mask = 1;
	mask <<= ind;

	mask = ~mask;

	n &= mask;
}

static bool checkBit(unsigned int n, unsigned ind)
{
	unsigned int mask = 1;
	mask <<= ind;
	return (mask & n) == mask;
}


MultiSet::MultiSet(int maxNumber, int maxCountBits) : n(maxNumber), k(maxCountBits) {
	bucketsCount = ((n * k) / bucketSize) + 1;
	bucketSize = (sizeof(uint8_t) * 8);
	//elementsInBucket = bucketSize / k;
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

	//std::cout << count(num);
	std::cout << checkBits(counts[bucketIndex], bitIndex, bucketIndex) << std::endl;

	if (count(num) < maxCount)
	{
		unsigned mask = 1;
		unsigned bitIndexCopy = bitIndex;
		unsigned copyOfK = k;
		mask <<= bitIndex;

		while (checkBit(counts[bucketIndex], bitIndex) && copyOfK > 0)
		{
			counts[bucketIndex] ^= mask;
			if (bitIndexCopy > bucketSize)
			{
				bucketIndex++;
				mask = 1;
				bitIndex = 0;
				continue;
			}

			mask <<= 1;
			bitIndexCopy++;
			copyOfK--;
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

unsigned MultiSet::checkBits(unsigned currentBucket, unsigned bitIndex, unsigned bucketIndex) const
{
	int result = 0;
	unsigned int mask = 1;
	mask <<= bitIndex;
	for (size_t i = 0; i < k; i++)
	{
		if (bitIndex >= bucketSize)
		{
			currentBucket = counts[bucketIndex + 1];
			mask = 1;
			(result *= 10) += ((mask & currentBucket) == mask);
			bitIndex = 0;
			mask <<= 1;
			continue;
		}
		(result *= 10) += ((mask & currentBucket) == mask);
		bitIndex++;
		mask <<= 1;
	}
	return result;
}

unsigned MultiSet::getBitIndex(unsigned num) const
{
	return (num * k) % bucketSize;
}

unsigned MultiSet::getBucketIndex(const unsigned num) const
{
	return (num * k) / bucketSize;
}


unsigned MultiSet::count(unsigned num) const 
{
	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = getBitIndex(num);
	return fromBinaryToDecimal(checkBits(counts[bucketIndex], bitIndex, bucketIndex));
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
	MultiSet ms(10, 3);

	ms.insert(5);
	//ms.insert(5);

	ms.printAll();

	/*ms.remove(5);

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
	ms.insert(7);*/

	return 0;
}