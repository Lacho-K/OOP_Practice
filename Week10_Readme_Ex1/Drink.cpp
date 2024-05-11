#include "Drink.h"
#include <exception>
#include <iostream>
#pragma warning (disable : 4996)

Drink::Drink(const char* name, int ml)
{
	setName(name);
	setMl(ml);
}

Drink::Drink(const Drink& other)
{
	copyFrom(other);
}

Drink::Drink(Drink&& other) noexcept
{
	moveFrom(std::move(other));
}

Drink& Drink::operator=(const Drink& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Drink& Drink::operator=(Drink&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* Drink::getName() const
{
	return _name;
}

const int Drink::getMl() const
{
	return _ml;
}

void Drink::setName(const char* name)
{
	if (!name || _name == name || !isValidName(name))
		throw std::exception("Invalid name!");

	delete[] _name;
	_name = new char[strlen(name) + 1];
	strcpy(_name, name);
}

void Drink::setMl(int ml)
{
	if(ml < 0)
		throw std::exception("Invalid mililiters!");

	_ml = ml;
}

Drink::~Drink()
{
	free();
}

void Drink::copyFrom(const Drink& other)
{
	if (!other._name)
		return;

	_name = new char[strlen(other._name) + 1];

	strcpy(_name, other._name);
	_ml = other._ml;
}

void Drink::moveFrom(Drink&& other)
{
	_name = other._name;
	_ml = other._ml;

	other._name = nullptr;
	other._ml = 0;
}

void Drink::free()
{
	delete[] _name;

	_name = nullptr;
	_ml = 0;
}

bool Drink::isValidName(const char* name)
{
	if (*name < 'A' || *name > 'Z')
		return false;

	name++;

	while (*name)
	{
		if (*name < 'a' || *name > 'z')
			return false;

		name++;
	}

	return true;
}
