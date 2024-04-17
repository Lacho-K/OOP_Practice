#pragma once
class MultiSet {
private:
    int n;
    int k;
    uint8_t* counts;
    unsigned bucketsCount;
    unsigned bucketSize = (sizeof(uint8_t) * 8);
    unsigned maxCount;
    unsigned elementsInBucket;

public:
    MultiSet(int maxNumber, int maxCountBits);
    ~MultiSet();
    void insert(int num);
    void remove(int num);
    int count(int num) const;
    void printAll() const;
    void printMemoryRepresantation() const;

private:
    unsigned getBitIndex(unsigned num) const;
    unsigned getBucketIndex(const unsigned num) const;
    int checkBits(unsigned int n, unsigned ind);
};