#include<iostream>
#include "MultiSet.h"

unsigned int fromBinaryToDecimal(unsigned int n)
{
	unsigned int result = 0;
	unsigned int mult = 1; //2^0
	while (n != 0)
	{
		result += ((n % 10) * mult);
		mult *= 2;
		n /= 10;
	}
	return result;
}

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

void makeBitZero(uint8_t& n, unsigned int ind) //clear bit
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

class MultiSet {
private:
	int n;
	int k;
	uint8_t* counts;
	unsigned bucketsCount;
	unsigned bucketSize = (sizeof(uint8_t) * 8);
	unsigned elementsInBucket;
	unsigned maxCount;

public:
	MultiSet(int maxNumber, int maxCountBits) : n(maxNumber), k(maxCountBits) {
		bucketsCount = (n / (bucketSize / k)) + 1;
		bucketSize = (sizeof(uint8_t) * 8);
		elementsInBucket = bucketSize / k;
	    maxCount = (1 << k) - 1;
		counts = new uint8_t[bucketsCount]();
	}

	~MultiSet() {
		delete[] counts;
	}

	void insert(int num) 
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

	int checkBits(unsigned int n, unsigned ind)
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

	unsigned getBitIndex(unsigned num) const
	{
		return (num % elementsInBucket) * k;
	}

	unsigned getBucketIndex(const unsigned num) const
	{
		return num / elementsInBucket;
	}


	void remove(int num) {

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

	int count(int num) const {
		if (num < 0 || num > n) {
			std::cerr << "Error: Number out of range!" << std::endl;
			return -1;
		}
		int bucketIndex = getBucketIndex(num);
		int offset = getBitIndex(num);
		unsigned char mask = maxCount;
		return (counts[bucketIndex] >> offset) & mask;
	}

	void printAll() const {
		std::cout << '{' << " ";
		for (unsigned i = 0; i <= n; ++i) {
			unsigned count = this->count(i);
			for (unsigned j = 0; j < count; ++j) {
				std::cout << i << " ";
			}
		}
		std::cout << '}' << std::endl;
	}

	void printMemoryRepresantation() const 
	{
		for (unsigned i = 0; i < bucketsCount; i++)
		{
			std::cout << "Bucket " << i << ":" << toBinaryFromDecimal(counts[i]) << std::endl;
		}
	}
};

int main() {
	MultiSet ms(10, 2); // Example with numbers from 0 to 10 and up to 2^3 - 1 repetitions

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
	ms.printAll();
	ms.printMemoryRepresantation();
	ms.insert(7);

	return 0;
}