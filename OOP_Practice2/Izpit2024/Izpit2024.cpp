#include <iostream>
#include "AlternateDataSource.hpp"
#include "PrimeFunc.hpp"
#include "FibonacciFunc.hpp"
#include "RandomFunc.hpp"
#include "GeneratorDataSource.hpp"

int main()
{
    DataSource<unsigned>** sources = new DataSource<unsigned>*[3];

    sources[0] = new GeneratorDataSource<unsigned>(new PrimeFunc());
    sources[1] = new GeneratorDataSource<unsigned>(new FibonacciFunc());
    sources[2] = new GeneratorDataSource<unsigned>(new RandomFunc());

    // TODO: Fix no allocation
    AlternateDataSource<unsigned> ads(sources, 3);
}
