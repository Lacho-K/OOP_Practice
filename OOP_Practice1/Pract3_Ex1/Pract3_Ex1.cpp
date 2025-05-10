#include <iostream>
#include <fstream>

constexpr size_t MAX_LINE_SIZE = 1024;
constexpr size_t MAX_WORD_SIZE = 128;


int getLinesCount(std::ifstream& stream)
{
	int count = 0;
	while (!stream.eof())
	{
		std::string buffer;
		stream.getline(stream, buffer);
		count++;
	}

	stream.seekg(0, std::ios::beg);
	stream.clear();
}

int main()
{
    std::cout << "Hello World!\n";
}
