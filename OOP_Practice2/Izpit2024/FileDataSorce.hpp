#pragma once
#include "DataSource.hpp"
#include <istream>

template<typename T>
class FileDataSource : public DataSource<T>
{
public:
	explicit FileDataSource(const char* fileName)
	{
		std::istream is(filename);
		if (!is.good())
			throw std::runtime_error("Input stream not found");



	}

private:
};