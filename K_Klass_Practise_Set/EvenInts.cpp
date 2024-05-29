#include "EvenInts.h"

bool EvenInts::member(int x) const
{
    return x % 2 == 0;
}

Set* EvenInts::copy()
{
    return new EvenInts(*this);
}
