#pragma once
#include "Task.h"

class SimpleTask : public Task
{
public:

	virtual SimpleTask* clone() const override;

	virtual unsigned getTime() const override;

	virtual std::ostream& print(std::ostream& os) const override;

	virtual ~SimpleTask() override;

	SimpleTask(const SimpleTask& other);
	SimpleTask(SimpleTask&& other) noexcept;
	SimpleTask& operator=(const SimpleTask& other);
	SimpleTask& operator=(SimpleTask&& other) noexcept;

	SimpleTask(const char* desc, unsigned compTime);

	void setDescription(const char* desc);
	void setCompTime(unsigned compTime);
	friend std::ostream& operator<<(std::ostream& os, const SimpleTask& task);

private:
	char* description;

	void free();
	void swap(SimpleTask& other);
	void copyDynamic(const char* data);
};