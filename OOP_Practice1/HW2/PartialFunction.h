#pragma once
#include <iostream>

struct FuncResult
{
    bool defined;
    int result;
};

constexpr int MAX_POINTS = 32;

class PartialFunction 
{
public:
    virtual bool isDefinedAt(int32_t x) const = 0;
    virtual FuncResult operator()(int32_t x) const = 0;
    virtual PartialFunction* clone() const = 0;
    virtual ~PartialFunction() = default;
};