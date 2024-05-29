#include <iostream>
#include "PartialFunctionByCriterion .hpp"

int func(int x)
{
    return x;
}


int main()
{
    std::cout << "Hello World!\n";
    PartialFunctionByCriterion<int(*)(int)> name (func);
    std::cout << name.isDefinedAt(0);
}