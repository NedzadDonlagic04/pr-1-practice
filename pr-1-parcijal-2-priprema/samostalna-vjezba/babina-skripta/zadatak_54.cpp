#include<iostream>
#include<limits>
#include<cmath>
#include<iomanip>

constexpr std::size_t MATRIX_SIZE { 4 };
constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const);

[[nodiscard]] unsigned int getLongestDigitWidthInMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void enterMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void fillEvenRowsOfMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void printMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

[[nodiscard]] unsigned int countDigits(const int);
[[nodiscard]] float srednja_cifra(int);

int main() {
    int matrix[MATRIX_SIZE][MATRIX_SIZE] {};

    enterMatrix(matrix);
    fillEvenRowsOfMatrix(matrix);

    printMatrix(matrix);
    std::cout<<std::endl;

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

void enterAtLeast3DigitNum(int &num, const char * const outputText) {
    bool repeatLoop {};
    char errorMsg[BUFFER_SIZE];

    do {
        repeatLoop = false; 

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (num > -100 && num < 100) {
            printErrorMsg("Broj treba biti minimalno trocifren\n");
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
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

    for (std::size_t i = 0; i < MATRIX_SIZE; i += 2) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            std::sprintf(outputMsg, "Unesi broj na index poziciju [%lu][%lu]: ", i, ii);

            enterAtLeast3DigitNum(matrix[i][ii], outputMsg);
        }
    }
}

void fillEvenRowsOfMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    for (std::size_t i = 1; i < MATRIX_SIZE; i += 2) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            matrix[i][ii] = std::ceil(srednja_cifra(matrix[i - 1][ii]));
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

float srednja_cifra(int num) {
    num = std::abs(num);

    const unsigned int digitCount { getDigitWidth(num) };
    const bool isEven { digitCount % 2 == 0 };
    num = num / std::pow(10, digitCount / 2 - isEven);

    if (digitCount % 2 == 0) {
        return ((num % 10) + ((num / 10) % 10)) / 2.0f;
    }

    return num % 10;
}