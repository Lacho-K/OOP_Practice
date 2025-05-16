#pragma once

class Soldier
{
	char name[51];
	unsigned short age;
	int skillLevel;
	double salary;

public:
	Soldier();
	Soldier(const char* name, unsigned short age, int skilLevel, double salary);

	const char* getName() const;
	void setName(const char* newName);
	int getSkillLevel() const;
	void setSkillLevel(int skillLevel);
	double getSalary() const;
	void setSalary(double salary);
};
