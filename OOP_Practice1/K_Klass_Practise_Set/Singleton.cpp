#include "Singleton.h"

Singleton::Singleton(int elem)
{
    element = elem;
}

bool Singleton::member(int x) const
{
    return x == element;
}
