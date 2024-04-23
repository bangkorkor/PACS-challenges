#include "matrix.hpp"
#include "readMatrix.hpp"
#include <iostream>

#include <vector>

int main()
{
    // path of file to be read in Market Matrix Format
    std::string filename = "data/a.mtx";

    // Read the matrix from a file
    algebra::Matrix<double, algebra::StorageOrder::RowMajor> mat = algebra::readMatrix<double, algebra::StorageOrder::RowMajor>(filename);
    mat.compressCOO();
    // Print the matrix
    mat.printArray();

    std::vector<double> vec = {1, 2, 3};
    std::vector<double> res = mat * vec;

    // Print the result
    std::cout << "Result: \n\n";
    for (auto &val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}