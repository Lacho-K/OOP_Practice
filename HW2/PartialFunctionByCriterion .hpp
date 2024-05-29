#include <iostream>
#include "PartialFunction.h"

template <class Func>
class PartialFunctionByCriterion : public PartialFunction 
{
    Func _func;

public:
    PartialFunctionByCriterion(Func func) : _func(func) {}

    bool isDefinedAt(int x) const override 
    {
        int32_t result = _func(x);
        for (long i = INT32_MIN; i < INT32_MAX; i++)
        {
            if (result == _func(i) && i != x)
                return 0;
        }

        return 1;
    }

    FuncResult operator()(int x) const override
    {
        bool isDefined = isDefinedAt(x);
        if (!isDefined)
            throw::std::exception("Function is not defined");

        FuncResult res;
        res.defined = isDefinedAt(x);
        res.result = _func(x);
        return res;
    }
};