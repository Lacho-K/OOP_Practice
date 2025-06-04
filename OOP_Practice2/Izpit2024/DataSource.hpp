#pragma once
#include <stdexcept>
template<typename T>
class DataSource
{

public:
	
	virtual const T& next() = 0;
	virtual T* getMultiple(unsigned count) = 0;
	bool canContinue() = 0 const;
	bool reset() = 0;
	const T& operator() = 0 const;

	DataSource& operator>>(T& el) const
	{
		if (!canContinue())
			throw std::runtime_error("Can't get next element");

		el = next();
		return *this;
	}

	operator bool() const
	{
		return canContinue();
	}
};
