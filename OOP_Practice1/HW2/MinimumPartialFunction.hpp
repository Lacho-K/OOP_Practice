#include <iostream>
#include "PartialFunction.h"

class MinimumPartialFunction : public PartialFunction
{
private:
    PartialFunction** functions;
    size_t capacity;
    size_t count;

    void copyFrom(const MinimumPartialFunction& other)
    {
        functions = new PartialFunction * [other.capacity];
        capacity = other.capacity;
        count = other.count;
        for (size_t i = 0; i < count; ++i)
        {
            functions[i] = other.functions[i]->clone();
        }
    }

    void moveFrom(MinimumPartialFunction&& other)
    {
        functions = other.functions;
        capacity = other.capacity;
        count = other.count;

        other.functions = nullptr;
        other.capacity = 0;
        other.count = 0;
    }

    void free()
    {
        for (size_t i = 0; i < count; i++)
        {
            delete functions[i];
        }
        delete[] functions;
    }

public:
    MinimumPartialFunction() : functions(nullptr), capacity(0), count(0) {}

    MinimumPartialFunction(const MinimumPartialFunction& other)
    {
        copyFrom(other);
    }

    MinimumPartialFunction(MinimumPartialFunction&& other) noexcept
    {
        moveFrom(std::move(other));
    }

    MinimumPartialFunction(PartialFunction** funcs, size_t n) : capacity(n), count(n)
    {
        functions = new PartialFunction * [capacity];
        for (size_t i = 0; i < n; ++i)
        {
            functions[i] = funcs[i]->clone();
        }
    }

    MinimumPartialFunction& operator=(const MinimumPartialFunction& other)
    {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    MinimumPartialFunction& operator=(MinimumPartialFunction&& other) noexcept
    {
        if (this != &other) {
            free();
            moveFrom(std::move(other));
        }
        return *this;
    }


    bool isDefinedAt(int x) const override {
        for (size_t i = 0; i < count; ++i) {
            if (!functions[i]->isDefinedAt(x))
                return false;
        }
        return true;
    }

    FuncResult operator()(int x) const override {
        if (!isDefinedAt(x)) {
            throw std::runtime_error("Function is not defined at this point");
        }
        int32_t min_value = INT32_MAX;
        for (size_t i = 0; i < count; ++i) {
            int32_t value = functions[i]->operator()(x).result;
            if (value < min_value) {
                min_value = value;
            }
        }
        return { 1,min_value };
    }

    virtual PartialFunction* clone() const override
    {
        return new MinimumPartialFunction(*this);
    }

    ~MinimumPartialFunction() {
        free();
    }
};
