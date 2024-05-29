#include "SetUnion.h"

SetUnion::SetUnion()
{
    sets[0] = nullptr;
    sets[1] = nullptr;
}

SetUnion::SetUnion(Set* set1, Set* set2)
{
    sets[0] = set1;
    sets[1] = set2;
}

bool SetUnion::member(int x) const
{
    return sets[0]->member(x) || sets[1]->member(x);
}
