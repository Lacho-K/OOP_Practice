// RandomStringGenerator.hpp
#pragma once
#include "Generator.hpp"
#include <cstdlib>
#include <ctime>
#include <string>

class RandomStringGenerator : public Generator<std::string>
{
public:
    RandomStringGenerator()
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        generate();
    }

    const std::string& next() override
    {
        generate();
        return current;
    }

    const std::string& operator()() const override
    {
        return current;
    }

    bool canContinue() const override
    {
        return true;
    }

    bool reset() override
    {
        return true;
    }

    Generator<std::string>* clone() const override
    {
        return new RandomStringGenerator(*this);
    }

private:
    std::string current;

    void generate()
    {
        current.resize(10);
        for (int i = 0; i < 10; i++)
        {
            current[i] = 'a' + std::rand() % 26;
        }
    }
};
