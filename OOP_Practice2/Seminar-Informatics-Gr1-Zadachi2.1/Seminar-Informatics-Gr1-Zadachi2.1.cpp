#include <iostream>
#include <fstream>

bool nonWhitespace(char c)
{
    return c > '32' < '127';
}

unsigned countCharacters(std::ifstream& ifs, bool(*pred)(char c))
{
    unsigned counter = 0;
    while (!ifs.eof())
    {
        if(pred(ifs.get()))
            counter++;
    }

    return counter;
}

unsigned countWords(std::ifstream& ifs)
{
    unsigned counter = 0;
    char buff[1024];
    while (!ifs.eof())
    {
        counter++;
        ifs >> buff;
    }

    return counter;
}

unsigned countLines(std::ifstream& ifs, bool nonEmpty)
{
    unsigned counter = 0;
    bool hasChars = false;
    while (!ifs.eof())
    {
        char c = ifs.get();
        if (c != '\n')
        {
            hasChars = true;
        }
        if(hasChars || !nonEmpty)
        {
            counter++;
            hasChars = false;
        }
    }

    return counter;
}



int main()
{
    char arg;
    std::cin >> arg;

    std::ifstream ifs("test.txt");

    if (!ifs.is_open())
        return -1;

    std::cout << countLines(ifs, 0);
}