#include "CompositeTask.h"
#include <stdexcept>
#include <iostream>

// strong exception safe(if used in constructor)
void CompositeTask::copyDynamic(const char* name, const Task* const* subtasks,
	const size_t count, const size_t cap, bool copyName)
{
	if (!name || *name == '\0')
		throw std::invalid_argument("Name cannot be empty");
	if (!subtasks)
		throw std::invalid_argument("Subtasks cannot be empty");

	if (copyName) 
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

	this->subtasks = new Task * [cap];
	size_t copied = 0;
	try
	{
		for (; copied < count; copied++)
		{
			this->subtasks[copied] = subtasks[copied]->clone();
		}
	}
	catch (...)
	{
		for (size_t i = 0; i < copied; i++)
		{
			delete this->subtasks[i];
		}
		delete[] this->subtasks;
	}
}

void CompositeTask::free()
{
	delete[] name;
	name = nullptr;

	for (size_t i = 0; i < tasksCount; i++)
	{
		delete subtasks[i];
	}
	delete[] subtasks;

	subtasks = nullptr;
}

CompositeTask* CompositeTask::clone() const
{
	return new CompositeTask(*this);
}

unsigned CompositeTask::getTime() const
{
	return completionTime + totalTime();
}

std::ostream& CompositeTask::print(std::ostream& os) const
{
	for (size_t i = 0; i < tasksCount; i++)
	{
		subtasks[i]->print(os);
	}

	return os;
}

CompositeTask::~CompositeTask()
{
	free();
}

CompositeTask::CompositeTask(const char* name, const Task* const* subtasks,
	const size_t tasksCount,const size_t tasksCap)
	:name(nullptr), subtasks(nullptr)
{
	try
	{
		copyDynamic(name, subtasks, tasksCount, tasksCap);
	}
	catch (...)
	{
		free();
		throw;
	}

	this->tasksCount = tasksCount;
	this->tasksCap = tasksCap;
}

CompositeTask::CompositeTask(const CompositeTask& other)
	:CompositeTask(other.name, other.subtasks, other.tasksCount, other.tasksCap)
{
}

CompositeTask::CompositeTask(CompositeTask&& other)
{
	swap(other);
}

CompositeTask& CompositeTask::operator=(const CompositeTask& other)
{
	if (this != &other)
	{
		CompositeTask temp(other);
		swap(temp);
	}
	return *this;
}

CompositeTask& CompositeTask::operator=(CompositeTask&& other)
{
	if (this != &other)
	{
		free();
		swap(other);
	}

	return *this;
}

void CompositeTask::addTask(const Task* task)
{
	if (!task)
		return;

	if (tasksCount == tasksCap)
		resize();

	subtasks[tasksCount] = task->clone();
	tasksCount++;
}

unsigned CompositeTask::totalTime() const
{
	unsigned result = 0;
	for (size_t i = 0; i < tasksCount; i++)
	{
		result += subtasks[i]->getTime();
	}

	return result;
}

void CompositeTask::printPlan() const
{
	print(std::cout);
}

void CompositeTask::resize()
{													   
	Task** newSubtasks = new Task * [tasksCap * 2];
	size_t copied = 0;

	try
	{
		for (; copied < tasksCount; copied++)
			newSubtasks[copied] = subtasks[copied]->clone();
	}
	catch (...)
	{
		for (size_t i = 0; i < copied; i++)
		{
			delete newSubtasks[i];
		}
		delete[] newSubtasks;
		throw;
	}
	

	for (size_t i = 0; i < tasksCount; i++)
		delete subtasks[i];
	delete[] subtasks;

	subtasks = newSubtasks;
	tasksCap *= 2;
}

void CompositeTask::swap(CompositeTask& other)
{
	std::swap(name, other.name);
	std::swap(subtasks, other.subtasks);
	std::swap(tasksCount, other.tasksCount);
	std::swap(tasksCap, other.tasksCap);
}

std::ostream& operator<<(std::ostream& os, const CompositeTask& task)
{
	return task.print(os);
}
