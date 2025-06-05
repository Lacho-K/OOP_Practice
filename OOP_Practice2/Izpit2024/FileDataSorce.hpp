#pragma once
#include "DataSource.hpp"
#include <istream>

template<typename T>
class FileDataSource : public DataSource<T>
{
public:

	// no need for def. ctor

	explicit FileDataSource(const char* fileName) : is(fileName)
	{
		if (!is.good())
			throw std::runtime_error("Input stream not found");

		initialPos = is.tellg();
	}

	virtual const T& next() override
	{
		ensureNext();

		is >> currentEl;
		return currentEl;
	}

	virtual bool canContinue() = 0 const override
	{
		return is.good() && !(is.eof());
	}

	virtual bool reset() override
	{
		is.clear();
		is.seekg(initialPos);
	}

	virtual const T& operator() = 0 const override
	{
		return currentEl;
	}



private:
	std::istream is;
	int initialPos;
	T currentEl;
};