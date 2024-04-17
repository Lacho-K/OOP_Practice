#include<iostream>

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
		bucketsCount = n / (bucketSize / k);
		bucketSize = (sizeof(uint8_t) * 8);
		elementsInBucket = bucketSize / k;
	    maxCount = (1 << k) - 1;
		counts = new uint8_t[bucketsCount]();
	}

	~MultiSet() {
		delete[] counts;
	}

	void insert(int num) {
		if (num < 0 || num > n) 
		{
			std::cerr << "Error: Number out of range!" << std::endl;
			return;
		}

		unsigned bucketIndex = getBucketIndex(num);
		unsigned bitIndex = getBitIndex(num);

		if (fromBinaryToDecimal(checkBits(counts[bucketIndex], bitIndex)) < maxCount)
		{
			counts[bucketIndex] <<= k * bitIndex;
			counts[bucketIndex] ++;
			counts[bucketIndex] >>= k * bitIndex;
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
			n >>= 1;
		}
		return result;
	}

	unsigned getBitIndex(unsigned num) const
	{
		return num / elementsInBucket;
	}

	unsigned getBucketIndex(const unsigned num) const
	{
		return num / bucketSize;
	}


	void remove(int num) {
		if (num < 0 || num > n) {
			std::cerr << "Error: Number out of range!" << std::endl;
			return;
		}
		if (counts[num] > 0) {
			counts[num]--;
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
		return counts[num];
	}

	void printAll() const {
		std::cout << '{';
		for (unsigned i = 0; i <= n; ++i) {
			unsigned count = this->count(i);
			for (unsigned j = 0; j < count; ++j) {
				std::cout << i << " ";
			}
		}
		std::cout << '}' << std::endl;
	}

	void printMemoryRepresentation() const {
		std::cout << "Memory representation:" << std::endl;
		for (unsigned i = 0; i < n; ++i) {
			std::cout << "Bucket " << i << ": " << static_cast<int>(counts[i]) << std::endl;
		}
	}
};

int main() {
	MultiSet ms(10, 3); // Example with numbers from 0 to 10 and up to 2^3 - 1 repetitions

	ms.insert(5);
	ms.insert(5);
	ms.insert(5);
	ms.insert(7);
	ms.insert(7);
	ms.insert(7);
	ms.insert(7);

	std::cout << "Count of 5: " << ms.count(5) << std::endl;
	std::cout << "Count of 7: " << ms.count(7) << std::endl;
	ms.printAll();


	ms.remove(5);
	ms.remove(7);

	std::cout << "Count of 5 after removal: " << ms.count(5) << std::endl;
	std::cout << "Count of 7 after removal: " << ms.count(7) << std::endl;
	ms.printAll();
	ms.printMemoryRepresentation();

	return 0;
}