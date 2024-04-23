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

        // Skip all comment lines
        do
        {
            std::getline(file, line);
        } while (line[0] == '%');

        // Parse the dimensions and number of non-zero entries
        std::istringstream iss(line);
        if (!(iss >> rows >> cols >> nnz))
        {
            throw std::runtime_error("Failed to read matrix dimensions and nnz");
        }

        Matrix<T, order> m(rows, cols);

        // Read the non-zero elements
        while (std::getline(file, line))
        {
            if (line[0] == '%')
                continue; // Skip comment lines in the data section

            std::istringstream iss(line);
            if (iss >> row >> col >> val)
            {
                m(row - 1, col - 1) = val; // Convert 1-based index to 0-based index
            }
            else
            {
                std::cerr << "Error reading matrix data" << std::endl;
                throw std::runtime_error("Invalid matrix data");
            }
        }

        return m;
    }

} // namespace algebra

#endif
