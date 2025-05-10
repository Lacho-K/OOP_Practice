#include "EmptySet.h"

bool EmtySet::member(int x) const
{
    return false;
}

Set* EmtySet::copy()
{
    return new EmtySet(*this);
}

Set* EmtySet::copy(const Set* obj)
{
    return new EmtySet(*this);
}
