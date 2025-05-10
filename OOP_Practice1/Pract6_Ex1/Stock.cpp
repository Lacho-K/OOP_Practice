#include "Stock.h"
#include <iostream>
#pragma warning (disable: 4996)

void Stock::copy(const Stock& other)
{
    setAbbreviation(other.getAbbreviation());
    setName(other.getName());
    setPrices(other.getPrices());
}

const char* Stock::getAbbreviation() const
{
    return abbreviation;
}

const char* Stock::getName() const
{
    return name;
}

const unsigned* Stock::getPrices() const
{
    return prices;
}

void Stock::setAbbreviation(const char* abbreviation)
{
    if(abbreviation && std::strlen(abbreviation) <= 6)
    std::strcpy(this->abbreviation, abbreviation);
}

void Stock::setName(const char* name)
{
    if (abbreviation && std::strlen(name) <= 21)
    std::strcpy(this->name, name);
}

void Stock::setPrices(const unsigned* prices)
{
    if (!prices)
        return;

    for (size_t i = 0; i < 12; i++)
    {
        this->prices[i] = prices[i];
    }
}

bool Stock::isProfitable()
{
    unsigned increasingCount = 0;
    unsigned decreasingCount = 0;

    for (size_t i = 0; i < 11; i++)
    {
        if (this->prices[i] < this->prices[i + 1])
            increasingCount++;
        else if (this->prices[i] > this->prices[i + 1])
            decreasingCount++;
    }

    return (increasingCount > decreasingCount) && (this->prices[11] > (this->prices[0] + (this->prices[0] * 0.10)));
}

Stock::Stock()
{
    this->setAbbreviation("");
    this->setName("");
    unsigned defaultPrices[] = { 2,3,4,5 };
    this->setPrices(defaultPrices);
}

Stock::Stock(const char* abbreviation, const char* name, unsigned* prices)
{
    setAbbreviation(abbreviation);
    setName(name);
    setPrices(prices);
}

Stock::Stock(const Stock& other)
{
    copy(other);
}

Stock& Stock::operator=(const Stock& other)
{
    copy(other);
    return *this;
}
