#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <map>
#include <array>

enum class StorageOrder
{
    RowMajorm,
    ColumMajor
};

class Matrix
{
private:
    std::map<std::array<std::size_t, 2>, int> m_matrix;
    std::size_t rows, cols;

public:
    Matrix(std::size_t rows_, std::size_t cols_) : rows(rows_), cols(cols_) {} // constructor, only defined

    void printMatrix() const;

    int getVal(std::size_t i, std::size_t j) const;

    // Overload the [] operator
    int &operator[](const std::array<std::size_t, 2> &index)
    {
        return m_matrix[index];
    }
};
#endif