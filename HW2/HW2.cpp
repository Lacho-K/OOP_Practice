#include <iostream>
#include <fstream>
#include "PartialFunctionByCriterion.hpp"
#include "Type0Function.hpp"
#include "Type1Function.hpp"
#include "Type2Function.hpp"
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

PartialFunction* functionFactory(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file." << std::endl;
        return nullptr;
    }

    int16_t N, T;
    file >> N >> T;

    int a[MAX_POINTS], r[MAX_POINTS];

    switch (T)
    {
        case 0:
            for (int i = 0; i < N; ++i) {
                file >> a[i];
            }
            for (int i = 0; i < N; ++i) {
                file >> r[i];
            }
            return new Type0Function(N, a, r);
            break;
        case 1:
            for (int i = 0; i < N; ++i) {
                file >> a[i];
            }
            return new Type1Function(N, a);
            break;
        case 2:
            for (int i = 0; i < N; ++i) {
                file >> a[i];
            }
            return new Type2Function(N, a);
            break;

    default:
        std::cerr << "Function type not implemented." << std::endl;
    }

    return nullptr;
}


int main()
{
    PartialFunctionByCriterion<FuncResult(*)(int32_t)> name(func);
    PartialFunctionByCriterion<FuncResult(*)(int32_t)> name2(func2);
    PartialFunctionByCriterion<FuncResult(*)(int32_t)> name3(func3);

    PartialFunction** funcss = new PartialFunction * [6];
    funcss[0] = &name;
    funcss[1] = &name2;
    funcss[2] = &name3;
    funcss[3] = functionFactory("first.dat");
    funcss[4] = functionFactory("second.dat");
    funcss[5] = functionFactory("third.dat");

    MaximumPartialFunction max(funcss, 3);
    MinimumPartialFunction min(funcss, 3);

    std::cout << max(5).result;
    std::cout << std::endl;
    std::cout << min(5).result;
    std::cout << std::endl;
    std::cout << funcss[3]->operator()(3).result;
    std::cout << std::endl;
    std::cout << funcss[4]->operator()(10).result;
    std::cout << std::endl;
    std::cout << funcss[5]->operator()(7).result;
}