#pragma once
#include "DataSource.hpp"
#include <utility>

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

	virtual bool canContinue() const override
	{
		return is.good() && !(is.eof());
	}

	virtual bool reset() override
	{
		is.clear();
		is.seekg(initialPos);
		return is.good();
	}

	virtual const T& operator() const override
	{
		return currentEl;
	}

	virtual FileDataSource<T>* clone() const override
	{
		return new FileDataSource(*this);
	}



private:
	std::ifstream is;
	std::streampos initialPos;
	T currentEl;
};