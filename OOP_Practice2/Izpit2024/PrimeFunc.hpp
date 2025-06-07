#pragma once
#include "Generator.hpp"
#include <climits>

class PrimeFunc : public Generator<unsigned>
{
public:
    PrimeFunc(unsigned startVal, unsigned maxNum) : startVal(startVal), currentVal(startVal), maxNum(maxNum) {}
    PrimeFunc() : PrimeFunc(2, UINT_MAX) {}
    explicit PrimeFunc(unsigned maxNum) : PrimeFunc(2, maxNum) {}

    const unsigned& next() override
    {
        for (unsigned i = currentVal + 1; i < maxNum; i++)
        {
            bool isPrime = true;
            for (unsigned j = 2; j * j <= i; j++)
            {
                if (i % j == 0)
                {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime)
            {
                currentVal = i;
                return currentVal;
            }
        }
        return currentVal;
    }

    const unsigned& operator()() const override
    {
        return currentVal;
    }

    bool canContinue() const override
    {
        return currentVal < maxNum;
    }

    bool reset() override
    {
        currentVal = startVal;
        return true;
    }

    Generator<unsigned>* clone() const override
    {
        return new PrimeFunc(*this);
    }

private:
    unsigned startVal;
    unsigned currentVal;
    unsigned maxNum;
};