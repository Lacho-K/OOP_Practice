#include <iostream>
#include "PartialFunctionByCriterion.hpp"
#include "MaximumPartialFunction.hpp"
#include "MinimumPartialFunction.hpp"

FuncResult func(int32_t x)
{
    return { x > 0 , 1/x };
}
FuncResult func2(int32_t x)
{
    return { x > 0 , x*x };
}
FuncResult func3(int32_t x)
{
    return { 1 , x*2 };
}


int main()
{
    std::cout << "Hello World!\n";
    PartialFunctionByCriterion<FuncResult(*)(int32_t)> name(func);
    PartialFunctionByCriterion<FuncResult(*)(int32_t)> name2(func2);
    PartialFunctionByCriterion<FuncResult(*)(int32_t)> name3(func3);

    PartialFunction** funcss = new PartialFunction * [3];
    funcss[0] = &name;
    funcss[1] = &name2;
    funcss[2] = &name3;

    MaximumPartialFunction max(funcss, 3);
    MinimumPartialFunction min(funcss, 3);

    std::cout << max(5).result;
    std::cout << std::endl;
    std::cout << min(5).result;
}