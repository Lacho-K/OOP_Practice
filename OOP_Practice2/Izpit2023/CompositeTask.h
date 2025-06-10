#pragma once
#include "Task.h"
class CompositeTask : public Task
{
public:
	virtual CompositeTask* clone() const override;

	virtual unsigned getTime() const override;

	virtual std::ostream& print(std::ostream& os) const override;

	virtual ~CompositeTask() override;

	CompositeTask(const char* name, const Task* const* subtasks,
		const size_t tasksCount, const size_t tasksCap);
	CompositeTask(const CompositeTask& other);

	CompositeTask(CompositeTask&& other);

	CompositeTask& operator=(const CompositeTask& other);
	CompositeTask& operator=(CompositeTask&& other);

	friend std::ostream& operator<<(std::ostream& os, const CompositeTask& task);

	void addTask(const Task* task);

	unsigned totalTime() const;

	void printPlan() const;


private:
	char* name;
	Task** subtasks;
	size_t tasksCount;
	size_t tasksCap;

	void resize();
	void swap(CompositeTask& other);
	void copyDynamic(const char* name, const Task* const * subtasks, 
		const size_t count, const size_t cap, bool copyName = 1);
	void free();
};