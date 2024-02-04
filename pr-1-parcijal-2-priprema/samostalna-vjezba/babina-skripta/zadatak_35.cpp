#include<iostream>
#include<cmath>
#include<iomanip>

constexpr std::size_t MATRIX_SIZE { 10 };

void fillMatrixWithPowOf2(unsigned int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void printMatrix(unsigned int (&)[MATRIX_SIZE][MATRIX_SIZE], const char * const);

[[nodiscard]] unsigned int getDigitWidth(const int);
[[nodiscard]] unsigned int getLongestDigitWidthInMatrix(unsigned int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void switchRowsAndColsOfMatrix(unsigned int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void sortMatrixDescendingByCol(unsigned int (&)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t);

int main() {
    unsigned int matrix[MATRIX_SIZE][MATRIX_SIZE] {};

    fillMatrixWithPowOf2(matrix);
    printMatrix(matrix, "Matrica:\n");
    std::cout<<std::endl;
    
    switchRowsAndColsOfMatrix(matrix);
    printMatrix(matrix, "Matrica nakon transponovanja:\n");
    std::cout<<std::endl;

    sortMatrixDescendingByCol(matrix, 3);
    printMatrix(matrix, "Matrica nakon sortiranja 1. kolone (zajedno sa redovima):\n");

    return 0;
}

void fillMatrixWithPowOf2(unsigned int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    unsigned int powerOf2 { 1 };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            matrix[i][ii] = powerOf2;
            powerOf2 *= 2;

            if (powerOf2 < matrix[i][ii]) {
                return;
            }
        }
    }
}

void printMatrix(unsigned int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const char * const outputText) {
    const unsigned int longestWidth { getLongestDigitWidthInMatrix(matrix) };

    std::cout<<outputText;
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            std::cout<<std::setw(longestWidth)<<matrix[i][ii]<<' ';
        }
        std::cout<<std::endl;
    }
}

unsigned int getDigitWidth(const int num) {
    if (!num) {
        return 1;
    }

    const bool isNeg { num < 0 };

    return std::log10(std::abs(num)) + 1 + isNeg;
}

unsigned int getLongestDigitWidthInMatrix(unsigned int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    unsigned int longestWidth { 0u };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            longestWidth = std::max(longestWidth, getDigitWidth(matrix[i][ii]));
        }
    }

    return longestWidth;
}

void switchRowsAndColsOfMatrix(unsigned int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = i + 1; ii < MATRIX_SIZE; ii++) {
            std::swap(matrix[i][ii], matrix[ii][i]);
        }
    }
}

void swapMatrixRows(unsigned int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t rowTarget1, const std::size_t rowTarget2) {
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        std::swap(matrix[rowTarget1][i], matrix[rowTarget2][i]);
    }
}

void sortMatrixDescendingByCol(unsigned int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t col) {
    bool continueSorting {};
    std::size_t tempSize { std::size(matrix) - 1};

    do {
        continueSorting = false;

        for (std::size_t i = 0; i < tempSize; i++) {
            if (matrix[i][col] < matrix[i + 1][col]) {
                swapMatrixRows(matrix, i, i + 1); 
                continueSorting = true;
            }
        }

        tempSize--;
    } while(continueSorting);
}