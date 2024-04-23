#ifndef READMATRIX_H
#define READMATRIX_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <array>
#include <algorithm>
#include <iterator>
#include <tuple>

#include "matrix.hpp"

namespace algebra
{
    // reads a matrix from a file
    template <typename T, StorageOrder order>
    Matrix<T, order> readMatrix(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            throw std::runtime_error("Could not open file");
        }

        std::string line;
        std::size_t rows, cols, nnz;
        std::size_t row, col;
        T val;

        // Read the header
        std::getline(file, line);
        if (line[0] != '%')
        {
            throw std::runtime_error("Invalid header");
        }

        // Read the header
        std::getline(file, line);
        std::istringstream iss(line);
        iss >> rows >> cols >> nnz;

        Matrix<T, order> m(rows, cols);

        // Read the data
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            iss >> row >> col >> val;
            m(row - 1, col - 1) = val;
        }

        return m;
    }

} // namespace algebra

#endif
