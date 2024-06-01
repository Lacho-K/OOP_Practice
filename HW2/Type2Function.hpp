#include "PartialFunction.h"

class Type2Function : public PartialFunction
{
private:
    int args[MAX_POINTS];
    int count = 0;

public:

    Type2Function(uint16_t n, int* a)
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
        return true;
    }

    FuncResult operator()(int x) const override
    {
        for (int i = 0; i < count; i++)
        {
            if (args[i] == x) return { 1, 1 };
        }

        return { 1, 0 };
    }

    PartialFunction* clone() const override
    {
        return new Type2Function(*this);
    }
};