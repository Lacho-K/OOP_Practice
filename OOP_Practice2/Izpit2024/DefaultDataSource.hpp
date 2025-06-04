#pragma once
#include "DataSource.hpp"

template<typename T>
class DefaultDataSource : public DataSource<T>
{
public:

	const T& next() override
	{
		T nextEl;
		return nextEl;
	}

	T* getMultiple(unsigned count) override
	{
		T* arr = new T[count];
		for (size_t i = 0; i < count; i++)
		{
			arr[i] = next();
		}

		return arr;
	}

	bool canContinue() const override
	{
		return true;
	}

	bool reset() override
	{
		return true;
	}

	const T& operator() const override
	{
		return next();
	}
};