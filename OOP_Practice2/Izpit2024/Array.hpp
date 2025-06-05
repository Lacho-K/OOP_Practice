#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <type_traits>

template<typename T>
class Array
{
public:

	Array() = default;

	Array(const Array& other)
	{
		copyFrom(other);
	}

	Array& operator=(const Array& other)
	{
		if (this != &other)
		{
			Array temp(other);
			swap(temp);
		}
		return *this;
	}

	~Array()
	{
		free();
	}

	Array(Array&& other) noexcept
	{
		els = nullptr;
		count = 0;
		cap = 0;
		swap(other);
	}

	Array& operator=(Array&& other) noexcept
	{
		if (this != &other)
		{
			free();
			swap(other);
		}
		return *this;
	}

	void add(const T& el)
	{
		if (cout == cap)
			resize();

		els[count] = el;
		count++;
	}

	bool remove(const T& el)
	{
		int ind = contains(el);

		if (ind != -1)
		{
			std::swap(els[ind], els[count - 1]);
			count--;
			return true;
		}

		return false;
	}

	int contains(const T& el)
	{
		for (size_t i = 0; i < count; i++)
		{
			if (els[i] == el)
				return i;
		}

		return -1;
	}

private:

	T* els = nullptr;
	size_t count = 0;
	size_t cap = 8;

	void free()
	{
		if (els)
		{
			delete[] els;
			els = nullptr;
		}
		count = 0;
		cap = 0;
	}

	void copyFrom(const Array& other)
	{
		if (!other.els || other.count > other.cap)
		{
			throw std::invalid_argument("Invalid source array for copy");
		}

		T* newEls = new T[other.cap];
		size_t i = 0;

		try
		{
			for (; i < other.count; i++)
			{
				newEls[i] = other.els[i];
			}
		}
		catch (...)
		{
			delete[] newEls;
			throw;
		}

		free();
		els = newEls;
		count = other.count;
		cap = other.cap;
	}

	void swap(Array& other)
	{
		std::swap(els, other.els);
		std::swap(count, other.count);
		std::swap(cap, other.cap);
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
		catch (const std::exception&)
		{
			for (size_t i = 0; i < copied; i++)
			{
				delete newContainder[i];
			}
			throw;
		}

		delete[] els;
		els = newContainder;
		cap *= 2;
	}
};
