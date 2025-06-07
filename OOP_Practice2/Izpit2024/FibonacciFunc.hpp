#pragma once
#include "Generator.hpp"
#include <climits>

class FibonacciFunc : public Generator<unsigned>
{
public:
    FibonacciFunc(unsigned maxNum) : a(0), b(1), currentVal(0), maxNum(maxNum) {}
    FibonacciFunc() : FibonacciFunc(UINT_MAX) {}

    const unsigned& next() override
    {
        unsigned nextVal = a + b;
        a = b;
        b = nextVal;

        if (nextVal > maxNum)
            currentVal = maxNum;
        else
            currentVal = nextVal;

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
        a = 0;
        b = 1;
        currentVal = 0;
        return true;
    }

    Generator<unsigned>* clone() const override
    {
        return new FibonacciFunc(*this);
    }

private:
    unsigned a;
    unsigned b;
    unsigned currentVal;
    unsigned maxNum;
};