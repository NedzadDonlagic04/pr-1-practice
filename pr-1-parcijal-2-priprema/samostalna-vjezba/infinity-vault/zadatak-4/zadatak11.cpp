#include<iostream>
#include<cstddef>
#include<iomanip>
#include<limits>
#include<cmath>

constexpr std::size_t MATRIX_SIZE { 10 };

void clearBuffer();

bool brCif(const int);

void handleMatrixInput(int &, const std::size_t, const std::size_t);
void enterMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void printMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE], const char *);

float getAvgForRow(int (&)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t);
float getAvgForCol(int (&)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t);

void printRowWithHighestAvg(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void printColWithLowestAvg(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

int main() {
    int matrix[MATRIX_SIZE][MATRIX_SIZE] {};

    enterMatrix(matrix);
    printMatrix(matrix, "Matrica nakon unosa:\n");

    printRowWithHighestAvg(matrix);
    printColWithLowestAvg(matrix);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool brCif(const int num) {
    return std::log10(num) + 1;
}

void handleMatrixInput(int &num, const std::size_t row, const std::size_t col) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<"Unos vrijednosti u element ["<<row<<", "<<col<<"]: ";
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (brCif(num) % 2 == 0) {
            std::cout<<"Unos treba imati neparan broj cifara\n";
            repeatLoop = true;
        }
    } while (repeatLoop);
}

void enterMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            handleMatrixInput(matrix[i][ii], i, ii);
        }
    }
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

float getAvgForRow(int (&board)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t row) {
    float average { 0.0f };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        average += board[row][i];
    }

    return average / MATRIX_SIZE;
}

float getAvgForCol(int (&board)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t col) {
    float average { 0.0f };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        average += board[i][col];
    }

    return average / MATRIX_SIZE;
}

void printRowWithHighestAvg(int (&board)[MATRIX_SIZE][MATRIX_SIZE]) {
    std::size_t highestAvgRow { 0 };
    float highestAvg { getAvgForRow(board, 0) };
    float tempAvg {};

    for (std::size_t i = 1; i < MATRIX_SIZE; i++) {
        tempAvg = getAvgForRow(board, i);

        if (highestAvg < tempAvg) {
            highestAvg = tempAvg;
            highestAvgRow = i;
        }
    }

    std::cout<<"Row with highest average: ";
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        std::cout<<board[highestAvgRow][i];
        if (i + 1 != MATRIX_SIZE) {
            std::cout<<", ";
        }
    }
    std::cout<<std::endl;
}

void printColWithLowestAvg(int (&board)[MATRIX_SIZE][MATRIX_SIZE]) {
    std::size_t lowestAvgCol { 0 };
    float lowestAvg { getAvgForCol(board, 0) };
    float tempAvg {};

    for (std::size_t i = 1; i < MATRIX_SIZE; i++) {
        tempAvg = getAvgForCol(board, i);

        if (lowestAvg > tempAvg) {
            lowestAvg = tempAvg;
            lowestAvgCol = i;
        }
    }

    std::cout<<"Col with lowest average: ";
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        std::cout<<board[i][lowestAvgCol];
        if (i + 1 != MATRIX_SIZE) {
            std::cout<<", ";
        }
    }
    std::cout<<std::endl;

}