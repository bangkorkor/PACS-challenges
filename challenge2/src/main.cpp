#include "matrix.hpp"
#include <iostream>

#include <vector>

int main()
{
    algebra::Matrix<int, algebra::StorageOrder::RowMajor> m(3, 3);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(0, 2) = 3;
    m(1, 0) = 4;
    m(1, 1) = 5;
    m(1, 2) = 6;
    m(2, 0) = 7;
    m(2, 1) = 8;
    m(2, 2) = 9;
    m.printArray();

    std::vector<int> v = {2, 1, 0};
    std::vector<int> res = m * v;

    std::cout << "Result of matrix-vector multiplication: " << res[0] << " " << res[1] << " " << res[2] << "\n";

    return 0;
}