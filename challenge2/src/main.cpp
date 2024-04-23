#include <iostream>
#include <vector>

#include "testCases.hpp"

int main()
{
    // path of file to be read in Market Matrix Format
    std::string filename = "data/lnsp_131.mtx";

    // Test for creating and compressing a simple matrix
    test_MakeAndCompress();

    // Test for multiplying a matrix with a vector in different cases
    test_MatrixTimesVector();

    // Test for reading the matrix lnsp_131.mtx
    // test_ReadMatrix(filename);

    return 0;
}