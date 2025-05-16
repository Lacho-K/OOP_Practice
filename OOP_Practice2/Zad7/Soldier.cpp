#include "Soldier.h"
#include <string.h>
#include <stdexcept>

Soldier::Soldier():name("No name"), age(0), skillLevel(0), salary(0)
{
}

const char* Soldier::getName() const
{
	return name;
}

void Soldier::setName(const char* newName)
{
	if (!newName || strlen(newName) >= 50)
		throw std::invalid_argument("Name cannot be empty or more than 50 symbols");

	strcpy(name, newName);
}

int Soldier::getSkillLevel() const
{
	return skillLevel;
}

void Soldier::setSkillLevel(int skillLevel)
{
	if (skillLevel < 0)
		throw std::invalid_argument("Skill level cannot be < 0");

	this->skillLevel = skillLevel;
}

double Soldier::getSalary() const
{
	return salary;
}

void Soldier::setSalary(double salary)
{
	if (salary < 0)
		throw std::invalid_argument("Salary cannot be < 0");
	this->salary = salary;
}

Soldier::Soldier(const char* name, unsigned short age, int skilLevel, double salary)
	:age(age), skillLevel(skilLevel), salary(salary)
{
	setName(name);
}
