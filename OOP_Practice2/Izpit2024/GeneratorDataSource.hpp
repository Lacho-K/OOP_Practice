#pragma once
#include "DataSource.hpp"
#include "Generator.hpp"

template<typename T>
class GeneratorDataSource : public DataSource<T>
{
public:
    explicit GeneratorDataSource(Generator<T>* gen) : gen(gen->clone()) {}

    GeneratorDataSource(const GeneratorDataSource& other)
    {
        gen = other.gen->clone();
    }

    GeneratorDataSource& operator=(const GeneratorDataSource& other)
    {
        if (this != &other)
        {
            delete gen;
            gen = other.gen->clone();
        }
        return *this;
    }

    ~GeneratorDataSource()
    {
        delete gen;
    }

    const T& next() override
    {
        return gen->next();
    }

    const T& operator()() const override
    {
        return (*gen)();
    }

    bool canContinue() const override
    {
        return gen->canContinue();
    }

    bool reset() override
    {
        return gen->reset();
    }

    DataSource<T>* clone() const override
    {
        return new GeneratorDataSource<T>(*this);
    }

private:
    Generator<T>* gen;
};
