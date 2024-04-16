#include "matrix.hpp"
#include <iostream>

int main()
{
    algebra::Matrix<int, algebra::StorageOrder::RowMajor> m(3, 3);
    m(0, 0) = 1;
    m(2, 0) = 7;
    m(1, 1) = 8;
    m(2, 2) = 100;
    m.printArray();
    m.compressCOO();
    m.printArray();
    m(0, 1) = 80;
    m.printArray();

    return 0;
}