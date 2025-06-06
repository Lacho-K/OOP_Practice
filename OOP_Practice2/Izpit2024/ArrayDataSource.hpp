#pragma once
#include "DataSource.hpp"
#include <cassert>

template<typename T>
class ArrayDataSource : public DataSource<T>
{
public:

	ArrayDataSource() = default;

	ArrayDataSource(const ArrayDataSource<T>& other)
	{
		copyFrom(other.els, other.count);
	}

	ArrayDataSource(ArrayDataSource<T>&& other) noexcept
	{
		moveFrom(std::move(other));
	}

	ArrayDataSource(T* elements, size_t size)
	{
		copyFrom(elements, size);
	}

	ArrayDataSource<T>& operator=(const ArryDataSource<T>& other)
	{
		if (this != &other)
		{
			ArrayDataSource<T> temp(other);
			swap(other);
		}

		return *this;
	}
	
	ArrayDataSource<T>& operator=(ArryDataSource<T>&& other)
	{
		if (this != &other)
		{
			free();
			moveFrom(std::move(other));
		}

		return *this;
	}

	~ArrayDataSource()
	{
		free();
	}

	virtual ArrayDataSource<T>* clone() const override
	{
		return new ArrayDataSource(*this);
	}

	virtual const T& next() override
	{
		ensureNext();

		return els[index++];
	}

	virtual bool canContinue() const override
	{
		return index < count;
	}

	virtual bool reset() override
	{
		index = 0;
		return true;
	}

	virtual const T& operator() const override
	{
		assert(index < count);

		return els[index];
	}

	ArrayDataSource<T>& operator+=(const T el)
	{
		if (count == cap)
			resize();

		els[count] = el;
		count++;

		return *this;
	}

	ArrayDataSource<T> operator+(const T el) const
	{
		ArrayDataSource<T> temp(*this);
		temp += el;
		return temp;
	}

	ArrayDataSource<T>& operator--()
	{
		assert(index > 0);
		index--;
		return *this;
	}


private:
	T* els = nullptr;
	size_t index = 0;
	size_t count = 0;
	size_t cap = 4;

	void swap(ArrayDataSource<T>& other)
	{
		std::swap(els, other.els);
		std::swap(index, other.index);
		std::swap(count, other.count);
		std::swap(cap, other.cap);
	}

	void copyFrom(T* elements, size_t size)
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

	void moveFrom(ArrayDataSource<T>& other)
	{
		els = other.els;
		count = other.count;
		cap = other.cap;

		other.els = nullptr;
		other.count = other.cap = 0;
	}

	void free()
	{
		delete[] els;
		count = cap = 0;
		els = nullptr;
	}

	void resize()
	{
		T* newContainder = new T[cap * 2];

		unsigned copied = 0;
		try
		{
			for (; copied < count; copied++)
			{
				newContainer[copied] = els[copied];
			}
		}
		catch (...)
		{
			delete[] newContainder;
			throw;
		}

		delete[] els;
		els = newContainder;
		cap *= 2;
	}
};