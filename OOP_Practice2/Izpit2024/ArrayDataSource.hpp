#pragma once
#include "DataSource.hpp"
template<typename T>
class ArrayDataSource : public DataSource<T>
{
public:
	ArrayDataSource(T* elements, size_t size)
	{
		if (!elements && size > 0)
			throw std::invalid_argument("invalid array data source");

		els = new T[size];
		try
		{
			for (size_t i = 0; i < size; i++)
			{
				els[i] = elements[i];
			}
		}
		catch (...)
		{
			delete[] els;
			throw;
		}

		count = size;
		cap = count * 2;
	}

	virtual const T& next() override
	{
		ensureNext();

		return els[index++];
	}

	virtual bool canContinue() = 0 const override
	{
		return index < count;
	}

	virtual bool reset() override
	{
		index = 0;
	}

	virtual const T& operator() = 0 const override
	{
		ensureNext();

		return els[index];
	}




private:
	T* els = nullptr;
	size_t index;
	size_t count = 0;
	size_t cap = 0;
};