#include "Backpack.h"
#include <iostream>
#include <fstream>

void Backpack::swap(Backpack& other)
{
	books = other.books;
	cap = other.cap;
	count = other.count;
	maxWeight = maxWeight;
	currentWeight = other.currentWeight;

	other.books = nullptr;
}

void Backpack::copyDynamic(const Backpack& other)
{
	if (other.count > other.cap || other.currentWeight > other.maxWeight)
		throw std::logic_error("invalid object");

	books = new Book[other.cap];

	for (int i = 0; i < other.count; i++)
	{
		books[i] = other.books[i];
	}
}

void Backpack::free()
{
	delete[] books;
	books = nullptr;
}

void Backpack::setCountAndCap(const unsigned count, const unsigned cap)
{
	if (count < 0 || cap < 0)
		throw std::invalid_argument("count and cap must be > 0");

	if (count > cap)
		throw std::logic_error("count must be < cap");

	this->count = count;
	this->cap = cap;
}

void Backpack::setWeightAndMaxWeight(const float weight, const float maxWeight)
{
	if (weight < 0 || maxWeight < 0)
		throw std::invalid_argument("weight and maxWeight must be > 0");

	if (weight > maxWeight)
		throw std::logic_error("weight must be < maxWeight");

	this->currentWeight = weight;
	this->maxWeight = maxWeight;
}

void Backpack::resize()
{
	if (cap == 0)
	{
		++cap;
		books = new Book[cap];
		return;
	}

	cap *= 2;

	Book* newBooks = new Book[cap];
	for (int i = 0; i < count; i++)
	{
		newBooks[i] = books[i];
	}

	delete[] books;
	books = newBooks;
}

Backpack::Backpack(const Backpack& other)
{
	try
	{
		copyDynamic(other);
		setCountAndCap(other.count, other.cap);
		setWeightAndMaxWeight(other.currentWeight, other.maxWeight);
	}
	catch (...)
	{
		free();
		throw;
	}
}

Backpack::Backpack(const float maxWeight)
{
	setWeightAndMaxWeight(0, maxWeight);
}

Backpack& Backpack::operator=(const Backpack& other)
{
	if (this != &other)
	{
		Backpack copy(other);
		swap(copy);
	}

	return *this;
}

Backpack::~Backpack()
{
	free();
}

void Backpack::add(const Book& book)
{
	if (currentWeight + book.getWeight() > maxWeight)
		throw std::logic_error("book would break the maxWeight limit");

	if (count == cap)
		resize();

	books[count++] = book;
	currentWeight += book.getWeight();
}

void Backpack::remove(const ISBN& isbn)
{
	for (int i = 0; i < count; i++)
	{
		if (books[i].getISBN() == isbn)
		{
			currentWeight -= books[i].getWeight();
			std::swap(books[i], books[count - 1]);
			count--;
			return;
		}
	}

	throw std::runtime_error("Book not found");
}

void Backpack::serialize(const char* fileName) const
{
	if (!fileName || fileName[0] == '\0')
		throw std::invalid_argument("fileName empty or nullptr");

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
		throw std::runtime_error("ofs not open");

	ofs.write((const char*)&currentWeight, sizeof(currentWeight));
	ofs.write((const char*)&maxWeight, sizeof(maxWeight));
	ofs.write((const char*)&cap, sizeof(cap));
	ofs.write((const char*)&count, sizeof(count));

	for (int i = 0; i < count; i++)
	{
		books[i].serialize(ofs);
	}
}

void Backpack::deserialize(const char* fileName)
{
	if (!fileName || fileName[0] == '\0')
		throw std::invalid_argument("fileName empty or nullptr");

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
		throw std::runtime_error("ofs not open");

	free();

	ifs.read((char*)&currentWeight, sizeof(currentWeight));
	ifs.read((char*)&maxWeight, sizeof(maxWeight));
	ifs.read((char*)&cap, sizeof(cap));
	ifs.read((char*)&count, sizeof(count));
	books = new Book[cap];
	for (int i = 0; i < count; i++)
	{
		books[i].deserialize(ifs);
	}
}


