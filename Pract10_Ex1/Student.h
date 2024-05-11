#pragma once

class Student
{
	char* _name = nullptr;
	char* _speciality = nullptr;
	unsigned _fn = 0;

	void copyFrom(const Student& other);
	void moveFrom(Student&& other);
	void free();
	bool isValidName(const char* name);

public:

	Student() = default;
	Student(const Student& other);
	Student(const char* name, const char* speciality, unsigned fn);
	Student(Student&& other) noexcept;

	Student& operator=(const Student& other);
	Student& operator=(Student&& other) noexcept;

	const char* getName() const;
	const char* getSpeciality() const;
	unsigned getFn() const;

	void setName(const char* newName);
	void setSpeciality(const char* newSpeciality);
	void setFn(unsigned newFn);

	~Student();
};