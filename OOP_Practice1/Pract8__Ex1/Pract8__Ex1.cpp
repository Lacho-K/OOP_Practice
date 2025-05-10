#include <iostream>
#include "Matrix.h"

void Matrix::free()
{
	for (size_t i = 0; i < _rows; i++)
	{
		delete[] _mtx[i];
	}
	delete[] _mtx;
}


void Matrix::copyFrom(const Matrix& other)
{
	_rows = other.getRows();
	_colls = other.getColls();
	allocateMemory(_rows, _colls);
	assignValues(other.getMtx(), _rows, _colls);
}

void Matrix::copyFromMtx(int** otherMtx, size_t newRows, size_t newColls)
{
	_rows = newRows;
	_colls = newColls;
	allocateMemory(_rows, _colls);
	assignValues(otherMtx, _rows, _colls);
}

void Matrix::allocateMemory(const size_t rows, const size_t colls)
{
	_mtx = new int* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		_mtx[i] = new int[colls];
	}
}

void Matrix::assignValues(const int** otherMtx, size_t newRows, size_t newColls)
{
	for (size_t i = 0; i < newRows; i++)
	{
		for (size_t j = 0; j < newColls; j++)
		{
			_mtx[i][j] = otherMtx[i][j];
		}
	}
}


Matrix::Matrix()
{
	init(2, 2);
}

Matrix::Matrix(const size_t rows, const size_t colls)
{
	init(rows, colls);
}
Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}
Matrix::~Matrix()
{
	free();
}
Matrix& Matrix::operator=(const Matrix& other)
{
	if (this == &other)
		return;

	free();
	copyFrom(other);
}
void Matrix::init(const size_t rows, const size_t colls)
{
	if (rows < 1 || colls < 1)
		return;
	_rows = rows;
	_colls = colls;
	allocateMemory(_rows, _colls);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < colls; j++)
		{
			_mtx[i][j] = 0;
		}
	}
}
const int** Matrix::getMtx() const
{
	return _mtx;
}
const size_t Matrix::getRows() const
{
	return _rows;
}
const size_t Matrix::getColls() const
{
	return _colls;
}
void Matrix::setMtx(int** newMtx, size_t newRows, size_t newColls)
{
	if (!newMtx || _mtx == newMtx || newRows < 1 || newColls < 1)
		return;

	free();
	copyFromMtx(newMtx, newRows, newColls);
}
void Matrix::setRows(size_t newRows)
{
	if(newRows > 0)
	_rows = newRows;
}
void Matrix::setColls(size_t newColls)
{
	if (newColls > 0)
	_colls = newColls;
}

// TODO
Matrix operator+(const Matrix& mtx1, const Matrix& mtx2)
{
	size_t minRow = std::min(mtx1.getRows(), mtx2.getRows());
	size_t minColl = std::min(mtx1.getColls(), mtx2.getColls());

	Matrix resultMtx(minRow, minColl);
}

int main()
{
	std::cout << "Hello World!\n";
}