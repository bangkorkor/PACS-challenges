// test cases for  challenge2
#ifndef TESTCASES_H
#define TESTCASES_H

#include <chrono>

#include "matrix.hpp"
#include "readMatrix.hpp"

void test_MakeAndCompress()
{
    std::cout << "Test for creating and compressig sparse matrix ------------\n";
    algebra::Matrix<double, algebra::StorageOrder::RowMajor> mat(20, 20);
    mat(0, 0) = 1;
    mat(0, 1) = 2;
    mat(0, 2) = 3;
    mat(1, 0) = 4;
    mat(3, 1) = 5;
    mat(10, 10) = 8;
    mat(2, 2) = 9;
    mat(19, 19) = 7;
    mat.printMatrix();
    mat.compressCOO();
    std::cout << "\nCompressed matrix\n";
    mat.printArray();
}

void test_MatrixTimesVector()
{
    std::cout << "\nTest for multiplying a matrix with a vector in different cases ------------\n";
    algebra::Matrix<double, algebra::StorageOrder::RowMajor> mat(10, 10);
    mat(0, 0) = 1;
    mat(0, 8) = 2;
    mat(1, 5) = 8;
    mat(2, 1) = 3;
    mat(3, 3) = 4;
    mat(3, 9) = 5;
    mat(5, 5) = 6;
    mat(6, 7) = 2;
    mat(7, 2) = 1;
    mat(8, 2) = 9;
    mat(9, 6) = 7;
    std::cout << "uncompressed matrix, product: \n";
    std::vector<double> vec = {2, 2, 2, 1, 1, 1, 1, 1, 1, 1};
    std::vector<double> res = mat * vec;
    for (const auto &elem : res)
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    mat.compressCOO();
    std::cout << "compressed matrix, product: \n";
    res = mat * vec;
    for (const auto &elem : res)
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

void test_ReadMatrix(const std::string &filename)
{
    std::cout << "\nTest for reading the matrix ------------\n";
    algebra::Matrix<double, algebra::StorageOrder::RowMajor> mat = algebra::readMatrix<double, algebra::StorageOrder::RowMajor>(filename);
    mat.compressCOO();
    mat.printArray();
}

// make a sparse vector with 131 elements for testing different cases
std::vector<double> makeSparseVector()
{
    // generate a vector with 131 random elements
    std::vector<double> vec(131);
    for (std::size_t i = 0; i < 131; ++i)
    {
        vec[i] = rand() % 10;
    }
    return vec;
}

void test_time_RowMajor(const std::string &filename, std::vector<double> &vec)
{
    std::cout << "\nTest for multiplying with RowMajor ------------\n";
    // Uncompressed:
    algebra::Matrix<double, algebra::StorageOrder::RowMajor> mat = algebra::readMatrix<double, algebra::StorageOrder::RowMajor>(filename);
    auto start1 = std::chrono::high_resolution_clock::now();

    std::vector<double> res = mat * vec;

    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
    std::string placeholder1 = mat.is_compressed() ? "Compressed: " : "Uncompressed: ";
    std::cout << placeholder1 << duration1.count() << " ms" << std::endl;

    // Compressed:
    mat.compressCOO();
    auto start2 = std::chrono::high_resolution_clock::now();

    std::vector<double> res2 = mat * vec;

    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    std::string placeholder2 = mat.is_compressed() ? "Compressed: " : "Uncompressed: ";
    std::cout << placeholder2 << duration2.count() << " ms" << std::endl;
}

void test_time_ColumnMajor(const std::string &filename, std::vector<double> &vec)
{
    std::cout << "\nTest for multiplying with ColumnMajor ------------\n";
    // Uncompressed:
    algebra::Matrix<double, algebra::StorageOrder::ColumnMajor> mat = algebra::readMatrix<double, algebra::StorageOrder::ColumnMajor>(filename);
    auto start1 = std::chrono::high_resolution_clock::now();

    std::vector<double> res = mat * vec;

    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
    std::string placeholder1 = mat.is_compressed() ? "Compressed: " : "Uncompressed: ";
    std::cout << placeholder1 << duration1.count() << " ms" << std::endl;

    // Compressed:
    mat.compressCOO();
    auto start2 = std::chrono::high_resolution_clock::now();

    std::vector<double> res2 = mat * vec;

    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    std::string placeholder2 = mat.is_compressed() ? "Compressed: " : "Uncompressed: ";
    std::cout << placeholder2 << duration2.count() << " ms" << std::endl;
}

#endif