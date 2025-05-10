#pragma once
#include "ISBN.h"
#include <fstream>

class Book
{
	char* bookName = nullptr;
	char* authorName = nullptr;
	float weight = 0;
	ISBN isbn;

	void copyDynamic(const Book& other);
	void swap(Book& other);
	void free();
	void validateStr(const char* str);
	void setWeight(const float weight);

public:

	Book() = default;
	Book(const Book& other);
	Book(const char* bookName, const char* authorName, const float weight, const ISBN& isbn);
	Book& operator=(const Book& other);
	~Book();

	const float getWeight() const;
	const ISBN& getISBN() const;
	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
};