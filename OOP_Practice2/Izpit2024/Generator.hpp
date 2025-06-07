#pragma once

template<typename T>
class Generator
{
public:
    virtual const T& next() = 0;
    virtual const T& operator()() const = 0;
    virtual bool canContinue() const = 0;
    virtual bool reset() = 0;
    virtual Generator<T>* clone() const = 0;
    virtual ~Generator() = default;
};