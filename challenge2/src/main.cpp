#include "matrix.hpp"
#include <iostream>

int main()
{
    algebra::Matrix<double, algebra::StorageOrder::RowMajor> m(3, 5);
    // std::cout << m.getVal(0, 0) << "\n";
    m(0, 0) = 1.2;
    m(0, 1) = 2.3;
    m(0, 2) = 3.4;
    m(0, 3) = 4.5;
    m(0, 4) = 5.6;
    m(1, 0) = 6.7;

    m(2, 3) = 14.5;
    m(2, 4) = 15.6;

    m.printMatrix();
    m.printArray();

    std::cout << "\nCompressed matrix:\n\n";
    m.compressCOO();
    m.printMatrix();
    m.printArray();
    m.is_compressed() ? std::cout << "Matrix is compressed\n" : std::cout << "Matrix is not compressed\n";

    std::cout << "\nUncompressing matrix:\n\n";
    m.uncompress();
    m.printArray();

        return 0;
}