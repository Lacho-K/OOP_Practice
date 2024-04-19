#include<iostream>
#include<fstream>
#include "MultiSet.h"

static unsigned getClosestPowerOfTwo(unsigned v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	unsigned power = 0;
	while (v)
	{
		power++;
		v /= 2;
	}

	return power - 1;
}

static unsigned toBinaryFromDecimal(unsigned int n)
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

void MultiSet::copyFrom(const MultiSet& other)
{
	buckets = new uint8_t[other.bucketsCount]();

	for (size_t i = 0; i < other.bucketsCount; i++)
	{
		buckets[i] = other.buckets[i];
	}

	n = other.n;
	k = other.k;

	bucketsCount = ((n * k) / BUCKET_SIZE) + 1;
	maxCount = (1 << k) - 1;
}

void MultiSet::free()
{
	delete[] buckets;
	buckets = nullptr;
}

MultiSet::MultiSet(int maxNumber, int maxCountBits) 
{
	n = maxNumber;
	k = maxCountBits;
	bucketsCount = ((n * k) / BUCKET_SIZE) + 1;
	maxCount = (1 << k) - 1;
	buckets = new uint8_t[bucketsCount]();
}


MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MultiSet::~MultiSet()
{
	free();
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
		unsigned copyOfK = k;
		unsigned copyOfBucketIndex = bucketIndex;
		mask <<= bitIndex;

		while (checkBit(buckets[copyOfBucketIndex], bitIndexCopy) && copyOfK > 0)
		{
			buckets[copyOfBucketIndex] ^= mask;

			mask <<= 1;
			bitIndexCopy++;
			copyOfK--;

			if (bitIndexCopy >= BUCKET_SIZE)
			{
				copyOfBucketIndex++;
				mask = 1;
				bitIndexCopy = 0;
			}
		}

		buckets[copyOfBucketIndex] |= mask;
	}
	else
	{
		std::cerr << "Error: Maximum count reached for number " << num << std::endl;
	}
}

void MultiSet::remove(int num) 
{

	if (num < 0 || num > n) 
	{
		std::cerr << "Error: Number out of range!" << std::endl;
		return;
	}

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = getBitIndex(num);

	if (count(num) > 0) 
	{

		unsigned mask = 1;
		unsigned bitIndexCopy = bitIndex;
		unsigned copyOfK = k;
		unsigned copyOfBucketIndex = bucketIndex;
		mask <<= bitIndex;

		while (!checkBit(buckets[copyOfBucketIndex], bitIndexCopy) && copyOfK > 0)
		{
			buckets[copyOfBucketIndex] |= mask;

			mask <<= 1;
			bitIndexCopy++;
			copyOfK--;

			if (bitIndexCopy >= BUCKET_SIZE)
			{
				copyOfBucketIndex++;
				mask = 1;
				bitIndexCopy = 0;
			}
		}

		makeBitZero(buckets[copyOfBucketIndex], bitIndexCopy);
	}
	else 
	{
		std::cerr << "Error: Number " << num << " not found!" << std::endl;
	}
}

unsigned MultiSet::getCountBits(unsigned bitIndex, unsigned bucketIndex) const
{
	unsigned resultMask = 0;

	for (size_t i = 0; i < k; i++)
	{
		if (bitIndex >= BUCKET_SIZE)
		{
			bucketIndex++;
			bitIndex = 0;
			resultMask |= (checkBit(buckets[bucketIndex], bitIndex) << i);
			bitIndex++;
			continue;
		}

		resultMask |= (checkBit(buckets[bucketIndex], bitIndex) << i);
		bitIndex++;
	}

	return resultMask;
}

unsigned MultiSet::getBitIndex(unsigned num) const
{
	return (num * k) % BUCKET_SIZE;
}

unsigned MultiSet::getBucketIndex(const unsigned num) const
{
	return (num * k) / BUCKET_SIZE;
}


unsigned MultiSet::count(unsigned num) const
{
	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = getBitIndex(num);
	return getCountBits(bitIndex, bucketIndex);
}

void MultiSet::printAll() const 
{
	std::cout << '{' << " ";
	for (unsigned i = 0; i < n; ++i) 
	{
		unsigned count = this->count(i);
		for (unsigned j = 0; j < count; ++j) 
		{
			std::cout << i << " ";
		}
	}
	std::cout << '}' << std::endl;
}

void MultiSet::printMemoryRepresantation() const
{
	for (unsigned i = 0; i < bucketsCount; i++)
	{
		std::cout << "Bucket " << i << ":" << toBinaryFromDecimal(buckets[i]) << std::endl;
	}
}

static MultiSet unionOfSets(const MultiSet& lhs, const MultiSet& rhs)
{
	unsigned resultN = std::max(lhs.n, rhs.n);
	unsigned resultK = getClosestPowerOfTwo(lhs.maxCount + rhs.maxCount);
	MultiSet resultMS(resultN, resultK);

	for (size_t i = 0; i < lhs.n; i++)
	{
		unsigned insertCount = lhs.count(i);
		for (size_t j = 0; j < insertCount; j++)
		{
			resultMS.insert(i);
		}
	}

	for (size_t i = 0; i < rhs.n; i++)
	{
		unsigned insertCount = rhs.count(i);
		for (size_t j = 0; j < insertCount; j++)
		{
			resultMS.insert(i);
		}
	}

	return resultMS;
}

void serialize(std::ofstream& ofs, const MultiSet& set)
{
	ofs.write((const char*)&set.n, sizeof(set.n));
	ofs.write((const char*)&set.k, sizeof(set.k));

	for (size_t i = 0; i < set.bucketsCount; i++)
	{
		ofs.write((const char*)&set.buckets[i], sizeof(set.buckets[i]));
	}
	
	ofs.close();
}

MultiSet deserialize(std::ifstream& ifs)
{
	unsigned n;
	unsigned k;

	ifs.read((char*)&n, sizeof(n));
	ifs.read((char*)&k, sizeof(k));

	MultiSet resultSet(n, k);

	for (size_t i = 0; i < resultSet.bucketsCount; i++)
	{
		ifs.read((char*)&resultSet.buckets[i], sizeof(resultSet.buckets[i]));
	}

	ifs.close();

	return resultSet;
}

static MultiSet intersectionOfSets(const MultiSet& lhs, const MultiSet& rhs)
{
	unsigned resultN = std::min(lhs.n, rhs.n);
	unsigned resultK = std::min(lhs.k, rhs.k);
	MultiSet resultMS(resultN, resultK);

	for (size_t i = 0; i < resultN; i++)
	{
		unsigned insertCount = std::min(lhs.count(i), rhs.count(i));

		for (size_t j = 0; j < insertCount; j++)
		{
			resultMS.insert(i);
		}

	}

	return resultMS;
}

static MultiSet additionOfSet(const MultiSet& set)
{
	MultiSet resultMS(set.n, set.k);

	for (size_t i = 0; i < set.n; i++)
	{
		unsigned insertCount = set.maxCount - set.count(i);
		for (size_t j = 0; j < insertCount; j++)
		{
			resultMS.insert(i);
		}
	}

	return resultMS;
}


int main()
{
	MultiSet ms1(10, 5);
	MultiSet ms2(15, 2);

	ms1.insert(5);
	ms1.insert(5);
	ms1.insert(5);
	ms1.insert(1);
	ms1.insert(1);
	ms1.insert(1);
	ms1.insert(8);

	ms2.insert(5);
	ms2.insert(5);
	ms2.insert(8);
	ms2.insert(8);
	ms2.insert(7);
	ms2.insert(7);
	ms2.insert(6);
	ms2.insert(6);
	ms2.insert(6);

	ms1.printAll();
	ms2.printAll();

	std::cout << std::endl;
	ms1.printMemoryRepresantation();
	std::cout << std::endl;
	ms2.printMemoryRepresantation();
	std::cout << std::endl;

	MultiSet serializeSet(15, 5);

	std::ofstream ofs("test.dat", std::ios::binary);

	if (!ofs.is_open())
		return -1;

	serializeSet.insert(1);
	serializeSet.insert(2);
	serializeSet.insert(3);
	serializeSet.insert(4);
	serializeSet.insert(4);

    serialize(ofs, serializeSet);
	
	std::ifstream ifs("test.dat", std::ios::binary);

	if (!ifs.is_open())
		return -1;

	MultiSet deserializeSet =  deserialize(ifs);

	deserializeSet.printAll();

	MultiSet unionSet = unionOfSets(ms1, ms2);
	MultiSet interseCtionSet = intersectionOfSets(ms1, ms2);
	MultiSet additionSet = additionOfSet(ms2);

	unionSet.printAll();
	interseCtionSet.printAll();
	additionSet.printAll();
}