#include "PartialFunction.h"

class Type0Function : public PartialFunction 
{
private:
    int args[MAX_POINTS];
    int results[MAX_POINTS];
    int count = 0;

public:

    Type0Function() = default;

    Type0Function(uint16_t n, int* a, int* r)
    {
        if (n > MAX_POINTS)
            throw std::exception("count must be less than 32");

        count = n;
        for (int i = 0; i < n; i++) {
            args[i] = a[i];
            results[i] = r[i];
        }
    }

    bool isDefinedAt(int x) const override 
    {
        for (int i = 0; i < count; i++) 
        {
            if (args[i] == x) return true;
        }
        return false;
    }

    FuncResult operator()(int x) const override 
    {
        if(!isDefinedAt(x))
            throw std::exception("Function is not defined at this point.");

        for (int i = 0; i < count; i++) 
        {
            if (args[i] == x) return {1, results[i]};
        }

        return {0, 0};
    }

    PartialFunction* clone() const override 
    {
        return new Type0Function(*this);
    }
};