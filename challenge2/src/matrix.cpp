#include "matrix.hpp"
#include <iostream>
#include <string>

namespace algebra
{
    // gets value at position (i, j), NEEDS TESTING FOR COMPRESSED AND UNCOMRESSED MATRICES
    template <typename T, StorageOrder order>
    T Matrix<T, order>::getVal(std::size_t i, std::size_t j) const
    {
        auto it = m_matrix.find({i, j});
        return it != m_matrix.end() ? it->second : 0; // Return 0 if the element is not found
    }

    // prints the matrix, only for vizualization
    template <typename T, StorageOrder order>
    void Matrix<T, order>::printMatrix() const
    {
        if (order == StorageOrder::RowMajor)
        {
            for (std::size_t i = 0; i < m_rows; ++i)
            {
                for (std::size_t j = 0; j < m_cols; ++j)
                {
                    std::cout << getVal(i, j) << " ";
                }
                std::cout << "\n";
            }
        }
        else
        {
            for (std::size_t j = 0; j < m_cols; ++j)
            {
                for (std::size_t i = 0; i < m_rows; ++i)
                {
                    std::cout << getVal(i, j) << " ";
                }
                std::cout << "\n";
            }
        }
    }

    // prints an array of the matrix, you can see the values and their positions
    template <typename T, StorageOrder order>
    void Matrix<T, order>::printArray() const
    {
        std::cout << "-----DEBUG: Printing array\n";
        for (const auto &elem : m_matrix)
        {
            std::cout << elem.first[0] << " " << elem.first[1] << " " << elem.second << "\n";
        }
    }

    // resizes the matrix, NEEDS TESTING
    template <typename T, StorageOrder order>
    void Matrix<T, order>::resize(std::size_t new_rows, std::size_t new_cols)
    {
        std::cout << "---------DEBUG: Resizing matrix " << m_rows << "x" << m_cols << " to " << new_rows << "x" << new_cols << "\n";
        if (new_rows == m_rows && new_cols == m_cols)
        {
            return;
        }

        std::map<std::array<std::size_t, 2>, T> new_matrix;
        for (std::size_t i = 0; i < new_rows; ++i)
        {
            for (std::size_t j = 0; j < new_cols; ++j)
            {
                if (i < m_rows && j < m_cols)
                {
                    new_matrix[{i, j}] = getVal(i, j);
                }
                else
                {
                    new_matrix[{i, j}] = 0;
                }
            }
        }

        m_matrix = new_matrix;
        m_rows = new_rows;
        m_cols = new_cols;
        compressed = false;
    }

    // checks if the matrix is compressed
    template <typename T, StorageOrder order>
    bool Matrix<T, order>::is_compressed() const
    {
        return compressed;
    }

    // compresses the matrix using COO, NEEDS TESTING
    template <typename T, StorageOrder order>
    void Matrix<T, order>::compressCOO()
    {
        if (compressed)
        {
            std::cout << "---------DEBUG: Matrix is already compressed\n";
            return;
        }

        std::map<std::array<std::size_t, 2>, T> compressed_matrix;
        if (order == StorageOrder::RowMajor)
        {
            for (std::size_t i = 0; i < m_rows; ++i)
            {
                for (std::size_t j = 0; j < m_cols; ++j)
                {
                    if (getVal(i, j) != 0)
                    {
                        compressed_matrix[{i, j}] = getVal(i, j);
                    }
                }
            }
        }
        else
        {
            for (std::size_t j = 0; j < m_cols; ++j)
            {
                for (std::size_t i = 0; i < m_rows; ++i)
                {
                    if (getVal(i, j) != 0)
                    {
                        compressed_matrix[{i, j}] = getVal(i, j);
                    }
                }
            }
        }

        m_matrix = compressed_matrix;
        compressed = true;
    }

    // uncompresses the matrix
    template <typename T, StorageOrder order>
    void Matrix<T, order>::uncompress()
    {
        if (!compressed)
        {
            std::cout << "---------DEBUG: Matrix is already uncompressed\n";
            return;
        }

        if (order == StorageOrder::RowMajor)
        {
            for (std::size_t i = 0; i < m_rows; ++i)
            {
                for (std::size_t j = 0; j < m_cols; ++j)
                {
                    if (m_matrix.find({i, j}) == m_matrix.end())
                    {
                        m_matrix[{i, j}] = 0;
                    }
                }
            }
        }
        else
        {
            for (std::size_t j = 0; j < m_cols; ++j)
            {
                for (std::size_t i = 0; i < m_rows; ++i)
                {
                    if (m_matrix.find({i, j}) == m_matrix.end())
                    {
                        m_matrix[{i, j}] = 0;
                    }
                }
            }
        }

        compressed = false;
    }

    // Explicit template instantiation
    template class Matrix<int, StorageOrder::RowMajor>;
    template class Matrix<int, StorageOrder::ColumnMajor>;
    template class Matrix<double, StorageOrder::RowMajor>;
    template class Matrix<double, StorageOrder::ColumnMajor>;

} // namespace algebra