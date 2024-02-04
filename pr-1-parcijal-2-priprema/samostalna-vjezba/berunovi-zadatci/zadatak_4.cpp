#include<iostream>
#include<iomanip>
#include<cmath>
#include<limits>

unsigned int longestDigitCount { 1 };

[[nodiscard]] unsigned int countDigits(const int);

void clearBuffer();
void enterSize(std::size_t &, const char * const);

int getRandomValue(int, int);
int** createMatrix(int, int);
void setRandomValues(int **, int, int, int, int);
void printMatrix(int **, int, int);
int** diagonalStack(int **, int **, int, int, int, int);
void deleteMatrix(int **, int);

int main() {
    std::srand(time(NULL));
    // In case constant seed needed
    // std::srand(15);

    std::size_t row1 {}, row2 {};
    std::size_t col1 {}, col2 {};

    enterSize(row1, "Unesite broj redova za prvu matricu: ");
    enterSize(col1, "Unesite broj kolona za prvu matricu: ");
    enterSize(row2, "Unesite broj redova za drugu matricu: ");
    enterSize(col2, "Unesite broj kolona za drugu matricu: ");

    int **matrix1 { createMatrix(row1, col1) };
    int **matrix2 { createMatrix(row2, col2) };

    setRandomValues(matrix1, row1, col1, 1, 10);
    setRandomValues(matrix2, row2, col2, 1, 10);

    std::cout<<"Matrica M1:\n";
    printMatrix(matrix1, row1, col1);

    std::cout<<"Matrica M2:\n";
    printMatrix(matrix2, row2, col2);

    int **diagonalMatrix { diagonalStack(matrix1, matrix2, row1, col1, row2, col2) };

    std::cout<<"Matrica M3 formirana diagonalnim slaganjem M1 i M2:\n";
    printMatrix(diagonalMatrix, row1 + row2, col1 + col2);

    deleteMatrix(matrix1, row1);
    deleteMatrix(matrix2, row2);
    deleteMatrix(diagonalMatrix, row1 + row2);

    return 0;
}

unsigned int countDigits(const int num) {
    if (num == 0) {
        return 1;
    }

    const bool isNeg { num < 0 };

    return std::log10(std::abs(num)) + 1 + isNeg;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterSize(std::size_t &size, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>size;

        if (std::cin.fail()) {
            std::cout<<"Invalid input\n";
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Unos treba biti u intervalu [2, 1000]\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

int getRandomValue(int from, int to) {
    return std::rand() % (to - from + 1) + from; 
}

int** createMatrix(int rows, int columns) {
    int **matrix { new int*[rows] {} };

    for (std::size_t i = 0; i < rows; i++) {
        matrix[i] = new int[columns] {};
    }

    return matrix;
}

void setRandomValues(int **matrix, int rows, int columns, int from, int to) {
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < columns; ii++) {
            matrix[i][ii] = getRandomValue(from, to);

            longestDigitCount = std::max(longestDigitCount, countDigits(matrix[i][ii]));
        }
    }
}

void printMatrix(int **matrix, int rows, int columns) {
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < columns; ii++) {
            std::cout<<std::setw(longestDigitCount)<<matrix[i][ii]<<' ';
        }
        std::cout<<'\n';
    }

}

int** diagonalStack(int **m1, int **m2, int r1, int c1, int r2, int c2) {
    int **diagonalMatrix { createMatrix(r1 + r2, c1 + c2) };

    for (std::size_t i = 0; i < r1; i++) {
        for (std::size_t ii = 0; ii < c1; ii++) {
            diagonalMatrix[i][ii] = m1[i][ii];
        }
    }

    for (std::size_t i = r1; i < r1 + r2; i++) {
        for (std::size_t ii = c1; ii < c1 + c2; ii++) {
            diagonalMatrix[i][ii] = m2[i - r1][ii - c1];
        }
    }

    return diagonalMatrix;
}

void deleteMatrix(int **matrix, int rows) {
    for (std::size_t i = 0; i < rows; i++) {
        delete[] matrix[i];
    }

    delete matrix;

    longestDigitCount = 1;
}