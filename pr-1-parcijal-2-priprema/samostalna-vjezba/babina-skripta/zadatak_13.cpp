#include<iostream>
#include<limits>
#include<optional>
#include<cmath>
#include<iomanip>

constexpr std::size_t BUFFER_SIZE { 256 };
constexpr std::size_t MATRIX_SIZE { 3 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] unsigned int getDigitWidth(const int);
[[nodiscard]] unsigned int getLongestDigitWidthInMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void enterMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void printMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

[[nodiscard]] int isMatrixSymetricalBasedOnMiddleElement(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

int main() {
    int matrix[MATRIX_SIZE][MATRIX_SIZE] { 0 }; 

    enterMatrix(matrix);
    printMatrix(matrix);

    const int isSymmetricMatrixByMiddle { isMatrixSymetricalBasedOnMiddleElement(matrix) };

    if (isSymmetricMatrixByMiddle == -1) {
        std::cout<<"Matrica ima paran broj redova\n";
    } else if (isSymmetricMatrixByMiddle == 0) {
        std::cout<<"Matrica nije simetricna\n";
    } else {
        std::cout<<"Matrica je simetricna\n";
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

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
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
        } else if (min && num < min.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti manji od %d\n", min.value());
            printErrorMsg(errorMsg);
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti veci od %d\n", max.value());
            printErrorMsg(errorMsg);
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

int isMatrixSymetricalBasedOnMiddleElement(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    if (MATRIX_SIZE % 2 == 0) {
        return -1;
    }

    for (std::size_t i = 0; i < MATRIX_SIZE / 2 + 1; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE / 2 + 1; ii++) {
            if (matrix[i][ii] != matrix[MATRIX_SIZE - 1 - i][MATRIX_SIZE - 1 - ii]) {
                return 0;
            }
        }
    }
    
    return 1;
}