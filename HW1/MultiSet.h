#pragma once
class MultiSet {
private:
    int n;
    int k;
    uint8_t* counts;
    unsigned bucketsCount;
    unsigned bucketSize = (sizeof(uint8_t) * 8);
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

private:
    unsigned getBitIndex(unsigned num) const;
    unsigned getBucketIndex(const unsigned num) const;
    unsigned getCountNumber(unsigned bitIndex, unsigned bucketIndex) const;
};