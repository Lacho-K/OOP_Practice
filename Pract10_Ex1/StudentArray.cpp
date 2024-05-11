#include "StudentArray.h"
#include <iostream>

void StudentArray::free()
{
	delete[] students;
	count = 0;
	capacity = 0;
}

void StudentArray::copyfrom(const StudentArray& other)
{
	for (size_t i = 0; i < other.size(); i++)
	{
		pushBack(other.at(i));
	}
}

void StudentArray::moveFrom(StudentArray&& other)
{
	for (size_t i = 0; i < other.size(); i++)
	{
		pushBack(std::move(other.at(i)));
	}
}

void StudentArray::resize()
{
	Student* newArr = new Student[capacity * 2];
	for (size_t i = 0; i < count; i++)
	{
		newArr[i] = students[i];
	}
	delete[] students;
	students = newArr;
}

StudentArray::StudentArray(): count(0), capacity(8)
{
	students = new Student[capacity];
	for (size_t i = 0; i < capacity; i++)
	{
		students[i] = Student();
	}
}

StudentArray::StudentArray(const StudentArray& other)
{
	copyfrom(other);
}

StudentArray::StudentArray(StudentArray&& other) noexcept
{
	moveFrom(std::move(other));
}

StudentArray& StudentArray::operator=(const StudentArray& other)
{
	if (this != &other)
	{
		free();
		copyfrom(other);
	}
	return *this;
}

StudentArray& StudentArray::operator=(StudentArray&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void StudentArray::pushBack(const Student& student)
{
	if (count == capacity)
		resize();

	students[count++] = student;
}

void StudentArray::pushBack(Student&& student)
{
	if (count == capacity)
		resize();

	students[count++] = std::move(student);
}

void StudentArray::pushFront(const Student& student)
{
	if (count == capacity)
		resize();

	for (size_t i = 0; i < count; i++)
	{
		students[count - i] = students[count - (i + 1)];
	}

	students[0] = student;

	count++;
}

void StudentArray::pushFront(Student&& student)
{
	if (count == capacity)
		resize();

	for (size_t i = 0; i < count; i++)
	{
		students[count - i] = students[count - (i + 1)];
	}

	students[0] = student;

	count++;
}

const Student& StudentArray::getBack() const
{
	return students[count - 1];
}

const Student& StudentArray::getFront() const
{
	return students[0];
}

size_t StudentArray::size() const
{
	return count;
}

Student& StudentArray::at(unsigned index) const
{
	if (index < 0 || index > count - 1)
		throw std::exception("Index out of range!");
		

	return students[index];
}

StudentArray::~StudentArray()
{
	free();
}
