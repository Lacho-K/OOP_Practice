#include <iostream>
#include <fstream>

void writeToFile(const char* fileName)
{
    unsigned count;
    std::cin >> count;

    int* arayy = new int[count];

    for (int i = 0; i < count; i++)
    {
        std::cin >> arayy[i];
    }

    std::ofstream ofs(fileName, std::ios::binary);

    ofs.write((const char*)(&count), sizeof(count));
    ofs.write((const char*)(arayy), sizeof(arayy));

    ofs.close();
    //ofs.flush();

    delete[] arayy;
}

//TASK 2
//read array from binary file

int* readFromFile(const char* fileName)
{
    std::ifstream ifs(fileName, std::ios::binary);

    if (!ifs.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return nullptr;
    }

    unsigned count;

    ifs.read((char*)(&count), sizeof(count));

    int* arayy = new int[count];

    ifs.read((char*)arayy, sizeof(arayy));

    return arayy;
}


int main()
{
    //std::cout << "Hello World!\n";
    writeToFile("koro.bin");

    int* arrFromFile = readFromFile("koro.bin");

    for (size_t i = 0; i < 5; i++)
    {
        std::cout << arrFromFile[i] << " ";
    }

    delete[] arrFromFile;
}
