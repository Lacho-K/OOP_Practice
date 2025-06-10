#pragma once
#pragma warning (disable:4996)
#include <ostream>
class Task
{
public:
	virtual Task* clone() const = 0;

	virtual unsigned getTime() const = 0;

	virtual std::ostream& print(std::ostream& os) const = 0;

	virtual ~Task() = default;

protected:
	unsigned completionTime;
};