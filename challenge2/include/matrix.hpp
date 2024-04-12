#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <map>
#include <array>

namespace algebra
{

    enum class StorageOrder
    {
        RowMajor,
        ColumnMajor
    };

    template <typename T, StorageOrder order>
    class Matrix
    {
    private:
        std::map<std::array<std::size_t, 2>, T> m_matrix;
        std::size_t m_rows, m_cols;
        bool compressed = false;

    public:
        Matrix(std::size_t rows_, std::size_t cols_) : m_rows(rows_), m_cols(cols_) {} // constructor, only defined

        void printMatrix() const;
        T getVal(std::size_t i, std::size_t j) const;

        // Overload the [] operator
        T &operator[](const std::array<std::size_t, 2> &index)
        {
            return m_matrix[index];
        }

        // TODO
        void compress();
        void uncompress();
        bool is_compressed() const;
        void resize(std::size_t new_rows, std::size_t new_cols);
    };

} // namespace name
#endif