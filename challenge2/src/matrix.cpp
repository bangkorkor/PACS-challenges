#include "matrix.hpp"
#include <iostream>
#include <string>
#include <map>
#include <array>
#include <vector>

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
        std::cout << "-----: Printing array\n";
        for (const auto &elem : m_matrix)
        {
            std::cout << elem.first[0] << " " << elem.first[1] << " " << elem.second << "\n";
        }
    }

    // resizes the matrix
    template <typename T, StorageOrder order>
    void Matrix<T, order>::resize(std::size_t new_rows, std::size_t new_cols)
    {
        std::cout << "---------: Resizing matrix " << m_rows << "x" << m_cols << " to " << new_rows << "x" << new_cols << "\n";
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
            std::cout << "---------: Matrix is already compressed\n";
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
            std::cout << "---------: Matrix is already uncompressed\n";
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

    // Overload the () operator
    template <typename T, StorageOrder order>
    T &Matrix<T, order>::operator()(std::size_t i, std::size_t j)
    {
        // if out of bounds, throw error
        static T error_value;
        if (i >= m_rows || j >= m_cols)
        {
            std::cout << "ERROR: Cannot add value, " << i << " " << j << " is out of bounds\n";
            return error_value;
        }

        // if compressed you can not add new values only change existing ones
        if (compressed && m_matrix.find({i, j}) == m_matrix.end())
        {
            std::cout << "ERROR: Cannot add value, matrix is compressed\n";
            return error_value;
        }
        return m_matrix[{i, j}];
    }

    // Function to multiply a matrix with a vector
    template <typename T, StorageOrder order>
    std::vector<T> operator*(const Matrix<T, order> &mat, const std::vector<T> &vec)
    {
        if (mat.m_cols != vec.size())
        {
            std::cerr << "Error: Matrix and vector dimensions do not match for multiplication.\n";
            return {};
        }

        std::vector<T> res(mat.m_rows, 0);
        if (order == StorageOrder::RowMajor)
        {
            for (std::size_t i = 0; i < mat.m_rows; ++i)
            {
                for (std::size_t j = 0; j < mat.m_cols; ++j)
                {
                    res[i] += mat.getVal(i, j) * vec[j];
                }
            }
        }
        else
        {
            for (std::size_t j = 0; j < mat.m_cols; ++j)
            {
                for (std::size_t i = 0; i < mat.m_rows; ++i)
                {
                    res[i] += mat.getVal(i, j) * vec[j];
                }
            }
        }
        return res;
    }

    // Explicit template instantiation
    template class Matrix<int, StorageOrder::RowMajor>;
    template class Matrix<int, StorageOrder::ColumnMajor>;
    template class Matrix<double, StorageOrder::RowMajor>;
    template class Matrix<double, StorageOrder::ColumnMajor>;

    // Explicit template instantiation for operators
    template std::vector<int> operator*(const Matrix<int, StorageOrder::RowMajor> &mat, const std::vector<int> &vec);
    template std::vector<int> operator*(const Matrix<int, StorageOrder::ColumnMajor> &mat, const std::vector<int> &vec);
    template std::vector<double> operator*(const Matrix<double, StorageOrder::RowMajor> &mat, const std::vector<double> &vec);
    template std::vector<double> operator*(const Matrix<double, StorageOrder::ColumnMajor> &mat, const std::vector<double> &vec);

} // namespace algebra