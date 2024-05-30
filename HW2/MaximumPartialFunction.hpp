#include <iostream>
#include "PartialFunction.h"

class MaximumPartialFunction : public PartialFunction 
{
private:
    PartialFunction** functions;
    size_t capacity;
    size_t count;

    void copyFrom(const MaximumPartialFunction& other)
    {
        functions = new PartialFunction*[other.capacity];
        for (size_t i = 0; i < count; ++i)
        {
            functions[i] = other.functions[i]->clone();
        }
        capacity = other.capacity;
        count = other.count;
    }

    void moveFrom(MaximumPartialFunction&& other)
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
    MaximumPartialFunction() : functions(nullptr), capacity(0), count(0) {}

    MaximumPartialFunction(const MaximumPartialFunction& other)
    {
        copyFrom(other);
    }

    MaximumPartialFunction(MaximumPartialFunction&& other) noexcept
    {
        moveFrom(std::move(other));
    }

    MaximumPartialFunction(PartialFunction** funcs, size_t n) : capacity(n), count(n) 
    {
        functions = new PartialFunction*[capacity];
        for (size_t i = 0; i < n; ++i) 
        {
            functions[i] = funcs[i]->clone();
        }
    }

    MaximumPartialFunction& operator=(const MaximumPartialFunction& other) 
    {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    MaximumPartialFunction& operator=(MaximumPartialFunction&& other) noexcept 
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
        int32_t max_value = INT32_MIN;
        for (size_t i = 0; i < count; ++i) {
            int32_t value = functions[i]->operator()(x).result;
            if (value > max_value) {
                max_value = value;
            }
        }
        return {1,max_value};
    }

    virtual PartialFunction* clone() const override
    {
        return new MaximumPartialFunction(*this);
    }

    ~MaximumPartialFunction() {
        free();
    }
};
