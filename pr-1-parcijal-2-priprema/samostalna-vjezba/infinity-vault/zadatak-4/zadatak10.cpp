#include<iostream>
#include<cstddef>
#include<iomanip>

constexpr std::size_t MATRIX_SIZE { 10 };

void printMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE], const char *);
void fillMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void switchRowsAndCols(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

bool isBoardSquareWhite(const std::size_t, const std::size_t);
float getAverageForBlackSquaresAboveDiagonal(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

int main() {
    int matrix[MATRIX_SIZE][MATRIX_SIZE] {};

    printMatrix(matrix, "Orginalna matrica:\n");

    fillMatrix(matrix);
    printMatrix(matrix, "Matrica nakon popunjenja:\n");

    switchRowsAndCols(matrix);
    printMatrix(matrix, "Matrica nakon zamjene redova i kolona:\n");

    std::cout<<"Prosjek vrijednost iznad glavne dijagonale crnih polja je: ";
    std::cout<<getAverageForBlackSquaresAboveDiagonal(matrix)<<std::endl;

    return 0;
}

void printMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const char *outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            std::cout<<std::setw(10)<<matrix[i][ii]<<' ';
        }
        std::cout<<std::endl;
    }
}

void fillMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    int valueToAssing { 1 };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            matrix[i][ii] = valueToAssing;

            valueToAssing *= 2;

            if (valueToAssing < 0) {
                return;
            }
        }
    }
}

void switchRowsAndCols(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = i + 1; ii < MATRIX_SIZE; ii++) {
            // Used for debugging 
            // std::cout<<"["<<i<<", "<<ii<<"] <==> ["<<ii<<", "<<i<<"]\n";
            std::swap(matrix[i][ii], matrix[ii][i]);
        }
    }
}

bool isBoardSquareWhite(const std::size_t row, const std::size_t col) {
    return (row + col) % 2 == 0;
}

float getAverageForBlackSquaresAboveDiagonal(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    float average { 0.0f };
    int counter { 0 };

    std::size_t initialBlackSquare = 1 + isBoardSquareWhite(0, 1);

    for (std::size_t i = 0; i < MATRIX_SIZE - 1; i++) {
        for (std::size_t ii = initialBlackSquare; ii < MATRIX_SIZE; ii += 2) {
            average += matrix[i][ii];
            counter++;
        }
        initialBlackSquare++;
    }

    return (counter)? average / counter : 0.0f;
}