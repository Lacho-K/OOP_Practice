#include "Sub.h";
#include <stdexcept>
#include <cassert>

Sub::Sub():count(0),cap(8), issues(nullptr)
{
	issues = new Issue * [cap];
}

Sub::Sub(Issue** issues, size_t count, size_t cap)
{
	try
	{
		copyDynamic(issues, cap, count);
	}
	catch (...)
	{
		free();
		throw;
	}
	this->count = count;
	this->cap = cap;
}

Sub::Sub(const Sub& other)
{
	try
	{
		copyDynamic(other.issues, other.cap, other.count);
	}
	catch (...)
	{
		free();
		throw;
	}
	count = other.count;
	cap = other.cap;
}

Sub::Sub(Sub&& other)
{
	ensureValid(other.count, other.cap);
	issues = other.issues;
	count = other.count;
	cap = other.cap;

	other.issues = nullptr;
	other.count = other.cap = 0;
}

Sub& Sub::operator=(const Sub& other)
{
	if (this != &other)
	{
		Sub temp(other);
		swap(temp);
	}
	return *this;
}

Sub& Sub::operator=(Sub&& other)
{
	if (this != &other)
	{
		Sub temp(std::move(other));
		swap(temp);
	}
	return *this;
}

Sub& Sub::operator+=(const Issue& issue)
{
	if (count == cap)
		resize();

	issues[count++] = issue.clone();
	return *this;
}

const Issue* Sub::operator[](unsigned index) const
{
	assert(index >= 0 && index < count);
	return issues[index];
}

double Sub::calculatePrice() const
{
	double sum = 0;
	for (size_t i = 0; i < count; i++)
	{
		double currentPrice = issues[i]->getPrice() - (issues[i]->getPrice() * 0.30);
		currentPrice *= issues[i]->getEditions();
		sum += currentPrice;
	}
	return sum;
}

Sub::~Sub()
{
	free();
}

void Sub::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete issues[i];
	}
	delete[] issues;
}

void Sub::swap(Sub& other)
{
	std::swap(issues, other.issues);
	std::swap(count, other.count);
	std::swap(cap, other.cap);
}

void Sub::copyDynamic(Issue** issues, size_t cap, size_t count)
{
	ensureValid(count, cap);

	if (!issues)
		throw std::invalid_argument("Issues cannot be null");

	this->issues = new Issue * [cap];
	size_t copiedCount = 0;
	try
	{
		for (size_t i = 0; i < count; i++)
		{
			this->issues[i] = issues[i]->clone();
			copiedCount++;
		}
	}
	catch (...)
	{
		for (size_t i = 0; i < copiedCount; i++)
		{
			delete this->issues[i];
		}
		delete[] this->issues;
		throw;
	}
}

void Sub::ensureValid(size_t count, size_t cap)
{
	if (count > cap)
		throw std::invalid_argument("Count cannot be > cap");
}

void Sub::resize()
{
	Issue** newIssues = new Issue * [cap * 2];
	for (size_t i = 0; i < count; i++)
	{
		newIssues[i] = issues[i];
	}
	delete[] issues;
	issues = newIssues;
	cap *= 2;
}
