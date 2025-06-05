#pragma once
#include "DataSource.hpp"

template<typename T>
class DefaultDataSource : public DataSource<T>
{
public:

	virtual const T& next() override
	{
		T nextEl;
		return nextEl;
	}

	virtual bool canContinue() const override
	{
		return true;
	}

	virtual bool reset() override
	{
		return true;
	}

	virtual const T& operator() const override
	{
		return next();
	}
};