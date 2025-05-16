#include "Issue.h"
#include <stdexcept>
#pragma warning(disable:4996)

Issue::Issue(char* title, double price, unsigned yearlyEditions)
{
	setTitle(title);
	setPrice(price);
	setEditions(yearlyEditions);
}

Issue::Issue(const Issue& other)
{
	try
	{
		setTitle(other.title);
		setPrice(other.price);
		setEditions(other.yearlyEditions);
	}
	catch (...)
	{
		free();
		throw;
	}
}

Issue::Issue(Issue&& other):title(other.title), price(other.price), yearlyEditions(other.yearlyEditions)
{
	other.title = nullptr;
	other.price = other.yearlyEditions = 0;
}

Issue& Issue::operator=(const Issue& other)
{
	if (this != &other)
	{
		try
		{
			setTitle(other.title);
			setPrice(other.price);
			setEditions(other.yearlyEditions);
		}
		catch (...)
		{
			free();
			throw;
		}
	}

	return *this;
}

Issue& Issue::operator=(Issue&& other)
{
	if (this != &other)
	{
		swap(other);
	}
	return *this;
}

Issue::~Issue()
{
	free();
}

const char* Issue::getTitle() const
{
	return title;
}

void Issue::setTitle(const char* title)
{
	if (!title)
		throw std::invalid_argument("Title cannot be null");

	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
}

double Issue::getPrice() const
{
	return price;
}

void Issue::setPrice(double newPrice)
{
	if (newPrice < 0.0)
		throw std::invalid_argument("Price cannot be < 0");

	price = newPrice;
}

unsigned Issue::getEditions() const
{
	return yearlyEditions;
}

void Issue::setEditions(unsigned editions)
{
	if (editions < 0)
		throw std::invalid_argument("Editions cannot be < 0");

	yearlyEditions = editions;
}

void Issue::free()
{
	delete[] title;
	title = nullptr;
}

void Issue::swap(Issue& other)
{
	std::swap(title, other.title);
	std::swap(price, other.price);
	std::swap(yearlyEditions, other.yearlyEditions);
}
