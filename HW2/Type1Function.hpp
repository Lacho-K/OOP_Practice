#include "PartialFunction.h"

class Type1Function : public PartialFunction
{
private:
    int args[MAX_POINTS];
    int count = 0;

public:

    Type1Function(uint16_t n, int* a)
    {
        if (n > MAX_POINTS)
            throw std::exception("count must be less than 32");

        count = n;
        for (int i = 0; i < n; i++) {
            args[i] = a[i];
        }
    }

    bool isDefinedAt(int x) const override
    {
        for (int i = 0; i < count; i++)
        {
            if (args[i] == x) return false;
        }
        return true;
    }

    FuncResult operator()(int x) const override
    {
        if (!isDefinedAt(x))
        {
            std::cout << "Function is not defined at " << x;
            throw std::exception(".");
        }

        return { 1, x };
    }

    PartialFunction* clone() const override
    {
        return new Type1Function(*this);
    }
};