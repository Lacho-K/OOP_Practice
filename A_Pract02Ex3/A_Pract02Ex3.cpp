#include <iostream>
#include <fstream>

void reverseFile(const char* fileName)
{
    std::ifstream input(fileName);

    std::ofstream output("output.txt");

    input.seekg(-1,std::ios::end);

    while (input.tellg() != (std::streampos)std::ios::beg)
    {
        char current = input.peek();
        output << current;
        input.seekg(-1, std::ios::cur);
    }
}

void reverseFileLines(const char* fileName)
{
    std::ifstream input(fileName);

    std::ofstream output("output.txt");

    while (!input.eof())
    {
        char buff[1024];
        input.getline(buff, 1024);
        output << _strrev(buff) << std::endl;
    }
    
}

int main()
{
    std::cout << "Hello World!\n";
    reverseFileLines("test.txt");
}
