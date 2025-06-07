#include <iostream>
#include <fstream>
#include "AlternateDataSource.hpp"
#include "PrimeFunc.hpp"
#include "FibonacciFunc.hpp"
#include "RandomFunc.hpp"
#include "GeneratorDataSource.hpp"
#include "RandomStringGenerator.hpp"

int main()
{
    DataSource<unsigned>** sources = new DataSource<unsigned>*[3];

    sources[0] = new GeneratorDataSource<unsigned>(new PrimeFunc());
    sources[1] = new GeneratorDataSource<unsigned>(new FibonacciFunc(25));
    sources[2] = new GeneratorDataSource<unsigned>(new RandomFunc());

    AlternateDataSource<unsigned> ads(sources, 3);

    std::ofstream ofs1("adsOut.dat", std::ios::binary);

    unsigned* data = ads.getMultiple(1000);
    ofs1.write((const char*)data, sizeof(unsigned) * 1000);
    delete[] data;

    RandomStringGenerator gen;

    std::ofstream ofs2("stringGenerator.dat", std::ios::binary);

    for (int i = 0; i < 50; i++)
    {
        std::string str = gen.next();
        ofs2.write(str.c_str(), 10);
    }

    ofs2.close();
}
