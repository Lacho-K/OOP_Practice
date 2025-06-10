#include "SimpleTask.h"
#include <stdexcept>
#include <iostream>

SimpleTask* SimpleTask::clone() const
{
	return new SimpleTask(*this);
}

unsigned SimpleTask::getTime() const
{
	return completionTime;
}

SimpleTask::~SimpleTask()
{
	free();
}

SimpleTask::SimpleTask(const SimpleTask& other) 
	: SimpleTask(other.description, other.completionTime)
{}

SimpleTask::SimpleTask(SimpleTask&& other) noexcept
{
	swap(other);
}

SimpleTask& SimpleTask::operator=(const SimpleTask& other)
{
	if (this != &other)
	{
		SimpleTask temp(other);
		swap(temp);
	}
	return *this;
}

SimpleTask& SimpleTask::operator=(SimpleTask&& other) noexcept
{
	if (this != &other)
	{
		free();
		swap(other);
	}

	return *this;
}

void SimpleTask::free()
{
	delete[] description;
	description = nullptr;
}

void SimpleTask::swap(SimpleTask& other)
{
	std::swap(description, other.description);
	std::swap(completionTime, other.completionTime);
}

SimpleTask::SimpleTask(const char* desc, unsigned compTime)
	: description(nullptr)
{
	try
	{
		copyDynamic(desc);
	}
	catch (const std::bad_alloc)
	{
		free();
		throw;
	}
	catch (...)
	{
		free();
		throw;
	}
	completionTime = compTime;
}

void SimpleTask::setDescription(const char* desc)
{
	char* temp = new char[strlen(desc) + 1];
	strcpy(temp, desc);
	delete[] description;
	description = temp;
}

void SimpleTask::setCompTime(unsigned compTime)
{
	this->completionTime = compTime;
}

std::ostream& SimpleTask::print(std::ostream& os) const
{
	return (os << description << std::endl);
}

// it's meaningless to have tasks without description
void SimpleTask::copyDynamic(const char* data)
{
	if(!data || *data == '\0')
		throw std::invalid_argument("Data to copy was empty");

	description = new char[strlen(data) + 1];
	strcpy(description, data);
}

std::ostream& operator<<(std::ostream& os, const SimpleTask& task)
{
	return task.print(os);
}
