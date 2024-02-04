#include<cstddef>

#pragma once

#ifndef UTILITY
#define UTILITY

namespace utils {
    constexpr std::size_t MATRIX_SIZE { 3 };

    void createSpaces(const int);
    bool enterNum(int &);

    int countDigits(const int);
    int findLargestNumberDigitCount(const int (&)[MATRIX_SIZE][MATRIX_SIZE], std::size_t = MATRIX_SIZE * MATRIX_SIZE);

    void clearTerminal();

    void printMatrix(const int (&)[MATRIX_SIZE][MATRIX_SIZE]);
    void printPartOfMatrix(const int (&)[MATRIX_SIZE][MATRIX_SIZE], std::size_t = MATRIX_SIZE * MATRIX_SIZE, const int = 1);
    void enterMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
}

#endif