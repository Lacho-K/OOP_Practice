#include "Stock.h"
#include <iostream>
#pragma warning (disable: 4996)

void Stock::copy(const Stock& other)
{
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
    std::strcpy(this->abbreviation, abbreviation);
}

void Stock::setName(const char* name)
{
    std::strcpy(this->name, name);
}

void Stock::setPrices(unsigned* prices)
{
    for (size_t i = 0; i < 12; i++)
    {
        this->prices[i] = prices[i];
    }
}

Stock::Stock(const char* abbreviation, const char* name, unsigned* prices)
{
    setAbbreviation(abbreviation);
    setName(name);
    setPrices(prices);
}

Stock::Stock(const Stock& other)
{
}

//Stock& Stock::operator=(const Stock& other)
//{
//    // // O: insert return statement here
//}
