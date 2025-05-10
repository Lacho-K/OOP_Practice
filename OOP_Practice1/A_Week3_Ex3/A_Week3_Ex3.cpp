#include <iostream>
#include <fstream>

void replaceSymbolsInFile(const char* fileName, const char targetSymbol, const char replacementSymbol)
{
    std::ifstream input(fileName);
    std::ofstream output(fileName);

    if (!input.is_open() || !output.is_open())
        return;

    while (!input.eof())
    {
        if (input.peek() == targetSymbol)
        {
            output << replacementSymbol;
            input.get();
        }
        else 
        {
            output << (char)input.get();
            if (input.peek() == std::ios::end)
                return;
        }
    }
}

void replaceInFile(char ch, char ch2, std::fstream& file)
{
    while (!file.eof())
    {
        char currentSybmol = file.get();

        if (currentSybmol != ch)
            continue;

        file.seekp(-1, std::ios::cur);
        file.put(ch2);
        file.flush();
    }
}

int main()
{
    std::fstream file("test.txt", std::ios::in | std::ios::out);
    std::cout << "Hello World!\n";
    //replaceSymbolsInFile("test.txt", '@', '#');
    replaceInFile('@', 'X', file);
}