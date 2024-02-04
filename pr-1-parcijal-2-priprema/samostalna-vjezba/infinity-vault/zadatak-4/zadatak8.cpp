#include<iostream>
#include<cstddef>
#include<limits>
#include<cmath>
#include<iomanip>

constexpr std::size_t MATRIX_SIZE { 8 };

constexpr short TEXT_RED { 0 }, 
                TEXT_DEFAULT { -1 };

const char *setTextColor(const short);

void handleMatrixInput(int &, const std::size_t, const std::size_t); 
void enterMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE], short &);
void printMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE], const short, const std::ptrdiff_t = -1);

float getAverageValueForCol(int (&)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t);
std::size_t getLowestAverageCol(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

short getDigitCount(const int);

int main() {
    int matrix[MATRIX_SIZE][MATRIX_SIZE] {};
    short textWidth {};

    enterMatrix(matrix, textWidth);

    std::size_t lowestAvgIndex { getLowestAverageCol(matrix) };

    printMatrix(matrix, textWidth, lowestAvgIndex);

    return 0;
}

const char *setTextColor(const short color) {
    switch(color) {
        case 0:     // red
            return "\033[31m";
        case 1:     // blue 
            return "\033[36m";
        case 2:     // green
            return "\033[92m";
        default:     // default / reset 
            return "\033[0m";
    }
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        } else if (row % 2 == 0 && num % 2 == 0) {
            std::cout<<"Posto je red paran, unos mora biti neparan broj\n";
            repeatLoop = true;
        } else if (row % 2 != 0 && num % 2 != 0) {
            std::cout<<"Posto je red neparan, unos mora biti paran broj\n";
            repeatLoop = true;
        }
    } while (repeatLoop);
}

void enterMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], short &textWidth) {
    textWidth = 1;

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            handleMatrixInput(matrix[i][ii], i, ii); 

            textWidth = std::max(getDigitCount(matrix[i][ii]), textWidth);
        }
        std::cout<<std::endl;
    }
}

void printMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const short textWidth, std::ptrdiff_t highlightCol) {
    std::cout<<"Ispis matrice";
    if (highlightCol != -1) {
        std::cout<<" (crvena kolona ima najmanji prosjek od svih)";
    } 
    std::cout<<":\n";
    
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            if (ii == highlightCol) {
                std::cout<<setTextColor(TEXT_RED);
            }

            std::cout<<std::setw(textWidth)<<matrix[i][ii]<<' ';
            
            std::cout<<setTextColor(TEXT_DEFAULT);
        }
        std::cout<<std::endl;
    }
}

float getAverageValueForCol(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const std::size_t col) {
    float average { 0.0f };

    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        average += matrix[i][col];
    }

    return average / MATRIX_SIZE;
}

std::size_t getLowestAverageCol(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    std::size_t lowestIndex { 0 };
    float lowestAvg { getAverageValueForCol(matrix, 0) };
    float tempLowestAvg {};

    for (std::size_t i = 1; i < MATRIX_SIZE; i++) {
        tempLowestAvg = getAverageValueForCol(matrix, i);

        if (tempLowestAvg < lowestAvg) {
            lowestAvg = tempLowestAvg;
            lowestIndex = i;
        }
    }

    std::cout<<"Index kolone sa najmanjih prosjekom: "<<lowestIndex<<std::endl; 

    return lowestIndex;
}

short getDigitCount(const int num) {
    return std::log10(num) + 1;
}