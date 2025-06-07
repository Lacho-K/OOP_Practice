#pragma once
#include "Generator.hpp"
#include <cstdlib>
#include <ctime>
#include <climits>

class RandomFunc : public Generator<unsigned>
{
public:
    RandomFunc(unsigned minVal, unsigned maxVal) : minVal(minVal), maxVal(maxVal)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        currentVal = getRandInRange();
    }

    RandomFunc() : RandomFunc(0, UINT_MAX) {}

    const unsigned& next() override
    {
        currentVal = getRandInRange();
        return currentVal;
    }

    const unsigned& operator()() const override
    {
        return currentVal;
    }

    bool canContinue() const override
    {
        return true;
    }

    bool reset() override
    {
        currentVal = getRandInRange();
        return true;
    }

    Generator<unsigned>* clone() const override
    {
        return new RandomFunc(*this);
    }

private:
    unsigned minVal;
    unsigned maxVal;
    unsigned currentVal;

    unsigned getRandInRange() const
    {
        unsigned range = maxVal - minVal;
        if (range == UINT_MAX)
            range--; // avoid overflow

        if (range == 0)
            return minVal;

        return minVal + (std::rand() % (range + 1));
    }

};