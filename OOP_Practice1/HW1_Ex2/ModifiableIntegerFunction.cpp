#include <iostream>
#include <fstream>
#include "ModifiableIntegerFunction.h"

static uint16_t getIndexOfNum(int16_t num) {
    return num < 0 ? (MAX_SIZE / 2 - 1) - num : num;
}

ModifiableIntegerFunction::ModifiableIntegerFunction(int16_t(*func)(int16_t)) {
    function = func;
    for (int i = INT16_MIN; i < INT16_MAX; ++i) {
        uint16_t index = getIndexOfNum(i);
        isExcluded[index] = false;
        if (func)
            results[index] = function(i);
    }
}

int16_t ModifiableIntegerFunction::apply(int16_t num) {
    uint16_t index = getIndexOfNum(num);

    if (isExcluded[index]) {
        throw std::invalid_argument("Function is not defined");
    }
    else if (function != nullptr) {
        return results[index];
    }
}

void ModifiableIntegerFunction::setFunction(int16_t(*func)(int16_t)) {
    function = func;
    for (int i = 0; i < MAX_SIZE; ++i) {
        isExcluded[i] = false;
        results[i] = -1;
    }
}

void ModifiableIntegerFunction::setResults(int16_t input, int16_t result) {
    uint16_t index = getIndexOfNum(input);
    results[index] = result;
}

const int16_t* ModifiableIntegerFunction::getResults() const {
    return results;
}

const bool* ModifiableIntegerFunction::getExcludedValues() const {
    return isExcluded;
}

int16_t(*ModifiableIntegerFunction::getFunction())(int16_t) {
    return function;
}

void ModifiableIntegerFunction::excludePoint(int16_t input) {
    isExcluded[getIndexOfNum(input)] = true;
}

bool ModifiableIntegerFunction::isInjection() const {
    for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        uint16_t indI = getIndexOfNum(i);
        for (int16_t j = INT16_MIN; j < INT16_MAX; j++) {
            if (i == j)
                continue;
            uint16_t indJ = getIndexOfNum(j);
            if (this->results[indI] == this->results[indJ])
                return false;
        }
    }
    return true;
}

bool ModifiableIntegerFunction::isSurjection() const {
    for (int16_t i = INT16_MIN; i < INT16_MAX; i++) {
        uint16_t index = getIndexOfNum(i);
        if (isExcluded[index])
            return false;
    }
    return true;
}

bool ModifiableIntegerFunction::isBijection() const {
    return isInjection() && isSurjection();
}

static ModifiableIntegerFunction operator+(const ModifiableIntegerFunction& f1, const ModifiableIntegerFunction& f2)
{
    ModifiableIntegerFunction result([](int16_t num) -> int16_t { return 0; });

    for (int i = INT16_MIN; i <= INT16_MAX; ++i)
    {
        uint16_t index = getIndexOfNum(i);
        if (!f1.getExcludedValues()[index] && !f2.getExcludedValues()[index]) {
            result.setResults(index, f1.getResults()[index] + f2.getResults()[index]);
        }
    }

    return result;
}

static ModifiableIntegerFunction operator-(const ModifiableIntegerFunction& f1, const ModifiableIntegerFunction& f2)
{
    ModifiableIntegerFunction result([](int16_t num) -> int16_t { return 0; });

    for (int i = INT16_MIN; i <= INT16_MAX; ++i)
    {
        uint16_t index = getIndexOfNum(i);
        if (!f1.getExcludedValues()[index] && !f2.getExcludedValues()[index]) {
            result.setResults(index, f1.getResults()[index] - f2.getResults()[index]);
        }
    }

    return result;
}

static ModifiableIntegerFunction operator*(ModifiableIntegerFunction& f1, ModifiableIntegerFunction& f2)
{
    ModifiableIntegerFunction result([](int16_t num) -> int16_t { return 0; });

    for (int i = INT16_MIN; i <= INT16_MAX; ++i)
    {
        uint16_t index = getIndexOfNum(i);
        if (!f1.getExcludedValues()[index] && !f2.getExcludedValues()[index]) {
            result.setResults(index, f1.apply(f2.apply(i)));
        }
    }

    return result;
}

static bool operator<(ModifiableIntegerFunction& f1, ModifiableIntegerFunction& f2)
{
    for (int num = INT16_MIN; num <= INT16_MAX; ++num)
    {
        if (f1.getExcludedValues()[num] || f2.getExcludedValues()[num])
        {
            continue;
        }
        else if (f1.apply(num) < f2.apply(num))
        {
            return true;
        }
    }
    return false;
}

static bool operator||(ModifiableIntegerFunction& f1, ModifiableIntegerFunction& f2)
{
    for (int num = INT16_MIN; num <= INT16_MAX; ++num)
    {
        if (f1.getExcludedValues()[num] || f2.getExcludedValues()[num])
        {
            continue;
        }
        else if (f1.apply(num) == f2.apply(num))
        {
            return false;
        }
    }
    return true;
}

static ModifiableIntegerFunction operator^ (ModifiableIntegerFunction f, unsigned k)
{
    static ModifiableIntegerFunction result(f.getFunction());
    for (int i = 1; i < k; i++)
    {
        result = result * f;
    }

    return result;
}

static ModifiableIntegerFunction operator~(ModifiableIntegerFunction f) {
    bool isFunctionDefined = false;

    for (int num = INT16_MIN; num <= INT16_MAX; ++num) {
        if (!f.getExcludedValues()[getIndexOfNum(num)]) {
            isFunctionDefined = true;
            break;
        }
    }

    if (!isFunctionDefined) {
        throw std::logic_error("Original function is not defined. Inverse function cannot be generated.");
    }

    ModifiableIntegerFunction inverse(f.getFunction());

    // Iterate over the results of the original function to set the inverse results
    for (int num = INT16_MIN; num <= INT16_MAX; ++num) {
        int16_t result = f.apply(num);
        if (!f.getExcludedValues()[getIndexOfNum(result)]) {
            inverse.setResults(result, num);
        }
    }

    return inverse;
}

static void serialize(const char* filename, ModifiableIntegerFunction f) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }
    file.write((const char*)(&f), sizeof(f));
    file.close();
}

ModifiableIntegerFunction deserialize(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for reading.");
    }
    ModifiableIntegerFunction obj(nullptr);
    file.read((char*)(&obj), sizeof(obj));
    file.close();
    return obj;
}

static int16_t sampleFunction(int16_t num) {
    return num * 2;
}

int main() 
{
    /*ModifiableIntegerFunction f1(sampleFunction);
    ModifiableIntegerFunction f2 = f1 + f1;
    ModifiableIntegerFunction f3 = f1 - f1;
    ModifiableIntegerFunction f4 = f1 * f1;

    std::cout << f2.apply(3) << std::endl;
    std::cout << f3.apply(4) << std::endl;
    std::cout << f4.apply(4) << std::endl;*/

    //ModifiableIntegerFunction functionObject(sampleFunction);

    //int16_t input = 5;
    //std::cout << "Input: " << input << std::endl;
    //std::cout << "Output: " << functionObject.apply(input) << std::endl;

    //functionObject.setFunction([](int16_t num) -> int16_t { return num * num; });

    //std::cout << "Input: " << input << std::endl;
    //std::cout << "Output: " << functionObject.apply(input) << std::endl;

    //functionObject.setCustomResult(3, 10);
    //std::cout << "Input: 3" << std::endl;
    //std::cout << "Output: " << functionObject.apply(3) << std::endl;

    //// Изключване на точка
    //functionObject.excludePoint(3);
    //std::cout << "Input: 3" << std::endl;
    //try {
    //    std::cout << "Output: " << functionObject.apply(3) << std::endl;
    //}
    //catch (const std::invalid_argument& e) {
    //    std::cout << "Exception caught: " << e.what() << std::endl;
    //}

    //ModifiableIntegerFunction function1([](int16_t num) -> int16_t { return num * 2; });
    // ModifiableIntegerFunction function2([](int16_t num) -> int16_t { return num * 3; });

    //std::cout << (function1 ^ 2).apply(2);
    //std::cout << (~function1).apply(2);
    

    ////Test operator<
    //std::cout << "Testing operator<: ";
    //if (function1 < function2) {
    //    std::cout << "function1 is less than function2" << std::endl;
    //}
    //else {
    //    std::cout << "function1 is not less than function2" << std::endl;
    //}

    // Test areParallel
    /*std::cout << "Testing areParallel: ";
    if (function1 || function2) {
        std::cout << "function1 and function2 are parallel" << std::endl;
    }
    else {
        std::cout << "function1 and function2 are not parallel" << std::endl;
    }*/

    // Test inverseFunction
    /*ModifiableIntegerFunction inverse = function1.inverseFunction();
    std::cout << "Testing inverseFunction: ";
    for (int16_t num = std::numeric_limits<int16_t>::min(); num <= std::numeric_limits<int16_t>::max(); ++num) {
        std::cout << "Input: " << num << ", Output: " << inverse.apply(num) << std::endl;
    }*/

    ModifiableIntegerFunction function([](int16_t num) -> int16_t{ return num * 2; });

    function.setResults(3, 10);
    function.setResults(5, 20);

    try {
        serialize("function_data.dat", function);
        std::cout << "Object serialized successfully." << std::endl;

        ModifiableIntegerFunction deserializedFunction(deserialize("function_data.dat").getFunction());

        std::cout << "Applying deserialized function:" << std::endl;
        std::cout << "Result for input 3: " << deserializedFunction.apply(3) << std::endl;
        std::cout << "Result for input 4: " << deserializedFunction.apply(4) << std::endl;
        std::cout << "Result for input 5: " << deserializedFunction.apply(5) << std::endl;
        std::cout << "Result for input 6: " << deserializedFunction.apply(6) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}
