#include <iostream>
#include <fstream>

struct Product
{
    char description[32];
    int partNum;
    double cost;

    void printProduct(std::ostream& out)
    {
        out << this->description << " " << this->partNum << " " << this->cost << std::endl;
    }
};

void init(Product* prod, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        prod[i].cost = 0;
        strcpy_s(prod[i].description, "");
        prod[i].partNum = 0;
    }
}

void print(Product* prod, size_t length, std::ostream& out)
{
    for (size_t i = 0; i < length; i++)
    {
        prod[i].printProduct(out);
    }
}

int getCountOfProducts(std::ifstream& input)
{
    return input.get() - '0';
}

void readProducts(Product* products, size_t length, std::ifstream& input)
{
    input.get();
    for (size_t i = 0; i < length; i++)
    {
        input.getline(products[i].description, 32);
        input >> products[i].cost;
        input >> products[i].partNum;
    }
}


int main()
{
    std::ifstream input("test.txt");
    int prodCount = getCountOfProducts(input);
    //std::cin >> prodCount;
    std::cout << prodCount << std::endl;
    std::ofstream myfile("test.txt");/*
    myfile.open("test.txt");*/
    myfile << prodCount << std::endl;
    Product* products = new Product[prodCount];
    init(products, prodCount);

    /*strcpy_s(products[0].description, "screw driver");
    products[0].cost = 12;
    products[0].partNum = 234;
    strcpy_s(products[1].description, "hammer");
    products[1].cost = 43;
    products[1].partNum = 224;*/

    readProducts(products, prodCount, input);
    print(products, prodCount, std::cout);

    delete[] products;
}
