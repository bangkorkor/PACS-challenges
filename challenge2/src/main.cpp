#include "matrix.hpp"
#include <iostream>

int main()
{
    Matrix m(3, 5);
    // std::cout << m.getVal(0, 0) << "\n";
    m[{0, 0}] = 1;

    m.printMatrix();

    return 0;
}