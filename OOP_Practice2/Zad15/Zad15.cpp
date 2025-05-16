#pragma once
#include <iostream>
#include "IntSet.h"
#include "ArraySet.h"
#include "IntRange.h"

bool mon(IntSet* sets[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (!(*sets[i] < *sets[i + 1])) return false;
    }
    return true;
}

int main()
{
    IntSet* sets[3];

    // Първо множество: ArraySet {1, 2}
    ArraySet* a1 = new ArraySet(3);
    a1->insert(1);
    a1->insert(2);

    // Второ множество: IntRange [1, 3] => {1, 2, 3}
    IntRange* r1 = new IntRange(1, 3);

    // Трето множество: ArraySet {1, 2, 3, 4}
    ArraySet* a2 = new ArraySet(5);
    a2->insert(1);
    a2->insert(2);
    a2->insert(3);
    a2->insert(4);

    sets[0] = a1;
    sets[1] = r1;
    sets[2] = a2;

    bool result = mon(sets, 3);

    std::cout << "Is strictly increasing: " << (result ? "YES" : "NO") << std::endl;

    delete a1;
    delete r1;
    delete a2;
}