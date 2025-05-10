#pragma once
class Matrix
{
    int** _mtx;
    size_t _rows;
    size_t _colls;

    void free();
    void allocateMemory(const size_t rows, const size_t colls);
    void assignValues(const int** otherMtx, size_t newRows, size_t newColls);
    void copyFrom(const Matrix& other);
    void copyFromMtx(int** otherMtx, size_t newRows, size_t newColls);
public:

    Matrix();
    Matrix(const size_t rows, const size_t colls);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);
    void init(const size_t rows, const size_t colls);

    const int** getMtx() const;
    const size_t getRows() const;
    const size_t getColls() const;

    void setMtx(int** newMtx, size_t newRows, size_t newColls);
    void setRows(size_t newRows);
    void setColls(size_t newColls);
};