#include<iostream>
#include<limits>
#include<cmath>
#include<random>
#include<iomanip>

constexpr std::size_t MATRIX_SIZE { 10 };
constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const);

[[nodiscard]] unsigned int getDigitWidth(const int);
[[nodiscard]] unsigned int getLongestDigitWidthInMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void enterMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void printMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void flipMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void fillMatrixWithRandomNumbers(int (&)[MATRIX_SIZE][MATRIX_SIZE], const int = 0, const int = 1000);

[[nodiscard]] float getAverageForEvensAboveDiagonal(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
[[nodiscard]] float getAverageForOddsAboveSideDiagonal(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

int main() {
    int matrix[MATRIX_SIZE][MATRIX_SIZE] {};

    fillMatrixWithRandomNumbers(matrix);
    printMatrix(matrix);
    std::cout<<std::endl;

    flipMatrix(matrix);
    printMatrix(matrix);
    std::cout<<std::endl;

    const float average4EventsAboveDiagonal { getAverageForEvensAboveDiagonal(matrix) };
    const float average4OddsAboveSideDiagonal { getAverageForOddsAboveSideDiagonal(matrix) };

    std::cout<<"Aritmeticka sredina parni brojeva iznad dijagonale je ";
    std::cout<<average4EventsAboveDiagonal<<std::endl;
    std::cout<<"Aritmeticka sredina neparnih brojeva iznad sporedne dijagonale je ";
    std::cout<<average4OddsAboveSideDiagonal<<std::endl;

    if (average4EventsAboveDiagonal > average4OddsAboveSideDiagonal) {
        std::cout<<"Aritmeticka sredina parni brojeva iznad dijagonale je veca od ";
        std::cout<<"aritmeticke sredine neparnih brojeva iznad sporedne dijagonale\n";
    } else if (average4EventsAboveDiagonal < average4OddsAboveSideDiagonal) {
        std::cout<<"Aritmeticka sredina neparnih brojeva iznad sporedne dijagonale je ";
        std::cout<<"veca od aritmeticke sredine parnih brojeva iznad dijagonale\n";
    } else {
        std::cout<<"Aritmeticke sredine su jednake\n";
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

void enterNum(int &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
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

            enterNum(matrix[i][ii], outputMsg);
        }
    }
}

void printMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    const unsigned int longestMatrixDigitWidth { getLongestDigitWidthInMatrix(matrix) };

    std::cout<<"Ispis matrice:\n";
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            std::cout<<std::setw(longestMatrixDigitWidth)<<matrix[i][ii]<<' ';
        }
        std::cout<<std::endl;
    }
}

void flipMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = i + 1; ii < MATRIX_SIZE; ii++) {
            std::swap(matrix[i][ii], matrix[ii][i]);
        }
    }
}

void fillMatrixWithRandomNumbers(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const int from, const int to) {
    std::random_device dev {};
    std::mt19937 rng { dev() };
    std::uniform_int_distribution<std::mt19937::result_type> dist (from, to);

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            matrix[i][ii] = dist(rng);
        }
    }
}

float getAverageForEvensAboveDiagonal(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    float sum { 0.0f };
    unsigned int counter { 0 };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = i + 1; ii < MATRIX_SIZE; ii++) {
            if (matrix[i][ii] % 2 == 0) {
                sum += matrix[i][ii];
                counter++;
            }
        }
    }

    return (counter)? sum / counter : 0.0f;
}

float getAverageForOddsAboveSideDiagonal(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    float sum { 0.0f };
    unsigned int counter { 0 };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE - i - 1; ii++) {
            if (matrix[i][ii] % 2 != 0) {
                sum += matrix[i][ii];
                counter++;
            }
        }
    }

    return (counter)? sum / counter : 0.0f;
}