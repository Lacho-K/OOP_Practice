#pragma once

class Student
{
	char* _name;
	char* _speciality;
	unsigned _fn;

	void copyFrom(const Student& other);
	void moveFrom(Student&& other);
	void free();
	bool isValidName(const char* name);

public:

	Student();
	Student(const Student& other);
	Student(const char* name, const char* speciality, unsigned fn);
	Student(Student&& other);

	Student& operator=(const Student& other);
	Student& operator=(Student&& other);

	const char* getName() const;
	const char* getSpeciality() const;
	unsigned getFn() const;

	void setName(const char* newName);
	void setSpeciality(const char* newSpeciality);
	void setFn(unsigned newFn);

	~Student();
};