#include<iostream>
#include<iomanip>
#include<cmath>

constexpr std::size_t MATRIX_SIZE { 5 };

void fillMatrixWithFibNums(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void printMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void printBiggestDividorsForMatrixSides(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
[[nodiscard]] unsigned int euklidovAlgoritam(const int, const int);

[[nodiscard]] unsigned int countDigits(const int);
[[nodiscard]] unsigned int getLongestDigit(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

int main() {
    int matrix[MATRIX_SIZE][MATRIX_SIZE] {};

    fillMatrixWithFibNums(matrix);
    printMatrix(matrix);
    std::cout<<std::endl;
    printBiggestDividorsForMatrixSides(matrix);

    return 0;
}

void fillMatrixWithFibNums(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    unsigned int a { 0 };
    unsigned int b { 1 };
    bool isANext { true };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            if (isANext) {
                matrix[ii][i] = a;
                a += b;
            } else {
                matrix[ii][i] = b;
                b += a;
            }

            isANext = !isANext;
        }
    }
}

void printMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    const unsigned int longestDigit { getLongestDigit(matrix) };

    std::cout<<"Matrix:\n";
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            std::cout<<std::setw(longestDigit + 1)<<matrix[i][ii];
        }
        std::cout<<'\n';
    }
}

void printBiggestDividorsForMatrixSides(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    std::size_t halfRow = std::ceil(MATRIX_SIZE / 2.0);

    std::cout<<"Ispis najveci djelilaca brojeva u matrici:\n";
    for (std::size_t i = 0; i < halfRow; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            if (i + 1 == halfRow && ii == halfRow) {
                break;
            }

            const int a { matrix[i][ii] };
            const int b { matrix[MATRIX_SIZE - 1 - i][MATRIX_SIZE - 1 - ii] };

            std::cout<<"Za brojeve "<<a<<" i "<<b<<" najveci djelilac je "<<euklidovAlgoritam(a, b);
            std::cout<<'\n';
        }
        std::cout<<'\n';
    }
}

unsigned int euklidovAlgoritam(int a, int b) {
    while (b) {
        std::swap(a, b);
        b %= a;
    }

    return a;
}

unsigned int countDigits(const int num) {
    if (num == 0) {
        return 1;
    }

    const bool isNeg { num < 0 };

    return std::log10(std::abs(num)) + 1 + isNeg;
}

unsigned int getLongestDigit(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    unsigned int longestDigit { 0 };
    unsigned int tempLongestDigit {};

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            tempLongestDigit = countDigits(matrix[i][ii]);

            if (tempLongestDigit > longestDigit) {
                longestDigit = tempLongestDigit;
            }
        }
    }

    return longestDigit;
}