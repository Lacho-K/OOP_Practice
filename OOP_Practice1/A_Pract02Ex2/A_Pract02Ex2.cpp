#include <iostream>
#include <fstream>

void copyFileContent(std::ifstream& input, std::ofstream& output)
{
    if (!input.is_open() || !output.is_open())
    {
        return;
    }

    while (!input.eof())
    {
        char buff[1024];
        input.getline(buff, 1024, '|');
        output << buff;
    }
}
// doesn't work
void concatFiles(char fileNames[3][10], size_t length)
{
    std::ofstream output("output.txt");
    if (!output.is_open())
    {
        std::cerr << "Error opening output.txt" << std::endl;
        return;
    }

    for (size_t i = 0; i < length; i++)
    {
        char* currFileName = fileNames[i];
        std::ifstream currInput(currFileName);
        if (!currInput.is_open())
        {
            std::cerr << "Error opening file: " << currFileName << std::endl;
            continue; // Skip to the next file
        }

        copyFileContent(currInput, output);
        currInput.close();
        fileNames++;
    }
}

int main()
{
    const int numFiles = 3; // Adjust this based on the number of files
    char fileNames[][10] = {
    "file1.txt",
    "file2.txt",
    "file3.txt"
    // Add more filenames as needed
    };


    concatFiles(fileNames, numFiles);

}
