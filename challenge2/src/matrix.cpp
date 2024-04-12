#include "matrix.hpp"
#include <iostream>
#include <string>

int Matrix::getVal(std::size_t i, std::size_t j) const
{
    auto it = m_matrix.find({i, j});
    return it != m_matrix.end() ? it->second : 0;
}

void Matrix::printMatrix() const
{
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < cols; ++j)
        {
            std::cout << getVal(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
