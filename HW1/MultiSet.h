#pragma once

constexpr unsigned BUCKET_SIZE = (sizeof(uint8_t) * 8);


class MultiSet {
private:
    uint8_t* buckets;
    unsigned n;
    int k;
    unsigned bucketsCount;
    unsigned maxCount;
    void copyFrom(const MultiSet& other);
    void free();

public:
    MultiSet(int maxNumber, int maxCountBits);
    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);
    ~MultiSet();
    void insert(int num);
    void remove(int num);
    unsigned count(unsigned num) const;
    void printAll() const;
    void printMemoryRepresantation() const;

    friend MultiSet unionOfSets(const MultiSet& lhs, const MultiSet& rhs);
    friend MultiSet intersectionOfSets(const MultiSet& lhs, const MultiSet& rhs);
    friend MultiSet additionOfSet(const MultiSet& set);
    friend void serialize(std::ofstream& ofs, const MultiSet& set);
    friend MultiSet deserialize(std::ifstream& ifs);

private:
    unsigned getBitIndex(unsigned num) const;
    unsigned getBucketIndex(const unsigned num) const;
    unsigned getCountBits(unsigned bitIndex, unsigned bucketIndex) const;
};