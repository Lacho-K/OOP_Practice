#include "Student.h"
#include <iostream>
#pragma warning (disable : 4996)


void Student::free()
{
	delete[] _name;
	delete[] _speciality;

	_name = nullptr;
	_speciality = nullptr;
	_fn = 0;
}

void Student::copyFrom(const Student& other)
{
	_name = new char[strlen(other._name) + 1];
	_speciality = new char[strlen(other._speciality) + 1];

	strcpy(_name, other._name);
	strcpy(_speciality, other._speciality);
	_fn = other._fn;
}

void Student::moveFrom(Student&& other)
{
	_name = other._name;
	_speciality = other._speciality;
	_fn = other._fn;

	other._name = nullptr;
	other._speciality = nullptr;
	other._fn = 0;
}

Student::Student(const char* name, const char* speciality, unsigned fn)
{
	if (!name || _name == name || !isValidName(name))
		return;

	setName(name);
	setSpeciality(speciality);
	setFn(fn);
}

Student::Student(const Student& other)
{
	copyFrom(other);
}

Student::Student(Student&& other) noexcept
{
	moveFrom(std::move(other));
}

Student& Student::operator=(const Student& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Student& Student::operator=(Student&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Student::~Student()
{
	free();
}

void Student::setFn(unsigned fn)
{
	_fn = fn;
}

bool Student::isValidName(const char* name)
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

void Student::setName(const char* name)
{
	if (!name || _name == name || !isValidName(name))
		return;

	delete[] _name;
	_name = new char[strlen(name) + 1];
	strcpy(_name, name);
}

void Student::setSpeciality(const char* speciality)
{
	if (!speciality || _speciality == speciality)
		return;

	delete[] _speciality;
	_speciality = new char[strlen(speciality) + 1];
	strcpy(_speciality, speciality);
}

const char* Student::getName() const
{
	return _name;
}

const char* Student::getSpeciality() const
{
	return _speciality;
}

unsigned Student::getFn() const
{
	return _fn;
}