#pragma once
#include <stdexcept>
template<typename T>
class DataSource
{

public:
	
	virtual const T& next() = 0;
	virtual bool canContinue() const = 0;
	virtual bool reset() = 0;
	virtual const T& operator()() const = 0;
	virtual DataSource* clone() const = 0;

	virtual ~DataSource() = default;

	T* getMultiple(unsigned count)
	{
		ensureNext();

		T* toReturn = new T[count];

		try
		{
			for (size_t i = 0; i < count; i++)
			{
				toReturn[i] = next();
			}
		}
		catch (...)
		{
			delete[] toReturn;
			throw;
		}

		return toReturn;
	}

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

protected:
	void ensureNext() const
	{
		if (!canContinue())
			throw std::runtime_error("end of data source reached");
	}
	
	void ensureNext()
	{
		if (!canContinue())
			throw std::runtime_error("end of data source reached");
	}
};
