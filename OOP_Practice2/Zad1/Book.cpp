#include "Book.h"
#include <iostream>
#pragma warning (disable:4996)

void Book::copyDynamic(const Book& other)
{
	validateStr(other.bookName);
	validateStr(other.authorName);

	// no nothrow because it wouldn't cause a leak
	bookName = new char[strlen(other.bookName) + 1];

	authorName = new (std::nothrow) char[strlen(other.authorName) + 1];

	if (!authorName)
		throw std::runtime_error("authorName not created");

	strcpy(bookName, other.bookName);
	strcpy(authorName, other.authorName);
}

void Book::swap(Book& other)
{
	authorName = other.authorName;
	bookName = other.bookName;
	weight = other.weight;
	isbn = other.isbn;

	other.authorName = nullptr;
	other.bookName = nullptr;
}

void Book::free()
{
	delete[] authorName;
	delete[] bookName;
	authorName = nullptr;
	bookName = nullptr;
}

void Book::validateStr(const char* str)
{
	if (!str || str[0] == '\0')
		throw std::invalid_argument("Invalid str");
}

void Book::setWeight(const float weight)
{
	if (weight < 0)
		throw std::invalid_argument("Weight cannot be < 0");

	this->weight = weight;
}

// strong exception safety
Book::Book(const Book& other) : isbn(other.isbn)
{
	try
	{
		setWeight(other.weight);
		copyDynamic(other);
	}
	catch (...)
	{
		free();
		throw;
	}
}

Book::Book(const char* bookName, const char* authorName, const float weight, const ISBN& isbn) : isbn(isbn)
{
	validateStr(bookName);
	validateStr(authorName);

	this->bookName = new char[strlen(bookName) + 1];

	this->authorName = new (std::nothrow) char[strlen(authorName) + 1];

	if (!authorName)
		throw std::runtime_error("authorName not created");

	strcpy(this->bookName, bookName);
	strcpy(this->authorName, authorName);
	setWeight(weight);
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		Book copy(other);
		swap(copy);
	}

	return *this;
}

Book::~Book()
{
	free();
}

const float Book::getWeight() const
{
	return weight;
}

const ISBN& Book::getISBN() const
{
	return isbn;
}

void Book::deserialize(std::ifstream& ifs)
{
	size_t len;

	ifs.read((char*)&len, sizeof(len));
	bookName = new char[len];
	ifs.read(bookName, len);

	ifs.read((char*)&len, sizeof(len));
	authorName = new char[len];
	ifs.read(authorName, len);

	ifs.read((char*)&weight, sizeof(weight));
	ifs.read((char*)&isbn, sizeof(ISBN));
}

void Book::serialize(std::ofstream& ofs) const
{
	size_t len = strlen(bookName) + 1;
	ofs.write((const char*)&len, sizeof(len));
	ofs.write(bookName, len);

	len = strlen(authorName) + 1;
	ofs.write((const char*)&len, sizeof(len));
	ofs.write(authorName, len);

	ofs.write((const char*)&weight, sizeof(weight));
	ofs.write((const char*)&isbn, sizeof(ISBN));
}

