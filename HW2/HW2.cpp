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

static void freeFuncNames(char** names, int16_t N)
{
    for (int i = 0; i < N; i++)
    {
        delete names[i];
    }
    delete[] names;
}

PartialFunction* functionFactory(const char* filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::exception("Cannot open file.");
        return nullptr;
    }

    int16_t N, T;
    file >> N >> T;

    int a[MAX_POINTS], r[MAX_POINTS];
    char** funcNames = nullptr;
    PartialFunction** funcs = nullptr;

    switch (T)
    {
    case 0:
        for (int i = 0; i < N; i++) {
            file >> a[i];
        }
        for (int i = 0; i < N; i++) {
            file >> r[i];
        }
        file.close();
        return new Type0Function(N, a, r);
        break;
    case 1:
        for (int i = 0; i < N; i++) {
            file >> a[i];
        }
        file.close();
        return new Type1Function(N, a);
        break;
    case 2:
        for (int i = 0; i < N; i++) {
            file >> a[i];
        }
        file.close();
        return new Type2Function(N, a);
        break;
    case 3:
        funcNames = new char* [N];
        funcs = new PartialFunction* [N];
        for (int i = 0; i < N; i++)
        {
            funcNames[i] = new char[1024];
            file >> funcNames[i];
            funcs[i] = functionFactory(funcNames[i]);
            PartialFunction* currentFunc = funcs[i]->clone();
            //std::cout << (*funcs[i])(i).result;
        }

        freeFuncNames(funcNames, N);
        file.close();
        return new MaximumPartialFunction(funcs, N);
        break;
    case 4:
        funcNames = new char* [N];
        funcs = new PartialFunction* [N];
        for (int i = 0; i < N; i++)
        {
            funcNames[i] = new char[1024];
            file >> funcNames[i];
            funcs[i] = functionFactory(funcNames[i]);
            PartialFunction* currentFunc = funcs[i]->clone();
        }

        freeFuncNames(funcNames, N);
        file.close();
        return new MinimumPartialFunction(funcs, N);
        break;
    default:
        throw std::exception("Invalid command.");
    }
    return nullptr;
}

static void printFuncInInterval(int a, int b,const PartialFunction* func)
{
    for (int i = a; i <= b; i++)
    {
        std::cout << "f(" << i << ") = " << (*func)(i).result << std::endl;
    }
}


int main()
{
    try
    {
        int a, b;
        std::cin >> a >> b;
        PartialFunctionByCriterion<FuncResult(*)(int32_t)> name(func);
        PartialFunctionByCriterion<FuncResult(*)(int32_t)> name2(func2);
        PartialFunctionByCriterion<FuncResult(*)(int32_t)> name3(func3);

        PartialFunction** funcss = new PartialFunction * [8];
        funcss[0] = &name;
        funcss[1] = &name2;
        funcss[2] = &name3;
        //funcss[3] = functionFactory("first.dat");
        //funcss[4] = functionFactory("second.dat");
        //funcss[5] = functionFactory("third.dat");
        funcss[6] = functionFactory("func.dat");
        printFuncInInterval(a, b, funcss[6]);
        //funcss[7] = functionFactory("func1.dat");

      //   MaximumPartialFunction max(funcss, 3);
      //  MinimumPartialFunction min(funcss, 3);

        //std::cout << max(5).result;
        //std::cout << std::endl;
        //std::cout << min(5).result;
        //std::cout << std::endl;
        //std::cout << funcss[3]->operator()(3).result;
        //std::cout << std::endl;
        //std::cout << funcss[4]->operator()(10).result;
        //std::cout << std::endl;
        //std::cout << funcss[5]->operator()(7).result;
        //std::cout << std::endl;
        //std::cout << funcss[6]->operator()(7).result;
        //std::cout << std::endl;
        //std::cout << funcss[7]->operator()(7).result;
    }
    catch (const std::exception& e)
    {
        std::cout << (e.what());
    }
}