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
        Matrix(std::size_t rows_, std::size_t cols_) : m_rows(rows_), m_cols(cols_)
        {
            // Initialize the matrix with zeros
            for (std::size_t i = 0; i < m_rows; ++i)
            {
                for (std::size_t j = 0; j < m_cols; ++j)
                {
                    m_matrix[{i, j}] = 0;
                }
            }
        } // constructor

        void printMatrix() const;
        T getVal(std::size_t i, std::size_t j) const;
        void printArray() const;

        void compressCOO();
        void uncompress();
        bool is_compressed() const;
        void resize(std::size_t new_rows, std::size_t new_cols);

        // Overload the () operator
        T &operator()(std::size_t i, std::size_t j)
        {
            return m_matrix[{i, j}];
        }
    };

} // namespace algebra
#endif