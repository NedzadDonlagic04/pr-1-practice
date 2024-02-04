#include<iostream>
#include<limits>
#include<cmath>
#include<iomanip>

constexpr std::size_t MATRIX_SIZE { 3 };
constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterMatrixNum(int &, const char * const, const bool = true);

[[nodiscard]] unsigned int countDigits(const int);
[[nodiscard]] unsigned int getDigitWidth(const int);
[[nodiscard]] unsigned int getLongestDigitWidthInMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void enterMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void printMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);


[[nodiscard]] float getAverageForMatrixCol(int (&)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t);
[[nodiscard]] std::size_t getMatrixColWithLowestAvg(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

[[nodiscard]] float getAverageForMatrixRow(int (&)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t);
[[nodiscard]] std::size_t getMatrixRowWithHighestAvg(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

[[nodiscard]] bool isSquareWhite(const std::size_t, const std::size_t);
[[nodiscard]] bool isMatrixSymmetricalOnMainDiagonal(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

int main() {
    int matrix[MATRIX_SIZE][MATRIX_SIZE] {};

    enterMatrix(matrix);

    printMatrix(matrix);
    std::cout<<std::endl;

    if (isMatrixSymmetricalOnMainDiagonal(matrix)) {
        const std::size_t highestAvgRow { getMatrixRowWithHighestAvg(matrix) };

        std::cout<<"Red sa najvecim prosjekom: ";
        for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
            std::cout<<matrix[highestAvgRow][i]<<' ';
        }
        std::cout<<std::endl;
    } else {
        const std::size_t lowestAvgCol { getMatrixColWithLowestAvg(matrix) };

        std::cout<<"Kolona sa najnizim prosjekom: ";
        for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
            std::cout<<matrix[i][lowestAvgCol]<<' ';
        }
        std::cout<<std::endl;
    }

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}

void enterMatrixNum(int &num, const char * const outputText, const bool isSquareWhite) {
    bool repeatLoop {};
    
    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (isSquareWhite && (num % 2 == 0 || countDigits(num) % 2 != 0)) {
            printErrorMsg("Unos treba biti neparan broj sa parnim brojem cifara\n");
            clearBuffer();
            repeatLoop = true;
        } else if (!isSquareWhite && (num % 2 != 0 || countDigits(num) % 2 == 0)) {
            printErrorMsg("Unos treba biti paran broj sa neparnim brojem cifara\n");
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

unsigned int countDigits(const int num) {
    if (!num) {
        return 1;
    }

    return std::log10(std::abs(num)) + 1;
}

unsigned int getDigitWidth(const int num) {
    if (!num) {
        return 1;
    }

    const bool isNeg { num < 0 };

    return std::log10(std::abs(num)) + 1 + isNeg;
}

unsigned int getLongestDigitWidthInMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    unsigned int longestWidth { 0u };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            longestWidth = std::max(longestWidth, getDigitWidth(matrix[i][ii]));
        }
    }

    return longestWidth;
}

void enterMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    char outputMsg[BUFFER_SIZE] {};

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            std::sprintf(outputMsg, "Unesi broj na index poziciju [%lu][%lu]: ", i, ii);

            enterMatrixNum(matrix[i][ii], outputMsg, isSquareWhite(i, ii));
        }
    }
}

void printMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    const unsigned int longestMatrixDigitWidth { getLongestDigitWidthInMatrix(matrix) };

    std::cout<<"Ispis matrice:\n";
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            if (isSquareWhite(i, ii)) {
                std::cout<<"\033[40m";
            } else {
                std::cout<<"\033[47m";
            }

            std::cout<<std::setw(longestMatrixDigitWidth)<<matrix[i][ii
            ];

            if (ii + 1 != MATRIX_SIZE) {
                std::cout<<' ';
            }
            
            std::cout<<"\033[49m";
        }
        std::cout<<std::endl;
    }
}

float getAverageForMatrixCol(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t colToFind) {
    float sum { 0.0f };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        sum += matrix[i][colToFind];  
    }

    return sum / MATRIX_SIZE;
}

std::size_t getMatrixColWithLowestAvg(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    std::size_t lowestAvgCol { 0 };
    float lowestAvg { getAverageForMatrixCol(matrix, lowestAvgCol) };
    float tempAvg {};

    for (std::size_t i = 1; i < MATRIX_SIZE; i++) {
        tempAvg = getAverageForMatrixCol(matrix, i);

        if (tempAvg < lowestAvg) {
            lowestAvg = tempAvg;
            lowestAvgCol = i;
        }
    }

    // Debug
    // std::cout<<lowestAvg<<std::endl;

    std::cout<<"Kolona sa najmanjim prosjekom je kolona sa indexom ";
    std::cout<<lowestAvgCol<<std::endl;

    return lowestAvgCol;
}

float getAverageForMatrixRow(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t rowToFind) {
    float sum { 0.0f };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        sum += matrix[rowToFind][i];  
    }

    return sum / MATRIX_SIZE;
}

std::size_t getMatrixRowWithHighestAvg(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    std::size_t highestAvgRow { 0 };
    float highestAvg { getAverageForMatrixRow(matrix, highestAvgRow) };
    float tempAvg {};

    for (std::size_t i = 1; i < std::size(matrix); i++) {
        tempAvg = getAverageForMatrixCol(matrix, i);

        if (tempAvg > highestAvg) {
            highestAvg = tempAvg;
            highestAvgRow = i;
        }
    }

    // Debug
    // std::cout<<highestAvgRow<<std::endl;

    std::cout<<"Red sa najvecim prosjekom je red sa indexom ";
    std::cout<<highestAvgRow<<std::endl;

    return highestAvgRow;
}

bool isSquareWhite(const std::size_t row, const std::size_t col) {
    return (row + col) % 2 == 0;
}

bool isMatrixSymmetricalOnMainDiagonal(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = i + 1; ii < MATRIX_SIZE; ii++) {
            if (matrix[i][ii] != matrix[ii][i]) {
                return false;
            }
        }
    }

    return true;
}