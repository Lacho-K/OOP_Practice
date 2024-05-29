#pragma once
#include <iostream>
template <typename T, unsigned capacity>
class Sorted
{
private:
	T _arr[capacity];
	unsigned count = 0;
	int getRemoveItemIndex(T item);
	void sort();

public:
	const T* getArr() const;
	unsigned getCapacity() const;

	void add(T element);
	void remove(T element);
	void print() const;
};


template<typename T, unsigned capacity>
inline int Sorted<T, capacity>::getRemoveItemIndex(T item)
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (_arr[i] == item)
			return i;
	}
	return -1;
}

template<typename T, unsigned capacity>
inline void Sorted<T, capacity>::sort()
{
	for (size_t i = 0; i < count; i++)
	{
		bool hasSwapped = false;
		for (size_t j = 0; j < count-1-i; j++)
		{
			if (_arr[j] > _arr[j + 1]) 
			{
				std::swap(_arr[j], _arr[j + 1]);
				hasSwapped = true;
			}
		}
		if (!hasSwapped)
			return;
	}
}

template <typename T, unsigned capacity>
inline const T* Sorted<T, capacity>::getArr() const
{
	return _arr;
}

template <typename T, unsigned capacity>
inline unsigned Sorted<T, capacity>::getCapacity() const
{
	return capacity;
}

template <typename T, unsigned capacity>
inline void Sorted<T, capacity>::add(T element)
{
	if (count >= capacity)
		throw std::exception("capacity exceeded");

	_arr[count++] = element;

	if(count > 1)
	sort();
}

template <typename T, unsigned capacity>
inline void Sorted<T, capacity>::remove(T element)
{
	int removeIndex = getRemoveItemIndex(element);
	if (removeIndex == -1)
		throw std::exception("Element not present in array");

	for (size_t i = removeIndex; i < capacity-1; i++)
	{
		_arr[i + 1] = _arr[i];
	}
}

template <typename T, unsigned capacity>
inline void Sorted<T, capacity>::print() const
{
	for (size_t i = 0; i < count; i++)
	{
		std::cout << _arr[i];
	}
}
