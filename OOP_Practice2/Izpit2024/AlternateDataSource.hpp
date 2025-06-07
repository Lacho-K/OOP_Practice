#pragma once
#include "DataSource.hpp"

template<typename T>
class AlternateDataSource : public DataSource<T>
{
public:

	AlternateDataSource(const AlternateDataSource<T>& other) :
		AlternateDataSource(other.sources, other.count)

	{
		index = other.index;
	}

	AlternateDataSource(DataSource<T>** src, size_t size)
	{
		sources = copySources(src, size);
		count = size;
	}


	AlternateDataSource(AlternateDataSource<T>&& other)
	{
		moveFrom(other);
	}

	AlternateDataSource<T>& operator=(const AlternateDataSource<T>& other)
	{
		if (this != &other)
		{
			AlternateDataSource temp(other);
			swap(temp);
		}

		return *this;
	}
	
	AlternateDataSource<T>& operator=(AlternateDataSource<T>&& other)
	{
		if (this != &other)
		{
			free();
			moveFrom(std::move(other));
		}

		return *this;
	}

	~AlternateDataSource()
	{
		free();
	}

	virtual AlternateDataSource<T>* clone() const override
	{
		return new AlternateDataSource(*this);
	}

	virtual const T& next() override
	{
		this->ensureNext();

		increaseIndex();

		while (!((*sources[index]).canContinue()))
		{
			increaseIndex();
		}

		return sources[index]->next();
	}

	virtual bool canContinue() const override
	{
		for (size_t i = 0; i < count; i++)
		{
			if (sources[i]->canContinue())
				return true;
		}

		return false;
	}

	virtual bool reset() override
	{
		for (size_t i = 0; i < count; i++)
		{
			sources[i]->reset();
		}
		return true;
	}

	virtual const T& operator()() const override
	{
		this->ensureNext();

		return (*sources[index])();
	}



private:
	DataSource<T>** sources = nullptr;
	size_t index = 0;
	size_t count = 0;

	DataSource<T>** copySources(DataSource<T>** src, size_t size)
	{
		if (!src || size == 0)
			throw std::invalid_argument("Empty array of data sources");

		DataSource<T>** container = new DataSource<T>*[size];

		size_t copiedCount = 0;
		try
		{
			for (; copiedCount < size; copiedCount++)
			{
				container[copiedCount] = src[copiedCount]->clone();
			}
		}
		catch (...)
		{
			for (size_t i = 0; i < copiedCount; i++)
			{
				delete container[i];
			}
			delete[] container;
			throw;
		}

		return container;
	}

	void free()
	{
		for (size_t i = 0; i < count; i++)
		{
			delete sources[i];
		}
		delete[] sources;
	}

	void moveFrom(AlternateDataSource<T>&& other)
	{
		sources = other.sources;
		index = other.index;
		count = other.count;

		other.sources = nullptr;
		other.index = other.count = 0;
	}

	void swap(AlternateDataSource<T>& other)
	{
		std::swap(sources, other.sources);
		std::swap(count, other.count);
		std::swap(index, other.index);
	}

	void increaseIndex()
	{
		index++;
		if (index >= count)
			index = 0;
	}
};