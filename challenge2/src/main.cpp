#include "matrix.hpp"
#include <iostream>

int main()
{
    algebra::Matrix<int, algebra::StorageOrder::RowMajor> m(3, 3);
    m(0, 0) = 1;
    m(2, 0) = 7;
    m(1, 1) = 4;
    m.compressCOO();
    m.printArray();

    m.resize(2, 2);

    m.printArray();
    return 0;
}