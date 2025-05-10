#pragma once
#include <iostream>

constexpr uint16_t MAX_SIZE = 65535;

class ModifiableIntegerFunction {
private:
    int16_t(*function)(int16_t);
    int16_t results[MAX_SIZE];
    bool isExcluded[MAX_SIZE];

    uint16_t getIndexOfNum(int16_t num) const {
        return num < 0 ? (MAX_SIZE / 2 - 1) - num : num;
    }

public:
    ModifiableIntegerFunction(int16_t(*func)(int16_t));

    int16_t apply(int16_t num);

    void setFunction(int16_t(*func)(int16_t));

    void setResults(int16_t input, int16_t result);

    const int16_t* getResults() const;

    const bool* getExcludedValues() const;

    int16_t(*getFunction())(int16_t);

    void excludePoint(int16_t input);

    bool isInjection() const;

    bool isSurjection() const;

    bool isBijection() const;
};