#include "matrix.hpp"
#include <iostream>
#include <string>

namespace algebra
{

    template <typename T, StorageOrder order>
    T Matrix<T, order>::getVal(std::size_t i, std::size_t j) const
    {
        auto it = m_matrix.find({i, j});
        return it != m_matrix.end() ? it->second : 0; // Return 0 if the element is not found
    }

    template <typename T, StorageOrder order>
    void Matrix<T, order>::printMatrix() const
    {
        for (std::size_t i = 0; i < m_rows; ++i)
        {
            for (std::size_t j = 0; j < m_cols; ++j)
            {
                std::cout << getVal(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Explicit template instantiation
    template class Matrix<int, StorageOrder::RowMajor>;
    template class Matrix<int, StorageOrder::ColumnMajor>;
    template class Matrix<double, StorageOrder::RowMajor>;
    template class Matrix<double, StorageOrder::ColumnMajor>;

} // namespace algebra