#include <iostream>
#include "PartialFunction.h"

template <class Func>
class PartialFunctionByCriterion : public PartialFunction 
{
    Func _func;

public:
    PartialFunctionByCriterion(const Func& func) : _func(func) {}

    bool isDefinedAt(int x) const override 
    {
        FuncResult res = _func(x);
        return res.defined;
    }

    FuncResult operator()(int x) const override
    {
        bool isDefined = isDefinedAt(x);
        if (!isDefined)
            throw::std::exception("Function is not defined");

        FuncResult res;
        res.defined = isDefined;
        res.result = _func(x).result;
        return res;
    }

    virtual PartialFunction* clone() const override
    {
        return new PartialFunctionByCriterion<Func>(_func);
    }
};