#pragma once
#include "Student.h"


class StudentArray
{
	Student* students;
	unsigned count;
	unsigned capacity;
	
	void free();
	void copyfrom(const StudentArray& other);
	void moveFrom(StudentArray&& other);
	void resize();

public:

	StudentArray();
	StudentArray(const StudentArray& other);
	StudentArray(StudentArray&& other) noexcept;

	StudentArray& operator=(const StudentArray& other);
	StudentArray& operator=(StudentArray&& other) noexcept;

	void pushBack(const Student& student);
	void pushBack(Student&& student);
	
	void pushFront(const Student& student);
	void pushFront(Student&& student);

	const Student& getBack() const;
	const Student& getFront() const;

	size_t size() const;
	Student& at(unsigned index) const;


	~StudentArray();
};