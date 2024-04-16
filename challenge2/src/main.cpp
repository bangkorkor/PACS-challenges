#include "matrix.hpp"
#include <iostream>

int main()
{
    algebra::Matrix<double, algebra::StorageOrder::RowMajor> m(3, 5);
    // std::cout << m.getVal(0, 0) << "\n";
    m(0, 0) = 1.2;
    m(1, 2) = 2.4;

    m.printMatrix();

    return 0;
}