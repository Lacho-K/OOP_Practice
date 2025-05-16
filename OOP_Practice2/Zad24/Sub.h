#pragma once
#include "Issue.h"
class Sub
{
public:

	Sub();
	Sub(Issue** issues, size_t count, size_t cap);
	Sub(const Sub& other);
	Sub(Sub&& other);

	Sub& operator=(const Sub& other);
	Sub& operator=(Sub&& other);

	Sub& operator+=(const Issue& issue);
	const Issue* operator[](unsigned index) const;

	double calculatePrice() const;

	~Sub();

private:
	Issue** issues;
	size_t count;
	size_t cap;

	void free();
	void swap(Sub& other);
	void copyDynamic(Issue** issues, size_t cap, size_t count);
	void ensureValid(size_t count, size_t cap);
	void resize();
};